#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

// interesting fact (not directly related to this program):
// in unix, stdin is fd "0", stdout is "1", stderr is "2"
int main(void) {
    int pfds[2]; // pair of file descriptors
    char buf[30];

    // pipe() returns 2 file descriptors, one of them is connected to write end 
    // of pipe, and the other is connected to read end of pipe
    if (pipe(pfds) == -1) {
        perror("pipe");
        exit(1);
    }

    printf("writing to file descriptor #%d\n", pfds[1]);
    write(pfds[1], "test", 5);

    printf("reading from file descriptor #%d\n", pfds[0]);
    read(pfds[0], buf, 5);
    printf("read \"%s\"\n", buf);

    return 0;
}


