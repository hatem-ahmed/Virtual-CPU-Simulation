
void hpfpreaging(int PROCESS_COUNT) { 
	int seed = time(NULL); 
	srand(seed);
	Process* queue = ProcessQueue(PROCESS_COUNT); // generate random processes 
	sortByArrvial(queue, PROCESS_COUNT); // sort the process by the arrival time

	// Assign the id for each process
	int index;
	for (index = 0; index < PROCESS_COUNT; index++) {
		queue[index].id = (char)(65 + index);
		if (queue[index].id > 90) {
			queue[index].id += 6;
		}
	}
	sortByPriorityWithSameArrivalTime(queue, PROCESS_COUNT); // sort the processes again by the priority on the top of the arrvial time 

	
	
	int timeslice = 0; // quant time 
	int cur = 0; // cur process runing 
	int curDone = false;
	Stat stat = newStat();  
	

	while (cur != PROCESS_COUNT) {
		Quant* quant = (Quant*) malloc(sizeof(Quant)); // generate a quant slice 
		(*quant).sid = timeslice; // assgin the time to the quant
		if (queue[cur].arrival_time <= timeslice) { // get the first arrival process
			(*quant).pid = queue[cur].id;
			queue[cur].start = true; // mark the execution process 
			queue[cur].remaining_time -= 1.0f;
			if (queue[cur].remaining_time <= 0) { // process finished 
				queue[cur].finished_time += timeslice;
				queue[cur].turnaround_time = queue[cur].run_time + queue[cur].wait_time;
				// queue[cur].start = false;
				addJob(&stat, queue[cur]); // add process to the quant
				cur++;
				curDone = true;
			}

			// swap the cur process to the end of the arrvial queue
			int last;
			if (!curDone) {
				int i = cur + 1;
				int j;
				if (i == PROCESS_COUNT - 1) {
					last = i;
				}
				else {
						
						if (i < PROCESS_COUNT) {
							if (queue[i].arrival_time > timeslice + 1) {
							last = cur;
						}
						else {
							int br = false;
							for (i = cur + 1; i < PROCESS_COUNT; i++) {
								if (queue[i].arrival_time <= timeslice + 1) {
									continue;
								}
								else {
									last = i-1;
									br = true;
									break;
								}
							}
							if (!br) {
								last = PROCESS_COUNT - 1;
							}

						}
					}
				}
				Process temp = queue[cur]; 
				for (j = cur; j < last; j++) {
					queue[j] = queue[j+1];
				}
				queue[last] = temp; // put next to the end of the last arrvial process
			}
			else {
				curDone = false;
				int i = cur;
				int j;
				if (i == PROCESS_COUNT - 1) {
					last = i;
				}
				else {
						if (i < PROCESS_COUNT) {
							if (queue[i].arrival_time > timeslice + 1) {
							last = cur;
						}
						else {
							int br = false;
							for (i = cur; i < PROCESS_COUNT; i++) {
								if (queue[i].arrival_time <= timeslice +1) {
									continue;
								}
								else {
									last = i - 1;
									br = true;
									break;
								}
							}
							if (!br) {
								last = PROCESS_COUNT - 1;
							}
						}
					}
				}
				Process temp = queue[cur]; 
				for (j = cur; j < last; j++) {
					queue[j] = queue[j+1];
				}
				queue[last] = temp; // put next to the end of the last arrvial process
			}
			int j;
			bool swap = false;
			int min = cur;
			for (j = cur; j <= last; j++) { // find the highest priority process in the rest of the array
				// if (queue[j].arrival_time <= timeslice) {
					queue[j].wait_time += 1.0f;
					queue[j].age++; // add the age 
					if (queue[j].age == 5 && queue[j].priority > 1) { // decrease priority 
						queue[j].priority--;
					}
					if (!queue[j].start) { // update the response time for the process that has not be execuated
						queue[j].response_time += 1.0f;
					}
					if (queue[j].priority < queue[min].priority) {
						swap = true;
						min = j;
					}
				//}
			}
			if (swap) { // if found do the swap 
				Process temp = queue[min];
				queue[min] = queue[cur];
				queue[cur] = temp;
			}

		}
		else {
			(*quant).pid = '-';
		}
		addQuant(&stat, (*quant));
		timeslice++;

	}

	Process* pq = stat.process;
	int size = stat.pc;
	int size1 = 0;
	int size2 = 0;
	int size3 = 0;
	int size4 = 0;
	int i;

	float response_1 = 0.0f;
	float wait_1 = 0.0f;
	float turnaround_1 =0.0f;
	int startquant_1 = 0;
	int endquant_1 = 0;

	float response_2 = 0.0f;
	float wait_2 = 0.0f;
	float turnaround_2 =0.0f;
	int startquant_2 = 0;
	int endquant_2 = 0;

	float response_3 = 0.0f;
	float wait_3 = 0.0f;
	float turnaround_3 =0.0f;
	int startquant_3 = 0;
	int endquant_3 = 0;

	float response_4 = 0.0f;
	float wait_4 = 0.0f;
	float turnaround_4 =0.0f;
	int startquant_4 = 0;
	int endquant_4 = 0;


	for (i = 0; i < size; i++) {
		if (pq[i].priority == 1) {
			startquant_1 = i;
			break;
		}
	}

	for (i = 0; i < size; i++) {
		if (pq[i].priority == 2) {
			startquant_2 = i;
			break;
		}
	}

	for (i = 0; i < size; i++) {
		if (pq[i].priority == 3) {
			startquant_3 = i;
			break;
		}
	}

	for (i = 0; i < size; i++) {
		if (pq[i].priority == 4) {
			startquant_4 = i;
			break;
		}
	}

	for (i = 0; i < size; i++) {
		if (pq[i].priority == 1) {
			size1++;
			response_1 += pq[i].response_time;
			wait_1 += pq[i].wait_time;
			turnaround_1 += pq[i].turnaround_time;
			endquant_1 = i;
		}
		else if (pq[i].priority == 2) {
			size2++;
			response_2 += pq[i].response_time;
			wait_2 += pq[i].wait_time;
			turnaround_2 += pq[i].turnaround_time;
			endquant_2 = i;
		}
		else if (pq[i].priority == 3) {
			size3++;
			response_3 += pq[i].response_time;
			wait_3 += pq[i].wait_time;
			turnaround_3 += pq[i].turnaround_time;
			endquant_3 = i;
		}
		else {
			size4++;
			response_4 += pq[i].response_time;
			wait_4 += pq[i].wait_time;
			turnaround_4 += pq[i].turnaround_time;
			endquant_4 = i;

		}		

	}

	printf("~~HPF-PRE-AGING~~\n");
	printf ("Queue1\n");
	printf("Queue1 Average Wait Time: %.1f\n", wait_1/size1);
	printf("Queue1 Average Response Time: %.1f\n", response_1/size1);
	printf("Queue1 Average Turnaround Time: %.1f\n", turnaround_1/size1);
	printf("Queue1 Throughput: %.1f\n\n", ((float)size1)/(endquant_1 - startquant_1 + 1));
    printf ("Queue2\n");
	printf("Queue2 Average Wait Time: %.1f\n", wait_2/size2);
	printf("Queue2 Average Response Time: %.1f\n", response_2/size2);
	printf("Queue2 Average Turnaround Time: %.1f\n", turnaround_2/size2);
	printf("Queue2 Throughput: %.1f\n\n", ((float)size2)/(endquant_2 - startquant_2 + 1));
	printf ("Queue3\n");
	printf("Queue3 Average Wait Time: %.1f\n", wait_3/size3);
	printf("Queue3 Average Response Time: %.1f\n", response_3/size3);
	printf("Queue3 Average Turnaround Time: %.1f\n", turnaround_3/size3);
	printf("Queue3 Throughput: %.1f\n\n", ((float)size3)/(endquant_3 - startquant_3 + 1));
	printf("Queue4 Average Wait Time: %.1f\n", wait_4/size4);
	printf("Queue4 Average Response Time: %.1f\n", response_4/size4);
	printf("Queue4 Average Turnaround Time: %.1f\n", turnaround_4/size4);
	printf("Queue4 Throughput: %.1f\n\n", ((float)size4)/(endquant_4 - startquant_4 + 1));

	printStat(stat);
	printf("\n");

}



