section .data
    proc_path db "/proc", 0          ; Path to the proc directory
    proc_name db "/proc/", 0         ; Template for process directories
    status_file db "/comm", 0        ; File to get the process name
    sigkill equ 9                    ; Signal number for SIGKILL
    max_buf equ 256                  ; Buffer size for reading

section .bss
    buffer resb max_buf              ; Buffer for reading data
    name_buffer resb 16              ; Buffer for process name
    dirent_buffer resb 1024          ; Buffer for reading dirents

section .text
    global _start

_start:
    ; Open the /proc directory
    mov rax, 257                     ; openat syscall
    mov rdi, -100                    ; AT_FDCWD
    mov rsi, proc_path
    mov rdx, 0                       ; O_RDONLY
    syscall
    mov r12, rax                      ; Store /proc fd

    ; Read the directory entries
read_dir:
    mov rax, 217                     ; getdents64 syscall
    mov rdi, r12                      ; /proc fd
    mov rsi, dirent_buffer            ; Buffer to read into
    mov rdx, 1024                     ; Buffer size
    syscall

    cmp rax, 0                       ; Check if any entries were read
    jle end_program                   ; Exit if no more entries

    ; Loop through the directory entries
    mov rcx, rax                      ; Number of bytes read
    mov rbx, dirent_buffer

parse_dir:
    ; Get the inode number (process ID)
    mov rsi, rbx
    add rsi, 10                       ; Offset to name (assumes x86-64)
    movzx rdx, word [rsi - 2]         ; Get the name length
    lea rdi, [proc_name]              ; Write into proc_name
    mov rcx, rdx                       ; Name length
    rep movsb                        ; Copy the process name
    
    add rbx, rdx                       ; Move to next directory entry

    ; Check if the name is a numeric PID
    mov rsi, rbx
    test byte [rsi], 0x30              ; Check if it's a number
    jne parse_dir                      ; If not, skip

    ; Open the /proc/<pid>/comm file to get the process name
    mov rax, 257                       ; openat syscall
    lea rsi, [proc_name]                ; /proc/<pid> base
    add rsi, 6                          ; offset after /proc/
    lea rdi, [rsi + 7]                  ; /proc/<pid>/comm path
    mov byte [rdi], '/'
    mov byte [rdi + 1], 'c'
    mov byte [rdi + 2], 'o'
    mov byte [rdi + 3], 'm'
    mov byte [rdi + 4], 'm'
    mov byte [rdi + 5], 0

    mov rdi, r12                       ; Parent fd
    mov rdx, 0                          ; O_RDONLY
    syscall

    ; Read the process name from /proc/<pid>/comm
    mov rax, 0                          ; read syscall
    mov rsi, buffer                     ; Buffer to read into
    mov rdi, rax                        ; File descriptor
    mov rdx, max_buf                    ; Max buffer size
    syscall

    ; Check if the command line parameter is in the process name
    mov rsi, [rsp + 8]                   ; argv[1]
    mov rdi, buffer                      ; Process name
    call find_substring                  ; Find the substring
    test rax, rax                        ; Check if the substring was found
    je next_dir

    ; If the process name contains the substring, kill the process
    mov rax, 62                          ; kill syscall
    mov rdi, [proc_name]                  ; Process PID
    mov rsi, sigkill                     ; SIGKILL signal
    syscall

next_dir:
    ; Move to the next directory entry
    add rbx, rdx
    dec rcx
    jnz parse_dir

    ; Loop to read more directory entries
    jmp read_dir

end_program:
    mov rax, 60                          ; exit syscall
    xor rdi, rdi                          ; exit code 0
    syscall

find_substring:
    ; Implement a simple substring search algorithm
    ; This is just a placeholder; a proper substring search is required
    ; Returns 0 if substring is found, non-zero otherwise
    xor rax, rax
    ret
