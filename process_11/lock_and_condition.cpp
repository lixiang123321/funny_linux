//
// Created by rere on 2021/7/15.
//

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_OF_TASKS 3
#define MAX_TASK_QUEUE 11

char tasklist[MAX_TASK_QUEUE] = "ABCDEFGHIJ";
int head = 0;
int tail = 0;

int quit = 0;

pthread_mutex_t g_task_lock;
pthread_cond_t g_task_cv;

// macos is Unix-like, use <uni std.h> and usleep
// https://stackoverflow.com/questions/19439672/sleep-operation-in-c-on-os-x/19440500
//#define sleep(x) usleep(x*1000)

void *coder(void *notused) {
    pthread_t thread = pthread_self();
#define tid thread

    // keep running
    while (!quit) {

        pthread_mutex_lock(&g_task_lock);
        // get the lock

        while (tail == head) {
            // no task
            if (quit) {
                // quit under finish type.
                pthread_mutex_unlock(&g_task_lock);
                pthread_exit((void *) 0);
            }

            printf("No task now! Thread %u is waiting!.\n", tid);
            pthread_cond_wait(&g_task_cv, &g_task_lock); // release lock and block
            // wake up and lock again
            // !!! the condition and lock must both ok, will go this.
            // how it implement??

            printf("Have task now! Thread %u is grabing the task !\n", tid);
        }

        // has task, with lock
        char task = tasklist[head++];
        pthread_mutex_unlock(&g_task_lock);
        printf("Thread %u has a task %c now!\n", tid, task);

        // doing task
        sleep(5);
        printf("Thread %u finish the task %c\n", tid, task);
    }
    pthread_exit((void *) 0);
}

int main(int argc, char *argv[]) {
    pthread_t threads[NUM_OF_TASKS];
    int rc;
    int t;

    // init lock and condition
    pthread_mutex_init(&g_task_lock, NULL);
    pthread_cond_init(&g_task_cv, NULL);

    // pthread create
    for (t = 0; t < NUM_OF_TASKS; t++) {
        rc = pthread_create(&threads[t], NULL, coder, NULL);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    sleep(5);

    // generate jobs every 20s.
    for (t = 1; t <= 4; t++) {
        pthread_mutex_lock(&g_task_lock);
        tail += t;
        printf("\nI am Boss, I assgned %d tasks, I notify all coders!\n", t);
        pthread_cond_broadcast(&g_task_cv);
        pthread_mutex_unlock(&g_task_lock);
        // broadcast/signal and unlock, order, check url below
        // https://stackoverflow.com/questions/4544234/calling-pthread-cond-signal-without-locking-mutex

        // sleep(20);
        // set 10 second to sleep, means longer,
        // and all jobs will be done in this 20s, and all the task will block by cond_wait().

        sleep(2);
        // set 2 second to sleep, means shorter
        // tasks will also do/clean the job,
        // though there is no new cond_broadcast, but
        // because while(!quit) is true. and while(tail == head) -> False, so cond_wait() will not call.

    }

    while (head != tail) {
        sleep(2);
    }

    pthread_mutex_lock(&g_task_lock);
    quit = 1;
    pthread_cond_broadcast(&g_task_cv);
    pthread_mutex_unlock(&g_task_lock);

    pthread_mutex_destroy(&g_task_lock);
    pthread_cond_destroy(&g_task_cv);
    pthread_exit(NULL);
}