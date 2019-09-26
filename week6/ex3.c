// EX3 -- An example of setting up a signal handler using portable sigaction().
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void signal_handler(int signum) {
    if (signum == SIGINT) {
        fprintf(stderr, "Caught SIGINT(%d) signal. Thank you!\n", signum);
    }
    exit(0);
}

int main() {
    struct sigaction act;
    act.sa_handler = signal_handler;

    sigaction(SIGINT, &act, NULL);

    printf("I have stuck in an infinite loop!\n");
    while (1);

    return 0;
}
