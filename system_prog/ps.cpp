#include <iostream>
#include <vector>
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
    std::string exe;
    std::string cwd;
    unsigned long long base_address;
    std::string state;
    std::vector<std::string> cmdline;
};

std::string read_symlink(const std::string &path)
{
    char buffer[PATH_MAX];
    ssize_t len = syscall(SYS_readlink, path.c_str(), buffer, sizeof(buffer) - 1);

    if (len == -1)
    {
        return "";
    }

    buffer[len] = '\0';
    return std::string(buffer);
}

unsigned long long get_base_address(int pid)
{
    char maps_path[PATH_MAX];
    snprintf(maps_path, sizeof(maps_path), "/proc/%d/maps", pid);
    int maps_fd = syscall(SYS_openat, AT_FDCWD, maps_path, O_RDONLY);
    if (maps_fd == -1)
    {
        return 0;
    }

    char buffer[BUFFER_SIZE];
    ssize_t len = syscall(SYS_read, maps_fd, buffer, sizeof(buffer) - 1);
    syscall(SYS_close, maps_fd);

    if (len <= 0)
    {
        return 0;
    }

    buffer[len] = '\0';
    std::istringstream ss(buffer);
    std::string address_range;
    ss >> address_range;

    size_t pos = address_range.find('-');
    if (pos == std::string::npos)
    {
        return 0;
    }

    std::string base_address_str = address_range.substr(0, pos);
    return std::stoull(base_address_str, nullptr, 16);
}

std::vector<ProcessInfo> get_processes_info()
{
    std::vector<ProcessInfo> processes;
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

                // Reading exe link
                std::string exe_path = "/proc/" + std::to_string(pinfo.pid) + "/exe";
                pinfo.exe = read_symlink(exe_path);

                // Reading cwd link
                std::string cwd_path = "/proc/" + std::to_string(pinfo.pid) + "/cwd";
                pinfo.cwd = read_symlink(cwd_path);

                // Skip process if exe or cwd is empty
                if (pinfo.exe.empty() || pinfo.cwd.empty())
                {
                    bpos += d->d_reclen;
                    continue;
                }

                // Reading base address
                pinfo.base_address = get_base_address(pinfo.pid);

                // Reading cmdline
                char cmdline_path[PATH_MAX];
                snprintf(cmdline_path, sizeof(cmdline_path), "/proc/%d/cmdline", pinfo.pid);
                int cmdline_fd = syscall(SYS_openat, AT_FDCWD, cmdline_path, O_RDONLY);
                if (cmdline_fd != -1)
                {
                    char cmdline[BUFFER_SIZE];
                    ssize_t len = syscall(SYS_read, cmdline_fd, cmdline, sizeof(cmdline) - 1);
                    if (len > 0)
                    {
                        cmdline[len] = '\0';
                        std::istringstream ss(std::string(cmdline, len));
                        std::string arg;
                        while (std::getline(ss, arg, '\0'))
                        {
                            pinfo.cmdline.push_back(arg);
                        }
                    }
                    syscall(SYS_close, cmdline_fd);
                }

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
                        ss >> temp >> temp >> pinfo.state >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp;
                    }
                    syscall(SYS_close, status_fd);
                }

                processes.push_back(pinfo);
            }
            bpos += d->d_reclen;
        }
    }

    if (nread == -1)
    {
        perror("Error reading /proc directory");
    }

    syscall(SYS_close, fd);
    return processes;
}

void write_processes_info(const std::vector<ProcessInfo> &processes)
{
    std::ostringstream oss;
    oss << "[\n";
    for (size_t i = 0; i < processes.size(); ++i)
    {
        const ProcessInfo &pinfo = processes[i];
        oss << "  {\n";
        oss << "    \"pid\": " << pinfo.pid << ",\n";
        oss << "    \"exe\": \"" << pinfo.exe << "\",\n";
        oss << "    \"cwd\": \"" << pinfo.cwd << "\",\n";
        oss << "    \"base_address\": " << pinfo.base_address << ",\n";
        oss << "    \"state\": \"" << pinfo.state << "\",\n";
        oss << "    \"cmdline\": [\n";
        for (size_t j = 0; j < pinfo.cmdline.size(); ++j)
        {
            oss << "      \"" << pinfo.cmdline[j] << "\"";
            if (j < pinfo.cmdline.size() - 1)
                oss << ",";
            oss << "\n";
        }
        oss << "    ]\n";
        oss << "  }";
        if (i < processes.size() - 1)
            oss << ",";
        oss << "\n";
    }
    oss << "]\n";

    std::string output = oss.str();
    syscall(SYS_write, STDOUT_FILENO, output.c_str(), output.size());
}

int main()
{
    std::vector<ProcessInfo> processes = get_processes_info();
    write_processes_info(processes);
    return 0;
}
