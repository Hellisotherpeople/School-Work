CFLAGS=-W -Wall -g 

all: th4

clean:
	rm -f *.o th4

th4: th4.o p1fxns.o
	gcc -o th4 th4.o p1fxns.o 

th4.o: th4.c 
p1fxns.o: p1fxns.h p1fxns.c
