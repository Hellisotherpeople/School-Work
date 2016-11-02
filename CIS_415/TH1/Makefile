CFLAGS=-W -Wall -g 

all: th1

clean:
	rm -f *.o th1

th1: th1.o p1fxns.o
	gcc -o th1 th1.o p1fxns.o 

th1.o: th1.c 
p1fxns.o: p1fxns.h p1fxns.c
