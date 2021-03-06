#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<string.h>
#include<sys/wait.h>
#include<pthread.h>

#define MM_LEN (int)(16*1024*1024)
#define L3_LEN (int)(4*1024*1024) /* Unused in this code */
#define L2H_LEN (int)((1*1024*1024)/2)
#define L2_LEN (int)(1*1024*1024)
#define L1_LEN (int)(32*1024)
#define RUNLEN (MM_LEN)

void * CPU_spin(void * arg);
void * L1_test(void * arg);
void * L2_half_test(void * arg);
void * L2_test(void * arg);
void * L3_test(void * arg);
void * MM_test(void * arg);

int main()
{
    pthread_t t[4];

    printf("Test 1:\n");
    pthread_create(&t[0], NULL, MM_test, (void *) RUNLEN);
    pthread_join(t[0], NULL);
    printf("Test 2:\n");
    pthread_create(&t[0], NULL, MM_test, (void *) RUNLEN);
    CPU_spin((void *) RUNLEN);
    pthread_join(t[0], NULL);
    printf("Test 3:\n");
    pthread_create(&t[0], NULL, MM_test, (void *) RUNLEN);
    L1_test((void *) (RUNLEN*5));
    pthread_join(t[0], NULL);
    printf("Test 4:\n");
    pthread_create(&t[0], NULL, MM_test, (void *) RUNLEN);
    L2_half_test((void *) (RUNLEN*5));
    pthread_join(t[0], NULL);
    printf("Test 4:\n");
    pthread_create(&t[0], NULL, MM_test, (void *) RUNLEN);
    L2_test((void *) (RUNLEN*5));
    pthread_join(t[0], NULL);
    printf("Test 5:\n");
    pthread_create(&t[0], NULL, MM_test, (void *) RUNLEN);
    MM_test((void *) RUNLEN);
    pthread_join(t[0], NULL);
    return 0;
}

void * CPU_spin(void * ratio)
{
    char * chunk = NULL;
    struct timeval t1;
    struct timeval t2;
    for(int i = 0; i<50000000; i++);
    return 0;
}

void * L1_test(void * arg)
{
    int i = 0;
    int ratio = ((int) arg) / L1_LEN;
    char * chunk = NULL;
    struct timeval t1;
    struct timeval t2;

    chunk = malloc(L1_LEN);

    for(i=0; i < ratio; i++)
    {
        memset(chunk, 42, L1_LEN);
        memset(chunk, 0, L1_LEN);
        memset(chunk, 42, L1_LEN);
        memset(chunk, 0, L1_LEN);
        memset(chunk, 42, L1_LEN);
        memset(chunk, 0, L1_LEN);
    }
    gettimeofday(&t1, NULL);
    for(i=0; i < ratio; i++)
    {
        memset(chunk, 42, L1_LEN);
        memset(chunk, 0, L1_LEN);
    }
    gettimeofday(&t2, NULL);
    for(i=0; i < ratio; i++)
    {
        memset(chunk, 42, L1_LEN);
        memset(chunk, 0, L1_LEN);
        memset(chunk, 42, L1_LEN);
        memset(chunk, 0, L1_LEN);
        memset(chunk, 42, L1_LEN);
        memset(chunk, 0, L1_LEN);
    }

    printf("L1: sec: %d us: %d\n", (int) t2.tv_sec - (int) t1.tv_sec, (int) t2.tv_usec - (int) t1.tv_usec);
    
    free(chunk);

    return 0;
}

void * L2_half_test(void * arg)
{
    int i = 0;
    int ratio = ((int) arg) / L2H_LEN;
    char * chunk = NULL;
    struct timeval t1;
    struct timeval t2;

    chunk = malloc(L2H_LEN);

    for(i=0; i < ratio; i++)
    {
        memset(chunk, 42, L2H_LEN);
        memset(chunk, 0, L2H_LEN);
        memset(chunk, 42, L2H_LEN);
        memset(chunk, 0, L2H_LEN);
        memset(chunk, 42, L2H_LEN);
        memset(chunk, 0, L2H_LEN);
    }
    gettimeofday(&t1, NULL);
    for(i=0; i < ratio; i++)
    {
        memset(chunk, 42, L2H_LEN);
        memset(chunk, 0, L2H_LEN);
    }
    gettimeofday(&t2, NULL);
    for(i=0; i < ratio; i++)
    {
        memset(chunk, 42, L2H_LEN);
        memset(chunk, 0, L2H_LEN);
        memset(chunk, 42, L2H_LEN);
        memset(chunk, 0, L2H_LEN);
        memset(chunk, 42, L2H_LEN);
        memset(chunk, 0, L2H_LEN);
    }

    printf("L2H: sec: %d us: %d\n", (int) t2.tv_sec - (int) t1.tv_sec, (int) t2.tv_usec - (int) t1.tv_usec);

    free(chunk);

    return 0;
}

void * L2_test(void * arg)
{
    int i = 0;
    int ratio = ((int) arg) / L2_LEN;
    char * chunk = NULL;
    struct timeval t1;
    struct timeval t2;

    chunk = malloc(L2_LEN);

    for(i=0; i < ratio; i++)
    {
        memset(chunk, 42, L2_LEN);
        memset(chunk, 0, L2_LEN);
        memset(chunk, 42, L2_LEN);
        memset(chunk, 0, L2_LEN);
        memset(chunk, 42, L2_LEN);
        memset(chunk, 0, L2_LEN);
    }
    gettimeofday(&t1, NULL);
    for(i=0; i < ratio; i++)
    {
        memset(chunk, 42, L2_LEN);
        memset(chunk, 0, L2_LEN);
    }
    gettimeofday(&t2, NULL);
    for(i=0; i < ratio; i++)
    {
        memset(chunk, 42, L2_LEN);
        memset(chunk, 0, L2_LEN);
        memset(chunk, 42, L2_LEN);
        memset(chunk, 0, L2_LEN);
        memset(chunk, 42, L2_LEN);
        memset(chunk, 0, L2_LEN);
    }

    printf("L2: sec: %d us: %d\n", (int) t2.tv_sec - (int) t1.tv_sec, (int) t2.tv_usec - (int) t1.tv_usec);

    free(chunk);

    return 0;
}

void * L3_test(void * arg)
{
    int i = 0;
    int ratio = ((int) arg) / L3_LEN;
    char * chunk = NULL;
    struct timeval t1;
    struct timeval t2;

    chunk = malloc(L3_LEN);

    for(i=0; i < ratio; i++)
    {
        memset(chunk, 42, L3_LEN);
        memset(chunk, 0, L3_LEN);
        memset(chunk, 42, L3_LEN);
        memset(chunk, 0, L3_LEN);
        memset(chunk, 42, L3_LEN);
        memset(chunk, 0, L3_LEN);
    }
    gettimeofday(&t1, NULL);
    for(i=0; i < ratio; i++)
    {
        memset(chunk, 42, L3_LEN);
        memset(chunk, 0, L3_LEN);
    }
    gettimeofday(&t2, NULL);
    for(i=0; i < ratio; i++)
    {
        memset(chunk, 42, L3_LEN);
        memset(chunk, 0, L3_LEN);
        memset(chunk, 42, L3_LEN);
        memset(chunk, 0, L3_LEN);
        memset(chunk, 42, L3_LEN);
        memset(chunk, 0, L3_LEN);
    }

    printf("L3: sec: %d us: %d\n", (int) t2.tv_sec - (int) t1.tv_sec, (int) t2.tv_usec - (int) t1.tv_usec);

    free(chunk);
        
    return 0;
}

void * MM_test(void * arg)
{
    int i = 0;
    int ratio = ((int) arg) / MM_LEN;
    char * chunk = NULL;
    struct timeval t1;
    struct timeval t2;

    chunk = malloc(MM_LEN);

    for(i=0; i < ratio; i++)
    {
        memset(chunk, 42, MM_LEN);
        memset(chunk, 0, MM_LEN);
        memset(chunk, 42, MM_LEN);
        memset(chunk, 0, MM_LEN);
        memset(chunk, 42, MM_LEN);
        memset(chunk, 0, MM_LEN);
    }
    gettimeofday(&t1, NULL);
    for(i=0; i < ratio; i++)
    {
        memset(chunk, 42, MM_LEN);
        memset(chunk, 0, MM_LEN);
    }
    gettimeofday(&t2, NULL);
    for(i=0; i < ratio; i++)
    {
        memset(chunk, 42, MM_LEN);
        memset(chunk, 0, MM_LEN);
        memset(chunk, 42, MM_LEN);
        memset(chunk, 0, MM_LEN);
        memset(chunk, 42, MM_LEN);
        memset(chunk, 0, MM_LEN);
    }

    printf("MM: sec: %d us: %d\n", (int) t2.tv_sec - (int) t1.tv_sec, (int) t2.tv_usec - (int) t1.tv_usec);

    free(chunk);

    return 0;
}
