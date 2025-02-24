#include <iostream>
#include <vector>
#include <unordered_map>
#include <sys/syscall.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <linux/limits.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_SIZE 4096

// Define linux_dirent64 structure without flexible array member
struct linux_dirent64
{
    ino64_t d_ino;           // 64-bit inode number
    off64_t d_off;           // 64-bit offset to next structure
    unsigned short d_reclen; // Size of this dirent
    unsigned char d_type;    // File type
    char d_name[256];        // Filename (null-terminated)
};

struct ProcessInfo
{
    int pid;
    std::string name;
    int ppid;
    std::vector<ProcessInfo> children;
};

std::string strip_parentheses(const std::string &str)
{
    if (str.size() > 2 && str.front() == '(' && str.back() == ')')
    {
        return str.substr(1, str.size() - 2);
    }
    return str;
}

void add_children_to_process(ProcessInfo &process, std::unordered_map<int, ProcessInfo> &process_map)
{
    for (auto it = process_map.begin(); it != process_map.end();)
    {
        if (it->second.ppid == process.pid)
        {
            process.children.push_back(it->second);
            it = process_map.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (auto &child : process.children)
    {
        add_children_to_process(child, process_map);
    }
}

std::vector<ProcessInfo> get_processes_info()
{
    std::vector<ProcessInfo> processes;
    std::unordered_map<int, ProcessInfo> process_map;
    int fd = syscall(SYS_openat, AT_FDCWD, "/proc", O_RDONLY | O_DIRECTORY);
    if (fd < 0)
    {
        perror("Failed to open /proc directory");
        return processes;
    }

    char buffer[BUFFER_SIZE];
    struct linux_dirent64 *d;
    int nread;

    while ((nread = syscall(SYS_getdents64, fd, buffer, sizeof(buffer))) > 0)
    {
        for (int bpos = 0; bpos < nread;)
        {
            d = (struct linux_dirent64 *)(buffer + bpos);
            if (isdigit(d->d_name[0]))
            {
                ProcessInfo pinfo;
                pinfo.pid = atoi(d->d_name);

                // Reading status
                char status_path[PATH_MAX];
                snprintf(status_path, sizeof(status_path), "/proc/%d/stat", pinfo.pid);
                int status_fd = syscall(SYS_openat, AT_FDCWD, status_path, O_RDONLY);
                if (status_fd != -1)
                {
                    char status[BUFFER_SIZE];
                    ssize_t len = syscall(SYS_read, status_fd, status, sizeof(status) - 1);
                    if (len > 0)
                    {
                        status[len] = '\0';
                        std::istringstream ss(status);
                        std::string temp;
                        ss >> pinfo.pid >> pinfo.name >> temp >> pinfo.ppid;

                        pinfo.name = strip_parentheses(pinfo.name);

                        process_map[pinfo.pid] = pinfo;
                    }
                    syscall(SYS_close, status_fd);
                }
            }
            bpos += d->d_reclen;
        }
    }

    if (nread == -1)
    {
        perror("Error reading /proc directory");
    }

    syscall(SYS_close, fd);

    // Collect top-level processes (with ppid 0)
    for (auto it = process_map.begin(); it != process_map.end();)
    {
        if (it->second.ppid == 0)
        {
            processes.push_back(it->second);
            it = process_map.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // Build the process tree
    for (auto &process : processes)
    {
        add_children_to_process(process, process_map);
    }

    return processes;
}

void write_processes_info(const std::vector<ProcessInfo> &processes, std::ostringstream &oss, int indent = 2)
{
    std::string indent_str(indent, ' ');
    for (size_t i = 0; i < processes.size(); ++i)
    {
        const ProcessInfo &pinfo = processes[i];
        oss << indent_str << "{\n";
        oss << indent_str << "  \"pid\": " << pinfo.pid << ",\n";
        oss << indent_str << "  \"name\": \"" << pinfo.name << "\",\n";
        if (!pinfo.children.empty())
        {
            oss << indent_str << "  \"children\": [\n";
            write_processes_info(pinfo.children, oss, indent + 4);
            oss << indent_str << "  ]\n";
        }
        else
        {
            oss << indent_str << "  \"children\": []\n";
        }
        oss << indent_str << "}";
        if (i < processes.size() - 1)
            oss << ",";
        oss << "\n";
    }
}

int main()
{
    std::vector<ProcessInfo> processes = get_processes_info();
    std::ostringstream oss;
    oss << "[\n";
    write_processes_info(processes, oss);
    oss << "]\n";
    std::string output = oss.str();
    syscall(SYS_write, STDOUT_FILENO, output.c_str(), output.size());
    return 0;
}
