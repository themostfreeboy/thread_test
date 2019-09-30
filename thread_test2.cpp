#include <stdio.h>
#include <pthread.h>

static int public_num = 0;
const int THREAD_NUM = 1000;
const int TIMES = 1000;

pthread_mutex_t mutex;

void* fun(void* args) {
    int thread_index = *(int*)args;
    for (int i=0; i<TIMES; ++i) {
        pthread_mutex_lock(&mutex);
        ++public_num;
        pthread_mutex_unlock(&mutex);
    }
    printf("thread %d:public_num=%d\n", thread_index, public_num);
    return NULL;
}

int main(int argc, char** argv) {
    pthread_t thread[THREAD_NUM];
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("pthread_mutex_init error\n");
        return 0;
    }
    for (int i=0; i<THREAD_NUM; ++i) {
        pthread_create(&thread[i], NULL, fun, (void*)(&i));
    }
    for (int i=0; i<THREAD_NUM; ++i) {
        pthread_join(thread[i], NULL);
    }
    printf("main:public_num=%d\n", public_num);
    if (pthread_mutex_destroy(&mutex) != 0) {
        printf("pthread_mutex_destroy error\n");
    }
    return 0;
}
