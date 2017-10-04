#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <wait.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define MAX_PASSENGER 100
#define MAX_PASSENGER_IN_TRAIN 5
#define MAX_TICKET 20
#define MAX_TRAIN_THREAD 5
#define MIN_START_TRAIN 10

void *ticket_thread(void *);
void *train_thread(void *);

// person == ticket
pthread_mutex_t gTicketMutex = PTHREAD_MUTEX_INITIALIZER;	// controls people in platform 
int gTicket[MAX_TICKET]; 		// total people in platform
int gTicketIn;					// total number of people which has got in platform
int gTicketOut;					// total number of people which has left platform

sem_t gStartTrainSem;			// train: waits until 10 people got in platform
sem_t gInAvailableSem;			// person enters platform while platform has less than 20 people
sem_t gOutAvailableSem;			// person leaves platform

pthread_t gTicketThread;
pthread_t gTrainThread[MAX_TRAIN_THREAD];
int gTicketThreadID;
int gTrainThreadID[MAX_TRAIN_THREAD];
int main(void)
{
	int i;

	/* TODO: initialize mutex */

	/* TODO: initialize semaphore */
	sem_init(&gStartTrainSem, 0, 0);
	sem_init(&gInAvailableSem, 0, MAX_TICKET);
	sem_init(&gOutAvailableSem, 0, 0);

	/* TODO: create threads */
	for(i = 0; i < 5; i++)
	{
		pthread_create(&gTrainThread[i], NULL, train_thread, i);
	}
	pthread_create(&gTicketThread, NULL, ticket_thread, NULL);

	pthread_join(gTrainThread[0], NULL);
	pthread_join(gTrainThread[1], NULL);
	pthread_join(gTrainThread[2], NULL);
	pthread_join(gTrainThread[3], NULL);
	pthread_join(gTrainThread[4], NULL);
	pthread_join(gTicketThread, NULL);

	pthread_exit(0);
}

void *ticket_thread(void *data)
{
    /* TODO: add code here */
	int i;
	int arg = (int)((void*)data);
	int timer;

	srand(time(NULL));
	for(i = 0; i < MAX_PASSENGER; i++)
	{
		if((gTicketIn - gTicketOut) < MAX_TICKET)
		{
			printf("ticket: passenger %d got ticket\n", i+1);
			timer = 300000 + rand()%200000;
			usleep(timer); // 0.3~0.5
			sem_wait(&gInAvailableSem);
			pthread_mutex_lock(&gTicketMutex);
			gTicket[i%MAX_TICKET] = i+1;
			gTicketIn++;
			pthread_mutex_unlock(&gTicketMutex);
			sem_post(&gOutAvailableSem);
			if(gTicketIn >= MIN_START_TRAIN)
			{
				sem_post(&gStartTrainSem);
			}
			if(gTicketIn == MIN_START_TRAIN)
			{
				sleep(1);
			}
		}
		else
		{
			i--;
		}
	}
}

void *train_thread(void *data)
{
    /* TODO: add code here */
	int i, j, num = 100;
	int* saveArr;
	int sum = 0;
	int arg = (int)((void*)data);
	int sw = 0;

	printf("======> train %d: wait\n", arg);

	while(1)
	{

		for(i = 0; i < MAX_PASSENGER_IN_TRAIN && gTicketIn != gTicketOut; i++)
		{
			if(sw == 0 && !sem_wait(&gStartTrainSem))
			{
				sw = 1;
				printf("======> train %d: ready\n", arg);
				i--;
				continue;
			}
			printf("======> train %d: passenger %d returned ticket\n", arg, gTicketOut+1);
			sem_wait(&gOutAvailableSem);
			pthread_mutex_lock(&gTicketMutex);
			for(j = 0; j < 20; j++)
			{
				if(num > gTicket[j] && gTicket[j] > 0)
				{
					num = gTicket[j];
					saveArr = &gTicket[j];
				}
			}
			*saveArr = 0;
			gTicketOut++;
			sum++;
			pthread_mutex_unlock(&gTicketMutex);
			sem_post(&gInAvailableSem);
		}
		if(i > 0)
		{
			printf("======> train %d: start with %d passengers\n", arg, i);
			sleep(5);
		}
		
		if(gTicketOut >= MAX_PASSENGER)
		{
			printf("======> train %d: stop\n", arg);
			printf("======> train %d: exit (total %d passengers)\n", arg, sum);
			break;
		}
	}
}
