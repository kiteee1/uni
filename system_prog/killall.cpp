#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/klog.h>
#include <signal.h>
#include <cstring>
#include <dirent.h>
#include <vector>

bool containsSubstring(const std::string &name, const std::string &substring) {
    return name.find(substring) != std::string::npos;
}

std::string readFile(const std::string &filePath) {
    char buffer[256];
    int fd = open(filePath.c_str(), O_RDONLY);
    if (fd < 0) {
        return "";
    }

    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    close(fd);

    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        return std::string(buffer);
    } else {
        return "";
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <substring>" << std::endl;
        return 1;
    }

    std::string targetSubstring(argv[1]);
    std::string procPath = "/proc";
    std::vector<pid_t> matchingPids;

    DIR *procDir = opendir(procPath.c_str());
    if (!procDir) {
        std::cerr << "Failed to open /proc" << std::endl;
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(procDir)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            pid_t pid = atoi(entry->d_name);
            if (pid > 0) {
                std::string commPath = procPath + "/" + std::to_string(pid) + "/comm";
                std::string processName = readFile(commPath);

                if (containsSubstring(processName, targetSubstring)) {
                    matchingPids.push_back(pid);
                }
            }
        }
    }

    closedir(procDir);

    for (pid_t pid : matchingPids) {
        if (kill(pid, SIGKILL) < 0) {
            std::cerr << "Failed to kill process " << pid << std::endl;
        }
    }

    return 0;
}