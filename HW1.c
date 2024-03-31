#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

void multi(int start, int end) {
    for (int i = start; i <= end; i++) {
        printf("%d * 7 = %d\n", i, i * 7);
    }
}

int main() {
    int process = 8;
    int range = 1000 / process;
    pid_t pid;
    clock_t startM, startS, endM, endS;
    double multiT, singleT;

    startM = clock();
    printf("멀티 프로세스 시작\n");

    for (int i = 0; i < process; i++) {
        pid = fork();

        if (pid == 0) { 
            int start = i * range + 1;
            int end = (i + 1) * range;
            if (i == process - 1) end = 1000;
            multi(start, end);
            return 0; 
        }
    }

    while (wait(NULL) > 0);
    endM = clock();
    multiT = ((double) (endM - startM)) / CLOCKS_PER_SEC;

    startS = clock();
    printf("단일 프로세스 시작\n");
    for (int i = 1; i <= 1000; i++) {
        printf("%d * 7 = %d\n", i, i * 7);
    }
    endS = clock();
    singleT = ((double) (endS - startS)) / CLOCKS_PER_SEC;
    printf("멀티 프로세스의 개수: %d개\n", process);
    printf("멀티 프로세스 시간: %f 초\n", multiT);
    printf("단일 프로세스 시간: %f 초\n", singleT);

    return 0;
}