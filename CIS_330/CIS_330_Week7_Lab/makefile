prog: main.o Rectangle.o Shape.o Symbol.o
	g++ -o lab7 main.o Rectangle.o Shape.o Symbol.o

main.o: main.C Rectangle.o Shape.o Symbol.o
	g++ -c -I. main.C

Rectangle.o: Rectangle.C Rectangle.h Shape.o Symbol.o
	g++ -c -I. Rectangle.C

Shape.o: Shape.C Shape.h
	g++ -c -I. Shape.C

Symbol.o: Symbol.C Symbol.h
	g++ -c -I. Symbol.C
