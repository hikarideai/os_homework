// EX8 -- An implementation of FCFS and SJN scheduling algorithms. Due to time 
//        constraints I decided to write only these two. However, I made it
//        extremely easy to extend functionality and add new implementations!
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define PROC_MAX 100
#define SCHD_MAX 2
#define DELAY 1

// Use to pass procces queue data to the different scheduling implementations.
struct proc_queue {
    int n;
    int* burst;
    // int* arrival;
    // int* priority;
};

typedef struct proc_queue proc_queue_t;

// Shedulers
void fcfs(proc_queue_t);
void sjn(proc_queue_t);

// Input handling routines
void read_tty(int*, int[]);
void read_args(int*, int[], int, char*[]);

// Clean up rountines
void proc_queue_free(proc_queue_t);


// Entry point
int main(int argc, char* argv[]) {
    // Read data
    int n;
    int burst[PROC_MAX];
    if (argc == 1) {
        read_tty(&n, burst);
    } else {
        read_args(&n, burst, argc, argv);
    }

    // Initialize hardcoded list of sheduler implementations
    void  (*schedule[SCHD_MAX])(proc_queue_t) = {
        fcfs, sjn
    };

    // Initialize process queue struct
    proc_queue_t arg;
    arg.n = n;
    arg.burst = (int*)malloc(n * sizeof(int));

    // Execute scheduler implementations one by one
    for (int i = 0; i < SCHD_MAX; i++) {
        memcpy(arg.burst, burst, n * sizeof(int));
        schedule[i](arg);
        printf("\n");
    }

    // Clean up
    proc_queue_free(arg);
    return 0;
}

void fcfs(proc_queue_t in) {
    printf("First Come First Serve (FCFS):\n");

    float total_wait = 0;
    int time = 0;
    for (int i = 0; i < in.n; i++) {
        total_wait += time;
        printf("P%d", i + 1);
        fflush(stdout);
        while (in.burst[i]) {
            sleep(DELAY);
            printf("=");
            fflush(stdout);
            in.burst[i]--;
            time++;
        }
    }
    printf("\nAverage Wait Time: %f\n", total_wait / in.n);
}

void sjn(proc_queue_t in) {
    printf("Shortest Job Next (SJN):\n");

    float total_wait = 0;
    int time = 0;
    for (int i = 0; i < in.n; i++) {
        int min = -1;
        for (int j = 0; j < in.n; j++) {
            if (min == -1 || in.burst[min] > in.burst[j]) 
                min = j;
        }

        total_wait += time;
        printf("P%d", min + 1);
        fflush(stdout);
        while (in.burst[min]) {
            sleep(DELAY);
            printf("=");
            fflush(stdout);
            in.burst[min]--;
            time++;
        }

        in.burst[min] = INT_MAX;
    }
    printf("\nAverage Wait Time: %f\n", total_wait / in.n);
}

void read_tty(int* n, int burst[]) {
    printf("Process count: ");
    scanf("%d", n);

    printf("Enter CPU bursts: ");
    for (int i = 0; i < *n; i++)
        scanf("%d", &burst[i]);

    printf("\n");
}

void read_args(int* n, int burst[], int argc, char* argv[]) {
    *n = argc - 1;

    for (int i = 0; i < argc; i++)
        sscanf(argv[i + 1], "%d", &burst[i]);
}

void proc_queue_free(proc_queue_t arg) {
    free(arg.burst);
}
