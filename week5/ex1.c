// Create a bunch of threads that run strictly one after another.
#include <stdio.h>
#include <pthread.h>

#define THREAD_COUNT 100

struct threadArg {
    int id;
};

typedef struct threadArg threadArg_t;

void * print_hello(void *arg) {
    printf("thread %d: Hello!\n", ((threadArg_t *)arg)->id);
    
    pthread_exit(0);
}

int main() {
    pthread_t threads[THREAD_COUNT];
    threadArg_t args[THREAD_COUNT];

    for (int i = 0; i < 100; i++) {
        args[i].id = i;
        pthread_create(&threads[i], NULL, print_hello, (void *)&args[i]);
        printf("main: created thread %d\n", i);
        pthread_join(threads[i], NULL);
    }

    pthread_exit(NULL);
}
