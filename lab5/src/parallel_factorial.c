#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
unsigned long long result = 1;

typedef struct {
    int k;
    int pnum;
    int mod;
    int thread_num;
} ThreadParams;

void *computeFactorial(void *params) {
    ThreadParams *p = (ThreadParams *)params;
    int k = p->k;
    int mod = p->mod;
    int start = (k / p->pnum) * p->thread_num + 1;
    int end = (p->thread_num == p->pnum - 1) ? k : (k / p->pnum) * (p->thread_num + 1);
    unsigned long long local_result = 1;

    for (int i = start; i <= end; i++) {
        local_result = (local_result * i) % mod;
    }

    pthread_mutex_lock(&mutex);
    result = (result * local_result) % mod;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char *argv[]) {
    int k = -1;
    int pnum = -1;
    int mod = -1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-k") == 0 && i + 1 < argc) {
            k = atoi(argv[i + 1]);
        } else if (strncmp(argv[i], "--pnum=", 7) == 0) {
            pnum = atoi(argv[i] + 7);
        } else if (strncmp(argv[i], "--mod=", 6) == 0) {
            mod = atoi(argv[i] + 6);
        }
    }

    if (k < 1 || pnum < 1 || mod < 1) {
        printf("Usage: %s -k <k> --pnum=<pnum> --mod=<mod>\n", argv[0]);
        return 1;
    }

    pthread_t *threads = malloc(sizeof(pthread_t) * pnum);
    ThreadParams *params = malloc(sizeof(ThreadParams) * pnum);

    for (int i = 0; i < pnum; i++) {
        params[i].k = k;
        params[i].pnum = pnum;
        params[i].mod = mod;
        params[i].thread_num = i;
        pthread_create(&threads[i], NULL, computeFactorial, &params[i]);
    }

    for (int i = 0; i < pnum; i++) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    free(params);

    printf("%d! mod %d = %llu\n", k, mod, result);

    return 0;
}