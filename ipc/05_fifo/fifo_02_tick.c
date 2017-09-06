#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "american maid"

// This program receives data through a FIFO.
// Algorithm:
// 1. Create a FIFO
// 2. Try open() it
// 3. open() call will block until some other process 
//    opens the FIFO for writing
int main(void) {
    char s[300];
    int num, fd;

    // create a fifo
    mknod(FIFO_NAME, S_IFIFO | 0666, 0);

    printf("waiting for writers...\n");
    fd = open(FIFO_NAME, O_RDONLY);
    printf("got a writer\n");

    do {
        if ((num = read(fd, s, 300)) == -1) {
            perror("read");
        } else {
            s[num] = '\0';
            printf("tick: read %d bytes: \"%s\"\n", num, s);
        }
    } while (num > 0);

    return 0;
}

