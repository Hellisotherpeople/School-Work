#include<Rectangle.h>
#include<iostream>

Rectangle::Rectangle()
{
	std::cout << "Initializing" << std::endl; 
}

Rectangle::Rectangle(int x, int y) : width(x), height(y)
{
	std::cout << "Initializing" << std::endl; 
}

int Rectangle::getWidth()
{
	return width;
}

int Rectangle::getHeight()
{
	return height;
}

int Rectangle::getArea()
{
	return width * height;
}
void Rectangle::draw()
{
    for(int i = 0; i < this->getRepeatNum(); i++){
        std::cout << "[]" << std::endl; 
    }
}