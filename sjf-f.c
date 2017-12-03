 #include "Stat.c"
 #include <time.h> 
 #include <stdbool.h>

void sjf(int PROCESS_COUNT) {
	int seed = time(NULL); 
	srand(seed);
	Process* queue = ProcessQueue(PROCESS_COUNT);
	sortByArrvial(queue, PROCESS_COUNT);
	// assign the id for each process 
	int index;
	for (index = 0; index < PROCESS_COUNT; index++) {
		queue[index].id = (char)(65 + index);
		if (queue[index].id > 90) {
			queue[index].id += 6;
		}
	}
	/*
	for (index = 0; index < PROCESS_COUNT; index++) {
		printf("ID: %c | Arrival: %d | Runtime: %d\n", queue[index].id, queue[index].arrival_time, queue[index].run_time);
	}
	*/

	int timeslice = 0;
	int cur = 0;
	// bool Done = false;
	Stat stat = newStat();
	bool curDone = false;

	while (cur != PROCESS_COUNT) {
		Quant* quant = (Quant*) malloc(sizeof(Quant));
		(*quant).sid = timeslice;
		if (queue[cur].arrival_time <= timeslice) { // find the first arrvial job
			(*quant).pid = queue[cur].id;
			 queue[cur].remaining_time -= 1.0f;
			if (queue[cur].remaining_time <= 0) {
				queue[cur].turnaround_time = queue[cur].run_time + queue[cur].wait_time;
				queue[cur].finished_time += timeslice;
				addJob(&stat, queue[cur]);
				cur++;
				curDone = true;
			}
			int j;
			int next;
			int k;
			if (curDone) {
				next = cur;
				curDone = false;
			}
			else {
				next = cur + 1;
			}
			// int next = cur + 1; 
			int next_min = next;
			int swap1 = false; // find the next shortest job in the rest of the array
			int swap2 = false;
			for (j = next; j < PROCESS_COUNT; j++) {
				if (queue[j].arrival_time <= timeslice) {
					queue[j].wait_time += 1.0f;
					queue[j].response_time += 1.0f;
					if (queue[j].run_time < queue[next_min].run_time) {
						swap1 = true;
						next_min = j;
					}
				}	
			}
			if (swap1) { // if found, do the swap 
				Process temp = queue[next_min];
				queue[next_min] = queue[next];
				queue[next] = temp;
			} 
			for (k = next; k < PROCESS_COUNT; k++) { // find the earliest arrvial time 
				if (queue[k].arrival_time <= timeslice) {
					if (queue[k].run_time == queue[next].run_time && queue[k].arrival_time < queue[next].arrival_time) {
						next_min = k;
						swap2 = true;
					}
				}

			}
			if (swap2) { 
				Process temp = queue[next_min];
				queue[next_min] = queue[next];
				queue[next] = temp;
			}

		}
		else {
			(*quant).pid = '-';
		}
		addQuant(&stat, (*quant));
		timeslice++;
	}
	//free(queue);
	printf("\n"); 
	printf("~~SJF~~\n");
	printStat(stat);
	printf("\n");

}
