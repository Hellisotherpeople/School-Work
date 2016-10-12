
FLAGS = -g -std=c++0x

all: prettyMemo prettyIter

%.o : %.cpp
	g++ -c $< $(FLAGS) 

prettyMemo: prettyMemo.o
	g++ -o $@ prettyMemo.o $(FLAGS)

prettyIter: prettyIter.o
	g++ -o $@ prettyIter.o $(FLAGS)
clean:
	$(RM) *.o prettyMemo prettyIter 
