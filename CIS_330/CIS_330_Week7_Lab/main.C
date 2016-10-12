#include<Shape.h>
#include<Rectangle.h>
#include<Symbol.h> 
#include<iostream>

int main(){
    Rectangle r(10,20);
    
    Shape *s = &r;
    
    Symbol *sym = &r; 
    sym->setRepeatNum(3);
    
    std::cout << s->getArea() << std::endl;
    std::cout << r.getWidth() << std::endl;
    std::cout << r.getHeight() << std::endl; 
    
}