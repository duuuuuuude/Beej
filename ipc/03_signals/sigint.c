#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>


// SIGINT - interrupt signal that process receives when user hits ^C

// handle SIGINT
void sigint_handler(int sig) {
    write(0, "Handle sigint..\n", 17);
}

int main(void) {
    // prototype
    void sigint_handler(int sig);

    char s[200];
    struct sigaction sa;

    sa.sa_handler = sigint_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    // set up signal handler
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("Enter a string:\n");
    
    if (fgets(s, sizeof s, stdin) == NULL) {
        perror("fgets:");
    } else {
        printf("You entered: %s\n", s);
    }

    return 0;
}


