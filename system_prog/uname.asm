section .data
    prompt_hostname db 'Hostname: ', 0
    prompt_os db 'OS: ', 0
    prompt_version db 'Version: ', 0
    prompt_release db 'Release: ', 0
    newline db 10

section .bss
    uname_buf resb 65*5

section .text
    global _start

_start:
    mov rax, 63
    mov rdi, uname_buf
    syscall

    mov rax, 1
    mov rdi, 1
    mov rsi, prompt_hostname
    mov rdx, 10
    syscall

    lea rsi, [uname_buf + 65]
    call write_cstring

    mov rax, 1
    mov rdi, 1
    mov rsi, newline
    mov rdx, 1
    syscall

    mov rax, 1
    mov rdi, 1
    mov rsi, prompt_os
    mov rdx, 4
    syscall

    lea rsi, [uname_buf]
    call write_cstring

    mov rax, 1
    mov rdi, 1
    mov rsi, newline
    mov rdx, 1
    syscall

    mov rax, 1
    mov rdi, 1
    mov rsi, prompt_version
    mov rdx, 9
    syscall

    lea rsi, [uname_buf + 195]
    call write_cstring

    mov rax, 1
    mov rdi, 1
    mov rsi, newline
    mov rdx, 1
    syscall

    mov rax, 1
    mov rdi, 1
    mov rsi, prompt_release
    mov rdx, 9
    syscall

    lea rsi, [uname_buf + 130]
    call write_cstring

    mov rax, 1
    mov rdi, 1
    mov rsi, newline
    mov rdx, 1
    syscall

    mov rax, 60
    xor rdi, rdi
    syscall

write_cstring:
    push rdx

    mov rax, 1
    mov rdi, 1
    
    xor rdx, rdx
    .find_null_byte:
        cmp byte [rsi + rdx], 0
        je .end_find
        inc rdx
        jmp .find_null_byte

    .end_find:
    syscall

    pop rdx
    ret