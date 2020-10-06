all: master worker

master: master.c
	mpicc -o master master.c

worker: worker.c
	mpicc -o worker worker.c
