#include <stdio.h>
#include <string.h>
#include "FCFS.h"
#include "RoundRobin.h"
#include "STRF.h"
#include "sjf-f.c"
#include "hpf-pre.c"
#include "HPF.c"
#include "hpfpreaging.c"
//#include <stdbool.h>


int main()
{

    int jobs = 0;
	int input = 0;
	int error = 0;


	printf("\nHow many random processes you want to generate?\n");
	scanf("%d", &jobs);


	printf("(1)FCFS \n");
	printf("(2)SJF\n");
	printf("(3)SRT\n");
	printf("(4)RR\n");
	printf("(5)HPF preemtive\n");
	printf("(6)HPF non-preemptive\n");
	printf("(7)HPF preemtive-aging\n");
	printf("(8)All\n");
	printf("(9)Exit\n");
	scanf("%d", &input);

	switch(input)
	{
		case 1:
			FCFS(jobs);
			break;
		case 2:
			sjf(jobs);
			break;
		case 3:
			SRT(jobs);
			break;
		case 4:
			RoundRobin(jobs);
			break;
		case 5:
			hpfpre(jobs);
			break;
		case 6:
			HPF(jobs);
			break;
		case 7:
			hpfpreaging(jobs);
			break;
		case 8:
			printf("\n\n~~ Shortest Remaining Time ~~\n\n");
			SRT(jobs);
			printf("\n\n~~ Shortest Remaining Time END ~~\n\n");
			printf("\n\n~~ First Come First Serve ~~\n\n");
			FCFS(jobs);
			printf("\n\n~~ First Come First Serve END ~~\n\n");
			printf("\n\n~~ Shortest Job First ~~");
			sjf(jobs);
			printf("\n\n~~ Shortest Job First END ~~\n\n");
			printf("\n\n~~ Highest Priority First (with preemption) ~~\n\n");
			hpfpre(jobs);
			printf("\n\n~~ Highest Priority First (with preemption) END ~~\n\n");
			printf("\n\n~~ Highest Priority First (with preemption and aging) ~~\n\n");
			hpfpreaging(jobs);
			printf("\n\n~~ Highest Priority First (with preemption and aging) END ~~\n\n");
			printf("\n\n~~ Highest Priority First (without preemption) ~~\n\n");
			HPF(jobs);
			printf("\n\n~~ Highest Priority First (without preemption) END ~~\n\n");
			printf("\n\n ~~ Round Robin ~~\n\n");
			RoundRobin(jobs);
			printf("\n\n ~~ Round Robin END ~~\n\n");
			break;

   		default:
			printf("error in choice\nexiting\n");
	}
	return 0;
}
