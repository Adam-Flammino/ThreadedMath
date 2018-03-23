#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

bool busy = false;
int nextInLine = -1;
int x;
int y;
int result1;
int result2;
int result3;
int totalLoops = 3000;
int totalLoopsCompleted = 0;

void enterCritical(int requestingThread){
    while (busy || nextInLine != requestingThread){
        if (nextInLine == -1){
            nextInLine = requestingThread;
        }
    }
    busy = true;
}

void leaveCritical(int requestingProcess){
    if (nextInLine == requestingProcess){ // Prevents a single thread from always being next in line
        nextInLine = -1;
    }
    busy = false;
}

void * first(){
    int i = 0;
    for(totalLoopsCompleted; totalLoopsCompleted < totalLoops; totalLoopsCompleted++) {
        i++;
        printf("\nThread one starting for the %i time\n", i);
        enterCritical(0);
        x = 5;
        y = 2;
        result1 = x + y;
        leaveCritical(0);
        printf("Thread 1 thinks 5 + 2 = %i\n", result1);
        usleep(rand() % 100);
    }
    result1 = i;
}

void * second(){
    int i = 0;
    for(totalLoopsCompleted; totalLoopsCompleted < totalLoops; totalLoopsCompleted++) {
        i++;
        printf("\nThread two starting for the %i time\n", i);
        enterCritical(1);
        x = 3;
        y = 7;
        result2 = x - y;
        leaveCritical(1);
        printf("Thread 2 thinks 3 - 7 = %i\n", result2);
        usleep(rand() % 100);
    }
    result2 = i;
}

void * third(){
    int i = 0;
    for(totalLoopsCompleted; totalLoopsCompleted < totalLoops; totalLoopsCompleted++) {
        i++;
        printf("\nThread three starting for the %i time\n", i);
        enterCritical(2);
        x = 9;
        y = 6;
        result3 = x * y;
        leaveCritical(2);
        printf("Thread 3 thinks 9 * 6 = %i", result3);
        usleep(rand() % 100);
    }
    result3 = i;
}

int main() {
    int threads = 2;
    srand(time(NULL));
    pthread_t tid[threads];
        pthread_create(&tid[0], NULL, &first, NULL);
        pthread_create(&tid[1], NULL, &second, NULL);
        pthread_create(&tid[2], NULL, &third, NULL);
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    return 0;
}
