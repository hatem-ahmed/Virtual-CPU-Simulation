#include <stdlib.h>
#include <stdio.h>
#include "ProcessQueue.c"
#include "Stat.h"

#define TABLE_SIZE 20

Stat newStat() {
	Stat* s = (Stat*) malloc(sizeof(Stat));
	return (*s);
}


// add a Proceess 
void addJob(Stat* s, Process ps) {
	(*s).pc = (*s).pc + 1;
	int size = (*s).pc;
	Process* p = (Process*) malloc(sizeof(Process) * size);
	int i;
	for(i = 0; i < size - 1; i++) {
		p[i] = (*s).process[i];
	}
	p[size-1] = ps;
	(*s).process = p;
}


// add a Quant, same as add a time slot 
void addQuant(Stat* s, Quant qt) {
	(*s).sc = (*s).sc + 1;
	int size = (*s).sc;
	Quant* q = (Quant*) malloc(sizeof(Quant) * size);
	int i;
	for(i = 0; i < size - 1; i++) {
		if((*s).quant != 0)
			q[i] = (*s).quant[i];
	}
	q[size-1] = qt;
	(*s).quant = q;
}

// print the stats 
void printStat(Stat s) {
	printf(" Pid | Arrival_time | Priority | Run_time | Response_time | Wait_time | Turnaround_time | Finshed_time\n");
	// printf("\n");
	float total_response = 0.0f;
	float total_wait = 0.0f;
	float total_turnaround = 0.0f;
	int i;
	for (int i = 0; i < s.pc; i++) {
		total_turnaround += s.process[i].turnaround_time;
		total_wait +=s.process[i].wait_time;
		total_response += s.process[i].response_time;
		printf(" %3c | %12.1d | %8d | %8.1d | %13.1f | %9.1f | %15.1f | %12d \n", s.process[i].id, s.process[i].arrival_time, s.process[i].priority, s.process[i].run_time, s.process[i].response_time, s.process[i].wait_time, s.process[i].turnaround_time, s.process[i].finished_time);
	}

	 int base;
    for(base = 0; base < s.sc; base = base + TABLE_SIZE)
    {
        printf("-----------+");
        for(i = 0; base + i < s.sc && i < TABLE_SIZE; i++)
        {
            printf("-----+");
        }
        printf("\n");
        printf(" QuantSlice|");
        for(i = 0; base + i < s.sc && i < TABLE_SIZE; i++)
        {
            printf(" %3d |", s.quant[base + i].sid);
        }
        printf("\n");
        printf("   Process |");
        for(i = 0; base + i < s.sc && i < TABLE_SIZE; i++)
        {
            printf(" %3c |", s.quant[base + i].pid);
        }
        printf("\n");
        printf("-----------+");
        for(i = 0; base + i < s.sc && i < TABLE_SIZE; i++)
        {
            printf("-----+");
        }
        printf("\n");
    }

    printf("Average Wait: %.1f\n", total_wait/s.pc);
    printf("Average Response: %.1f\n", total_response/s.pc);
    printf("Average Turnaround: %.1f\n", total_turnaround/s.pc);
    printf("Throughput: %.1f processes per 100 quanta\n", 100 * ((float) 50.0) / s.sc);

}


