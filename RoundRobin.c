#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <math.h>

#define DEBUG 1
unsigned int num_processes = 50;
float total_time_taken = 0;

struct Process
{
	int id;
	float arrival_time;
	float total_runtime;
	float total_runtime_backup;
	int priority;
	float turnaround_time;
	float waiting_time;
	float finishing_time;
	float response_time;
}*p;

struct CircularQueue
{
	struct Process *current;
	struct CircularQueue *next;
	struct CircularQueue *prev;
}*head,*temp_q,*rotation,temp_save;

void GenerateProcess1(int display)
{
	int i;
	//for all processes, randomize their values
	for(i = 0; i< num_processes; i++)
	{
		p[i].id = i;
		p[i].arrival_time = rand()%100;
		p[i].total_runtime_backup = p[i].total_runtime = (rand()%100+1)/10.0;
		p[i].priority = rand()%4+1;
		p[i].waiting_time = 0;
		p[i].turnaround_time = 0;
	}

	//print generated values if display is checked
	printf("\ngenerated simulation\n\n");
	if(display)
		for(i = 0; i< num_processes; i++)
		{
			printf("id = %d\t",p[i].id);
			printf("arrival_time = %0.1f\t",p[i].arrival_time);
			printf("total_runtime = %0.1f\t",p[i].total_runtime);
			printf("priority = %d\n",p[i].priority);
		}
}
void SwapProcess(int i,int j)
{
	//swap a process structure with another
	struct Process temp_p;
	temp_p = p[i];
	p[i] = p[j];
	p[j] = temp_p;
}
void SortProcess(int display)
{
	int i,j,min;

	//sort processes by arrival time in ascending order
	for(i = 0; i<num_processes; i++)
	{
		min = i;
		for(j = i; j<num_processes; j++)
		{
			if(p[j].arrival_time < p[min].arrival_time)
				min = j;
		}
			SwapProcess(i,min);
	}

	//sort processes by priority in ascending order, only for similar arrival times
	for(i = 0; i<num_processes; i++)
	{
		for(j = i+1; j<num_processes; j++)
		{
			if(p[i].arrival_time == p[j].arrival_time && p[i].priority > p[j].priority)
			{
				SwapProcess(i,j);
			}
		}
	}

	printf("\nsorted processes based on arrival time and priority\n\n");
	//display sorted processes if display var is checked
	if(display)
		for(i = 0; i< num_processes; i++)
		{
			printf("id = %d\t",p[i].id);
			printf("arrival_time = %0.1f\t",p[i].arrival_time);
			printf("total_runtime = %0.1f\t",p[i].total_runtime);
			printf("priority = %d\n",p[i].priority);
		}
}
void ExecuteProcessQueue(int display)
{
	unsigned int quanta,i,ProcessCounter,set;

	//initializing head of circular queue
	head = malloc(sizeof(struct CircularQueue));
	if(head == 0)
	{
		printf("error in malloc'ing head");
		return ;
	}

	//execution of quantum time
	printf("\nExecuting Process Queue\n\n");
	for(quanta = 0; quanta<=100 || head->current != 0 ;quanta++,total_time_taken++)
	{

		//New Process (if)Arrival to Circular Queue
		for(ProcessCounter = 0; ProcessCounter < num_processes; ProcessCounter++)
		{
			if(p[ProcessCounter].arrival_time <= quanta)
			{
				if(head->current == 0)
				{
					//if head of Queue points to nothing, initialize with latest process arrival
					head->current = &p[ProcessCounter];
					head->prev = head;
					head->next = head;
					rotation = head;
				}
				else
				{
					//if head is initialized, loop until end of Queue is found
					temp_q = head;
					while(temp_q->next != head)
						temp_q = temp_q->next;

					//allocate new memory for new process arrival
					temp_q->next = malloc(sizeof(struct CircularQueue));
					if(temp_q->next == 0)
					{
						printf("error in malloc");
						return ;
					}
					//update the linked list
					temp_q->next->prev = temp_q;
					temp_q->next->current = &p[ProcessCounter];
					temp_q->next->next = head;
					head->prev = temp_q->next;
				}

				//print arrival details, if display is checked
				if(display)
					printf("\nnew arrival of pid : %d at quanta : %d for %0.1f\n",p[ProcessCounter].id,quanta,p[ProcessCounter].total_runtime);

				//once process arrives, its arrival time is increased by a magic number
				//to ensure, it doesn't get submitted to queue again
				p[ProcessCounter].arrival_time += 10000.0;

				//Chart Process's response time
				p[ProcessCounter].response_time = quanta;

				//printing existing queue if display is checked
				if(display)
				{
					printf("printing queue : \n");
					temp_q = head;
					do
					{
						printf("entry : %d\n",temp_q->current->id);
						temp_q = temp_q->next;
					}while(temp_q != head);
				}
			}
		}

		//Core Round Robin implementation
		if(head->current != 0 && rotation != 0)
		{
			printf("quanta -> %d : \texecuting pid : %d\ttime left : %0.1f\n",quanta,rotation->current->id,rotation->current->total_runtime);

			rotation->current->total_runtime -= 1;

			//if runtime of a process after computation reaches 0
			//delete the process from queue and join previous and next elements

			if(rotation->current->total_runtime <= 0)
			{
				temp_q = rotation;
				if(rotation->prev == rotation && rotation->next == rotation)
				{
					rotation = 0;
				}
				else if(rotation->next == rotation->prev)
				{
					rotation = rotation->next;
					rotation->next = rotation;
					rotation->prev = rotation;
				}
				else
				{
					rotation->next->prev = rotation->prev;
					rotation->prev->next = rotation->next;
					rotation = rotation->next;
				}

				if(temp_q == head)
				{
					head = rotation;
					if(head == 0)
					{
						head = malloc(sizeof(struct CircularQueue));
						head->current = 0;
						rotation = head;
					}
				}
				if(display)
					printf("free'ing %d with arrival time %0.1f for run time %0.1f\n",temp_q->current->id,temp_q->current->arrival_time-10000.0,temp_q->current->total_runtime);

				//update process's waiting and turnaround time during its termination
				temp_q->current->waiting_time = fabsf(floorf(quanta - temp_q->current->total_runtime_backup - (temp_q->current->arrival_time - 10000.0)));
				temp_q->current->turnaround_time = quanta - (temp_q->current->arrival_time - 10000.0) + 1;
				temp_q->current->finishing_time = quanta;
				free(temp_q);
			}

			
			//round robin rotation, if 2 or more than 2 elements are in the queue
			if(head->current != 0 && rotation != rotation->next)
			{
				if(display)
					printf("rotation done from %d -> %d\n",rotation->current->id,rotation->next->current->id);
				rotation = rotation->next;
			}

		}
		else
			printf("quanta -> %d finished [empty]\n",quanta);
	}
	printf("\n\nend of simulation\n");
}

void Stats(int display)
{
	int i;
	float avg_turnaround_time = 0;
	float avg_waiting_time = 0;
	float avg_response_time = 0;
	for(i = 0; i< num_processes; i++)
	{
		if(display)
		{
			printf("p[%d] -> turnaround time : %0.1f\n",i,p[i].turnaround_time);
			printf("p[%d] -> waiting time : %0.1f\n",i,p[i].waiting_time);
			printf("p[%d] -> response time : %0.1f\n\n",i,p[i].response_time);
		}

		//average computation
		avg_turnaround_time += p[i].turnaround_time;
		avg_waiting_time += p[i].waiting_time;
		avg_response_time += p[i].response_time;
	}
	avg_turnaround_time /= num_processes;
	avg_waiting_time /= num_processes;
	avg_response_time /= num_processes;

	//stats display
	printf("average turnaround time : %0.1f\n",avg_turnaround_time);
	printf("average waiting time : %0.1f\n",avg_waiting_time);
	printf("average response time : %0.1f\n",avg_response_time);
	printf("total quanta : %0.1f\n",total_time_taken);
	printf("total number of processes : %d\n",num_processes);
	printf("throughput : %0.2f\n",100*num_processes/total_time_taken);
}

int RoundRobin(unsigned int n)
{
	
	num_processes = n;
	p = malloc(num_processes * sizeof(struct Process));
	
	//time seed for random, /dev/urandom can be used for true randomness
	srand(time(0));

	//generate random values for processes
	GenerateProcess1(DEBUG);

	//sort generated processes
	SortProcess(0);

	//execute processes using a circular linked list for RoundRobin
	ExecuteProcessQueue(0);

	//computing average times for stats
	Stats(0);
	return 1;
}
