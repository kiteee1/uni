#include <iostream>
#include <sys/stat.h>
#include <linux/stat.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

int statx_call(int dirfd, const char *pathname, int flags, unsigned int mask, struct statx *statxbuf) {
    return syscall(SYS_statx, dirfd, pathname, flags, mask, statxbuf);
}

std::string mode_to_string(uint16_t mode) {
    std::string perms = "";

    perms += (mode & S_IRUSR) ? 'r' : '-';
    perms += (mode & S_IWUSR) ? 'w' : '-';
    perms += (mode & S_IXUSR) ? 'x' : '-';

    perms += (mode & S_IRGRP) ? 'r' : '-';
    perms += (mode & S_IWGRP) ? 'w' : '-';
    perms += (mode & S_IXGRP) ? 'x' : '-';

    perms += (mode & S_IROTH) ? 'r' : '-';
    perms += (mode & S_IWOTH) ? 'w' : '-';
    perms += (mode & S_IXOTH) ? 'x' : '-';

    return perms;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    const char *filename = argv[1];
    struct statx stx;

    if (statx_call(AT_FDCWD, filename, AT_SYMLINK_NOFOLLOW, STATX_UID | STATX_GID, &stx) == -1) {
        std::cerr << "Error getting UID/GID: " << strerror(errno) << std::endl;
        return 1;
    }
    int uid = stx.stx_uid;
    int gid = stx.stx_gid;

    if (statx_call(AT_FDCWD, filename, AT_SYMLINK_NOFOLLOW, STATX_SIZE, &stx) == -1) {
        std::cerr << "Error getting file size: " << strerror(errno) << std::endl;
        return 1;
    }
    off_t file_size = stx.stx_size;

    if (statx_call(AT_FDCWD, filename, AT_SYMLINK_NOFOLLOW, STATX_MODE, &stx) == -1) {
        std::cerr << "Error getting file permissions: " << strerror(errno) << std::endl;
        return 1;
    }
    std::string permissions = mode_to_string(stx.stx_mode);

    std::cout << "UID: " << uid << ", GID: " << gid << std::endl;
    std::cout << "Size: " << file_size << std::endl;
    std::cout << permissions << std::endl;

    return 0;
}