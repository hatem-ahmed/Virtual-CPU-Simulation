#include <stdlib.h>
#include "Process.h"

float float_rand(float min, float max) {
    float scale = rand() / (float) RAND_MAX; // [0, 1.0] 
    return min + scale * (max - min);      //[min, max] 
}

int int_rand(int min, int max) {
	return min + (rand() % (max - min + 1));
}

// generate a rnadom process 
Process GenerateProcess() {
	Process* p = (Process*) malloc(sizeof(Process));
	(*p).age = 0; // start at 0 
	// (*p).arrival_time = float_rand(0, 99); // 0-99
    (*p).arrival_time = int_rand(0, 99);
	//(*p).run_time = float_rand(0.1, 10); // 0.1-10
	(*p).run_time = int_rand(1, 10);
	(*p).priority = int_rand(1, 4); // 1-4
	(*p).remaining_time = (*p).run_time; 
	(*p).finished_time = 0; // initilaize 0 at the beginning 
	/*
	(*p).response_time = 1.0f - ((*p).arrival_time - ((int) (*p).arrival_time)); 
	(*p).wait_time = 1.0f - ((*p).arrival_time - ((int) (*p).arrival_time));
	(*p).turnaround_time = 1.0f - ((*p).arrival_time - ((int) (*p).arrival_time));
	*/
	(*p).response_time = 0; 
	(*p).wait_time = 0;
	(*p).turnaround_time = 0;
	(*p).start = 0;
	// (*p).finished = false;

	return (*p);
}

// make a random process queue 
Process* ProcessQueue(int size) {
	Process* pq = (Process*) malloc(size * sizeof(Process)); 
	int i; 
	for (i = 0; i < size; i++) {
		pq[i] = GenerateProcess();
	}
	return pq;
}


void swap(Process *px, Process *py) {
	Process temp = *px;
	*px = *py;
	*py = temp;
}

// Selection sort
void sortByArrvial(Process* pq, int size) {
	int i, j, min;
	for (i = 0; i < size - 1; i++) {
		min = i;
		for (j = i + 1; j < size; j++) {
			if (pq[j].arrival_time < pq[min].arrival_time) {
				min = j;
			}
		}
		swap(&pq[min], &pq[i]);
	}
}

// sort according to the priority 
void sortByPriority(Process* pq, int start, int size) {
	int i, j, min;
	for (i = start; i < start + size - 1; i++) {
		min = i;
		for (j = i + 1; j < start + size; j++) {
			if (pq[j].priority < pq[min].priority) {
				min = j;
			}
		}
		swap(&pq[min], &pq[i]);
	}
}

// for the hpf, bucket sort. for the same arrival time sort the processes by the priority
void sortByPriorityWithSameArrivalTime(Process* pq, int size) {
	int right = 0;
	int left; 
	int count = 1; 
	int pre = pq[0].arrival_time;
	for (left = 1; left < size; ) {
		if (pre == pq[left].arrival_time) {
			count++;
			left++;
		}
		else {
			sortByPriority(pq, right, count);
			count = 1;
			right = left;
			pre = pq[right].arrival_time;
			left++;

		}
		sortByPriority(pq, right, count);

	}


}

/*
void sortByRun(Process* pq, int size) {
	int i, j , min;
	for (i = 0; i < size - 1; i++) {
		min = i;
		for (j = i + 1; j < size; j++) {
			if (pq[j].run_time , pq[min].run_time) {
				min = j;
			}
		}
		swap(&pq[min], &pq[i]);
	}

}
*/