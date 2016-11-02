CFLAGS=-W -Wall -g 

all: th2

clean:
	rm -f *.o th2

th2: th2.o p1fxns.o
	gcc -o th2 th2.o p1fxns.o 

th2.o: th2.c 
p1fxns.o: p1fxns.h p1fxns.c
