#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    int rv;

    // after fork(), there is 2 instances of your program running.
    // after fork(), pid of the child process is returned in the parent process
    // in the child process, fork() just returns 0
    // https://stackoverflow.com/questions/15102328/how-does-fork-work
    switch(pid = fork()) {
        case -1:
            perror("fork");
            exit(1); // parent exits
            break;

        case 0:
            printf("CHILD: this is a child process!\n");
            printf("CHILD: my PID is %d\n", getpid());
            printf("CHILD: my parent's PID is %d\n", getppid());
            printf("CHILD: enter my exit status: ");
            scanf("%d", &rv);
            printf("CHILD: I'm outta here!\n");
            exit(rv);
            break;
            
        default:
            printf("PARENT: this is a PARENT process!\n");
            printf("PARENT: my PID is %d\n", getpid());
            printf("PARENT: my child's PID is %d\n", pid);
            printf("PARENT: I am now waiting for my child to exit()...");
            wait(&rv);
            printf("PARENT: My child's exit status is: %d\n", WEXITSTATUS(rv));
            printf("PARENT: I'm outta here!\n");
            break;
    }
}


