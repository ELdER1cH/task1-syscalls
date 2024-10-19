/* Export functions here */// /* Export functions here */
// ## Task 1.1
// Write a wrapper for the read and write system calls by using the syscall function from the glibc. 
// Add the following optimsation: if the number of bytes to read/write is 0, do not call the system call.
// The resulting binary should be a shared library named librw_1.so 
// and should be usable by any application to replace the original glibc implementations of these two wrappers 
// without changing the behaviour of applications.

#include <unistd.h>
#include <sys/syscall.h>

/*
    int fd - file descriptor
    void *buf - buffer
    size_t count - number of bytes to read
 */
ssize_t read(int fd, void *buf, size_t count) {
    if (count == 0) {
        return 0;
    }
    return syscall(SYS_read, fd, buf, count);
}

/*
    int fd - file descriptor
    const void *buf - buffer
    size_t count - number of bytes to write
 */

ssize_t write(int fd, const void *buf, size_t count) {
    if (count == 0) {
        return 0;
    }
    return syscall(SYS_write, fd, buf, count);
}