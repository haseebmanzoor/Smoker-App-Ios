#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_THREADS 3
typedef void *(*smokers_t)(void *);
sem_t waits[3];
sem_t agent;

void *A_smoker(void* arg)
{
	while (true)
	{
		sleep(1);
		printf("Smoker A waiting to smoke with paper.....\n");

		sem_wait(&waits[0]);
		printf("Smoker A received matches and tobacco. Making Cigaratte\n");
		sem_post(&agent);
	}
	return NULL;
}
void* B_smoker(void* arg)
{
	while (true)
	{
		sleep(2);
		printf("Smoker B waiting to smoke with macth sticks....\n");
		sem_wait(&waits[1]);
		printf("Smoker A received matches and tobacco. Making Cigaratte\n");
		sem_post(&agent);
	}
	return NULL;
}
void* C_smoker(void* arg)
{
	while (true)
	{
		//sleep(3);
		printf("Smoker C waiting to smoke has tobacco\n");

		sem_wait(&waits[2]);  
		printf("Smoker A received matches and tobacco. Now making cigarette.\n");
		sem_post(&agent);
	}
	return NULL;
}
int main(int argc, char* arvg[])
{	
	srand(time(NULL));
	sem_init(&agent, 0, 1);
	pthread_t smoker_threads[3];

	smokers_t smoker_functions[3] = { A_smoker, B_smoker, C_smoker };

	for (int i = 0; i < NUM_THREADS; ++i)
	{
		sem_init(&waits[i], 0, 0);
		pthread_create(&smoker_threads[i], NULL, smoker_functions[i], NULL);
	}
	while (true)
	{
		sem_wait(&agent);
	
		sem_post(&waits[rand() % 2]);
	}
	for (int i = 0; i < NUM_THREADS; ++i)
	{
		pthread_join(smoker_threads[i], NULL);
	}

	return 0;
}
