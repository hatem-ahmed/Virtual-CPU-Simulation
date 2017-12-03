all:    main.c FCFS.h FCFS.c STRF.c STRF.h RoundRobin.h
	gcc -std=c99 -o P2 main.c FCFS.c STRF.c RoundRobin.c -lm

clean:
	rm -rf *.o *~ P2 core

