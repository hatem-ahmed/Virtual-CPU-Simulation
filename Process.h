typedef struct {
	char id; // A-Za-z
	int priority; // 1-4
	int age; // extra credit, for bumping the priority 
	int finished_time; // match with each quanta e.g 1, 2, 3... 99
	//float arrival_time; // 0-99
	//float run_time; // 0.1-10
	int arrival_time;
	int run_time;
	float response_time; 
	float wait_time;
	float turnaround_time;
	float remaining_time;
	//bool finished;
	int start; // for calcluating the response time of the hpf 
} Process; 