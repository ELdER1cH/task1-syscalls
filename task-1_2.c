/* Export functions here */
 /* Export functions here */

// ## Task 1.2
// Reuse your wrappers from task 1.1 and replace the syscall function with assembly that performs the system call. 
// You must manage error reporting in the same way the glibc would.
// The resulting binary should be a shared library named librw_2.so 
// and should be usable by any application to replace the original glibc implementations of these two wrappers without changing the behaviour of applications.


#include <unistd.h>
#include <sys/syscall.h>
 
//  asm asm-qualifiers ( AssemblerTemplate 
//                       : OutputOperands
//                       : InputOperands
//                       : Clobbers
//                       : GotoLabels)

// BSPW
// int src = 1;
// int dst;   

// asm ("mov %1, %0\n\t"
//     "add $1, %0"
//     : "=r" (dst) 
//     : "r" (src));

// printf("%d\n", dst);

// This code copies src to dst and add 1 to dst.


/*
    int fd - file descriptor
    void *buf - buffer
    size_t count - number of bytes to read
 */
ssize_t read(int fd, void *buf, size_t count) {
    if (count == 0 || count > 6)
        return 0;
    ssize_t ret;

    asm(    " movq %[syscall], %%rax\n"
            " movq %[fd], %%rdi\n"
            " movq %[buf], %%rsi\n"
            " movq %[count], %%rdx\n"
            " syscall\n"
            " movq %%rax, %[result]\n" 
            : [result]"=r" (ret)
            : [fd] "D" (fd), [buf] "S" (buf), [count] "d" (count), [syscall] "a" (SYS_read));
    return ret;
}


/*
    int fd - file descriptor
    const void *buf - buffer
    size_t count - number of bytes to write
 */

ssize_t write(int fd, const void *buf, size_t count) {
    if (count == 0 || count > 6)
        return 0;
    ssize_t ret;

    asm(" movq $0, %%rax\n"
            " movq $0, %%rdi\n"
            " movq $0, %%rsi\n"
            " movq $0, %%rdx\n"
            " syscall\n"
            " movq %%rax, %0\n"
            : "=r"(ret)
            : "D"(fd), "S"(buf), "d"(count), "a"(SYS_write)
            : "cc", "memory");
 return ret;
}