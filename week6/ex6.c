// EX6 -- Create two child processes and check wheather waitpid(3) returns on
//        child's state change (stop, cont, sig)
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <time.h>

#define WAIT_DELAY 5

void secsleep(int t) {
    struct timespec interval;
    interval.tv_sec = t;
    nanosleep(&interval, NULL);
}

void pwstat(int, const char*);

int main() {
    int pp[2];
    pipe(pp);

    pid_t ch1 = fork();
    pid_t ch2;
    
    if (ch1) {
        ch2 = fork();
        
        if (ch2) {
            // main
            if (write(pp[1], (char *)&ch2, sizeof(ch2)) < 0) {
                perror("main");
            }

            int status = 0;
            while (!status || (!WIFSIGNALED(status) && !WIFEXITED(status))) {
                waitpid(ch2, &status, WUNTRACED | WCONTINUED);
                pwstat(status, "Second child has changed its state");
            }

            wait(NULL); // Wait for the first child
        } else {
            // Child 2
            for (;;) {
                secsleep(1);
                printf("Beep Boop! [2]\n");
            }
        }
    } else {
        // Child 1
        secsleep(WAIT_DELAY);

        // Get the pid of the second child
        int ch2;
        read(pp[0], (char *)&ch2, sizeof(int));
        kill(ch2, SIGSTOP);
        printf("Child 1 sent SIGSTOP\n");

        secsleep(WAIT_DELAY);

        kill(ch2, SIGCONT);

        secsleep(WAIT_DELAY);
        
        kill(ch2, SIGKILL);

        exit(0);
    }

    return 0;
}

void pwstat(int wstatus, const char* header) {
    if (header)
        printf("%s:\n", header);

    printf("\texited: %d\n", WIFEXITED(wstatus));
    if (WIFEXITED(wstatus))
        printf("\t\texit code: %d\n", WEXITSTATUS(wstatus));
    printf("\tsignaled: %d\n", WIFSIGNALED(wstatus));
    if (WIFSIGNALED(wstatus)) {
        printf("\t\tsignal code: %d\n", WTERMSIG(wstatus));
        printf("\t\tcore dumped: %d\n", WCOREDUMP(wstatus));
    }
    printf("\tstopped: %d\n", WIFSTOPPED(wstatus));
    if (WIFSTOPPED(wstatus)) {
        printf("\t\tsignal code: %d\n", WSTOPSIG(wstatus));
    }
    printf("\tcontinued: %d\n", WIFCONTINUED(wstatus));

    fflush(stdout);
}
