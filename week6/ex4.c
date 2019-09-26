// EX4 -- Try to catch SIGKILL, SIGSTOP (hopelessly) and SIGUSR1.
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void signal_handler(int signum) {
    const char * signame;
    switch (signum) {
    case SIGKILL:
        // Should never happen
        signame = "SIGKILL";
        break;
    case SIGSTOP:
        // Should never happen also
        signame = "SIGSTOP";
        break;
    case SIGUSR1:
        signame = "SIGUSR1";
        break;
    default:
        fprintf(stderr, "Somehow caught a signal that I didn't intend to handle!\n");
    }

    fprintf(stderr, "Caught %s(%d) signal. Thank you!\n", signame, signum);
    exit(0);
}

int main() {
    struct sigaction act;
    act.sa_handler = signal_handler;

    sigaction(SIGKILL, &act, NULL);
    sigaction(SIGSTOP, &act, NULL);
    sigaction(SIGUSR1, &act, NULL);

    printf("I have stuck in an infinite loop!\n");
    while (1);

    return 0;
}
