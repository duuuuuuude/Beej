#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Basically, FIFO is a named pipe, but there's difference.
// With pipe:
// you must pipe() then fork() to get a child process that can
// communicate to the parent via the pipe
// With fifo:
// each unrelated process can simply open() pipe and transfer 
// data through it, no fork() needed

#define FIFO_NAME "american maid"

// this program sends data through a FIFO
// Algorithm:
// 1. Create a fifo
// 2. Try to open() it
// 3. open() call will block until some other process 
//    opens the other end of the pipe for reading
int main(void) {
    char s[300];
    int num, fd;

    // create a fifo
    mknod(FIFO_NAME, S_IFIFO | 0666, 0);

    printf("waiting for readers...\n");
    fd = open(FIFO_NAME, O_WRONLY);
    printf("got a reader -- type some stuff\n");

    // TODO !feof(stdin) means "true if feof(stdin) == 0, false otherwise"
    while(gets(s), !feof(stdin)) { 
        if ((num = write(fd, s, strlen(s))) == -1) {
            perror("write");
        } else {
            printf("speak: wrote %d bytes\n", num);
        }
    }

    return 0;
}

