CC=gcc    #use C compiler 
IDIR=./include ##Generic include directory 
LDIR=./lib #Generic lib directory 
TRIG=trig/cos330.o trig/sin330.o trig/tan330.o trig/arcsin330.o trig/arccos330.o trig/arctan330.o 
TRIG2=cos330.o sin330.o tan330.o arcsin330.o arccos330.o arctan330.o 
EXP=exp/exp330.o exp/log330.o 
EXP2=exp330.o log330.o
HEADER=math330.h


all: foo dirs cli/cli.c
	$(CC) -o mycli cli/cli.c -I$(IDIR) -L$(LDIR) -lmath330 -lm

dirs: 
	mkdir -p $(IDIR)
	cp $(HEADER) $(IDIR) 
	mkdir -p $(LDIR) 	


foo: cos330.o sin330.o tan330.o arcsin330.o arccos330.o arctan330.o exp330.o log330.o	
	ar r libmath330.a $(TRIG2) $(EXP2) 
	cp libmath330.a $(LDIR)
	cp $(HEADER) $(IDIR)
	
cos330.o: trig/cos330.c 
	$(CC) -c -I$(IDIR) trig/cos330.c -lm

sin330.o: trig/sin330.c
	$(CC) -c -I$(IDIR) trig/sin330.c -lm

tan330.o: trig/tan330.c
	$(CC) -c -I$(IDIR) trig/tan330.c -lm

arcsin330.o: trig/arcsin330.c
	$(CC) -c -I$(IDIR) trig/arcsin330.c -lm

arccos330.o: trig/arccos330.c 
	$(CC) -c -I$(IDIR) trig/arccos330.c -lm

arctan330.o: trig/arctan330.c 
	$(CC) -c -I$(IDIR) trig/arctan330.c -lm 

exp330.o: exp/exp330.c
	$(CC) -c -I$(IDIR) exp/exp330.c -lm
	
log330.o: exp/log330.c 
	$(CC) -c -I$(IDIR) exp/log330.c -lm
	


