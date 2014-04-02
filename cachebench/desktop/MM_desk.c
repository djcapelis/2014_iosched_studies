#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<string.h>
#include<sys/wait.h>
#include<pthread.h>

#define MM_LEN (int)(16*1024*1024)
#define L3_LEN (int)(4*1024*1024)
#define L3H_LEN (int)(2*1024*1024)
#define L2_LEN (int)(256*1024)
#define L1_LEN (int)(64*1024)

void * CPU_spin(void * arg);
void * L1_test(void * arg);
void * L2_test(void * arg);
void * L3H_test(void * arg);
void * L3_test(void * arg);
void * MM_test(void * arg);

int main()
{
    pthread_t t[4];

    printf("Test 1:\n");
    pthread_create(&t[0], NULL, MM_test, (void *) MM_LEN);
    pthread_join(t[0], NULL);
    printf("Test 2:\n");
    pthread_create(&t[0], NULL, MM_test, (void *) MM_LEN);
    CPU_spin((void *) MM_LEN);
    pthread_join(t[0], NULL);
    printf("Test 3:\n");
    pthread_create(&t[0], NULL, MM_test, (void *) MM_LEN);
    L2_test((void *) (MM_LEN*5*5));
    pthread_join(t[0], NULL);
    printf("Test 4:\n");
    pthread_create(&t[0], NULL, MM_test, (void *) MM_LEN);
    L3H_test((void *) (MM_LEN*5));
    pthread_join(t[0], NULL);
    printf("Test 5:\n");
    pthread_create(&t[0], NULL, MM_test, (void *) MM_LEN);
    L3_test((void *) (MM_LEN*5));
    pthread_join(t[0], NULL);
    printf("Test 6:\n");
    pthread_create(&t[0], NULL, MM_test, (void *) MM_LEN);
    MM_test((void *) MM_LEN);
    pthread_join(t[0], NULL);
    printf("Test 7a:\n");
    pthread_create(&t[0], NULL, MM_test, (void *) MM_LEN);
    pthread_create(&t[1], NULL, MM_test, (void *) MM_LEN);
    MM_test((void *) MM_LEN);
    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);
    printf("Test 7:\n");
    pthread_create(&t[0], NULL, MM_test, (void *) MM_LEN);
    pthread_create(&t[1], NULL, MM_test, (void *) MM_LEN);
    pthread_create(&t[2], NULL, MM_test, (void *) MM_LEN);
    MM_test((void *) MM_LEN);
    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);
    pthread_join(t[2], NULL);
    printf("Test 8:\n");
    pthread_create(&t[0], NULL, L2_test, (void *) (MM_LEN*5*5));
    pthread_create(&t[1], NULL, L3H_test, (void *) (MM_LEN*5));
    pthread_create(&t[2], NULL, MM_test, (void *) MM_LEN);
    CPU_spin((void *) MM_LEN);
    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);
    pthread_join(t[2], NULL);
    printf("Test 9:\n");
    pthread_create(&t[0], NULL, L2_test, (void *) (MM_LEN*5*5));
    pthread_create(&t[1], NULL, L3_test, (void *) (MM_LEN*5));
    pthread_create(&t[2], NULL, MM_test, (void *) MM_LEN);
    CPU_spin((void *) MM_LEN);
    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);
    pthread_join(t[2], NULL);
    return 0;
}

void * CPU_spin(void * ratio)
{
    char * chunk = NULL;
    struct timeval t1;
    struct timeval t2;
    for(int i = 0; i>-1; i++);
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

void * L3H_test(void * arg)
{
    int i = 0;
    int ratio = ((int) arg) / L3H_LEN;
    char * chunk = NULL;
    struct timeval t1;
    struct timeval t2;

    chunk = malloc(L3H_LEN);

    for(i=0; i < ratio; i++)
    {
        memset(chunk, 42, L3H_LEN);
        memset(chunk, 0, L3H_LEN);
        memset(chunk, 42, L3H_LEN);
        memset(chunk, 0, L3H_LEN);
        memset(chunk, 42, L3H_LEN);
        memset(chunk, 0, L3H_LEN);
    }
    gettimeofday(&t1, NULL);
    for(i=0; i < ratio; i++)
    {
        memset(chunk, 42, L3H_LEN);
        memset(chunk, 0, L3H_LEN);
    }
    gettimeofday(&t2, NULL);
    for(i=0; i < ratio; i++)
    {
        memset(chunk, 42, L3H_LEN);
        memset(chunk, 0, L3H_LEN);
        memset(chunk, 42, L3H_LEN);
        memset(chunk, 0, L3H_LEN);
        memset(chunk, 42, L3H_LEN);
        memset(chunk, 0, L3H_LEN);
    }

    printf("L3H: sec: %d us: %d\n", (int) t2.tv_sec - (int) t1.tv_sec, (int) t2.tv_usec - (int) t1.tv_usec);

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
	int j = 0;
    int ratio = ((int) arg) / MM_LEN;
    unsigned int * chunk = NULL;
    struct timeval t1;
    struct timeval t2;

    chunk = malloc(MM_LEN);

    for(i=0; i < ratio; i++)
    {
        memset(chunk, 42, MM_LEN);
        memset(chunk, 0, MM_LEN);
    }
	for(i=0; i < MM_LEN/8; i++)
		chunk[i] = rand();
    gettimeofday(&t1, NULL);
    for(i=0; i < ratio; i++)
    {
		for(j=0;j<((MM_LEN/8)-7);j++)
			chunk[j] = chunk[(chunk[j] % ((MM_LEN/8)-1))];
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

/*
int misc(int tc)
{
    chunk = malloc(chunklen);
    pid = fork();
    if(pid == 0)
    {
        for(int i = 0; i>-1; i++);
        for(int i = 0; i>-1; i++);
        for(int i = 0; i>-1; i++);
        return 0;
    }
    memset(chunk, 0, chunklen);
    memset(chunk, 0, chunklen);
    memset(chunk, 0, chunklen);
    gettimeofday(&t1, NULL);
    memset(chunk, 42, chunklen);
    gettimeofday(&t2, NULL);
    waitpid(pid, NULL, 0);
    printf("sec: %d us: %d\n", (int) t2.tv_sec - (int) t1.tv_sec, (int) t2.tv_usec - (int) t1.tv_usec);
    printf("-----\n");
	fflush(stdout);
    pid = fork();
    memset(chunk, 0, chunklen);
    memset(chunk, 0, chunklen);
    memset(chunk, 0, chunklen);
    gettimeofday(&t1, NULL);
    memset(chunk, 42, chunklen);
    gettimeofday(&t2, NULL);
	if(pid != 0)
		waitpid(pid, NULL, 0);
    printf("sec: %d us: %d\n", (int) t2.tv_sec - (int) t1.tv_sec, (int) t2.tv_usec - (int) t1.tv_usec);
	fflush(stdout);
    if(pid == 0)
		return 0;
    printf("-----\n");
	fflush(stdout);
    pid = fork();
	if(pid == 0)
	{
		memset(chunk, 0, 512*1024);
		memset(chunk, 0, 512*1024);
		memset(chunk, 0, 512*1024);
    	gettimeofday(&t1, NULL);
		for(int i = 0; i < 32; i++)
		{
			memset(chunk, 42, 512*1024);
			memset(chunk, 0, 512*1024);
		}
    	gettimeofday(&t2, NULL);
	}
	else
	{
    	memset(chunk, 0, chunklen);
    	memset(chunk, 0, chunklen);
    	memset(chunk, 0, chunklen);
    	gettimeofday(&t1, NULL);
    	memset(chunk, 42, chunklen);
    	gettimeofday(&t2, NULL);
	}
	if(pid != 0)
		waitpid(pid, NULL, 0);
    printf("sec: %d us: %d\n", (int) t2.tv_sec - (int) t1.tv_sec, (int) t2.tv_usec - (int) t1.tv_usec);
	fflush(stdout);
	return 0;
}
*/
