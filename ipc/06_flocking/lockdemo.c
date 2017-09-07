#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

// This program waits for the user to hit return, then locks its own source, 
// waits for another return, then unlocks it. 
// By running this program in two (or more) windows, you can see how 
// programs interact while waiting for locks.

// Basic usage:
// - if run with no cmd arguments, a program gets write lock on itself
// - if run with any cmd arguments, a program gets read lock on itself

// Compile this stuff and start messing with it in a couple of windows.
// Notice that:
// - when one lockdemo has a read lock, other instances of the 
//   program can get their own read locks with no problem.
// - when a write lock is obtained, none of other processes can get a lock 
//   of any kind.

int main(int argc, char* argv[]) {
    struct flock fl = {F_WRLCK, SEEK_SET, 0, 0, 0};
    int fd;

    fl.l_pid = getpid();

    if (argc > 1) {
        fl.l_type = F_RDLCK;
    }

    if ((fd = open("lockdemo.c", O_RDWR)) == -1) {
        perror("open");
        exit(1);
    }

    printf("Press <RETURN> to try to get lock: ");
    getchar();
    printf("Trying to get lock...");

    if (fcntl(fd, F_SETLKW, &fl) == -1) {
        perror("fcntl");
        exit(1);
    }
    
    printf("got lock\n");
    printf("Press <RETURN> to release lock: ");
    getchar();

    fl.l_type = F_UNLCK;    // set to unlock same region

    if (fcntl(fd, F_SETLK, &fl) == -1) {
        perror("fcntl");
        exit(1);
    }

    printf("Unlocked.\n");

    close(fd);

    return 0;
}


