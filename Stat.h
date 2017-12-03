typedef struct {
	char pid; // process id
	int sid; // time slice id 

}Quant;


typedef struct {

	int pc;  // # of processes 
	int sc;  // # of quant count
	Process* process; // process array 
	Quant* quant; // quant array
}Stat;