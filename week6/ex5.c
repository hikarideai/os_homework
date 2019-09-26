// EX5 -- A child prints a string every second, while the parent thread waits
//        10 seconds, sends SIGTERM to the child and terminates.
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void signal_handler(int signum) {
    exit(0);
}

int main(int argc, char* argv[]) {
    int pid = fork();

    if (pid) {
        struct timespec interval;
        interval.tv_sec = 10;
        nanosleep(&interval, NULL);
        kill(pid, SIGTERM);
    } else {
        for (;;) {
            printf("I'm alive!\n");
            fflush(stdout);
            struct timespec interval;
            interval.tv_sec = 1;
            nanosleep(&interval, NULL);
        }
    }
    return 0;
}
