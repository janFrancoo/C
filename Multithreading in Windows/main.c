#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define N_THREAD    8
#define ARR_LIM     1000000

static int *arr;
static int *resArr;

typedef struct {
    unsigned int tId;
    unsigned int start;
    unsigned int end;
} Interval;

Interval getInterval (int threadId) {
    Interval interval;
    int n = ARR_LIM / N_THREAD;

    interval.tId = threadId;
    interval.start = threadId * n;
    interval.end = (threadId + 1) * n - 1;

    return interval;
}

DWORD WINAPI FindAverage(void *lpParam) {
    Interval *interval;
    interval = (Interval *) lpParam;

    int sum = 0;
    for (int i=interval->start; i<=interval->end; i++) {
        sum += arr[i];
    }

    resArr[interval->tId] = sum / (ARR_LIM / N_THREAD);

    return 0;
}

int main()
{
    srand(time(0));

    HANDLE threadArr[N_THREAD];
    arr = malloc(sizeof(int) * ARR_LIM);
    resArr = malloc(sizeof(int) * N_THREAD);

    for (int i=0; i<ARR_LIM; i++)
        arr[i] = rand();

    for (int i=0; i<N_THREAD; i++) {
        Interval interval = getInterval(i);
        threadArr[i] = CreateThread(NULL, 0, FindAverage, &interval, 0, NULL);
        Sleep(1);
    }

    WaitForMultipleObjects(N_THREAD, threadArr, TRUE, INFINITE);

    int sum = 0;
    for (int i=0; i<N_THREAD; i++)
        sum += resArr[i];

    printf("Result = %d\n", sum / N_THREAD);

    return 0;
}
