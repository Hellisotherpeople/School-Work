#ifndef RECTANGLE_H
#define RECTANGLE_H

//Need 2 include statements here...
#include<Shape.h>
#include<Shape.C> 
#include<Symbol.h> 
#include<Symbol.C>

//To multiply-inherit, use the notation
//class Rectangle : baseClass1, baseClass2
class Rectangle : Shape, Symbol
{

	private:
		int width;
		int height;

	public:
		Rectangle();
		Rectangle(int, int);
		int getWidth();
		int getHeight();
		int getArea();
                void draw();
};

#endif
