CFLAGS=-W -Wall -g 

all: th3

clean:
	rm -f *.o th3

th3: th3.o p1fxns.o
	gcc -o th3 th3.o p1fxns.o 

th3.o: th3.c 
p1fxns.o: p1fxns.h p1fxns.c
