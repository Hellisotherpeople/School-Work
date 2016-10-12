/* This file should contain your struct definitions for Circle, Triangle, and 
   Rectangle */
typedef struct 
{
    double minX;
    double minY; 
    double maxX; 
    double maxY; 
} Rectangle;

typedef struct  
{ 
    double radius; 
    double origin; 
    double originY; 
} Circle;

typedef struct 
{ 
    double pt1X;
    double pt2X;
    double minY;
    double maxY;
} Triangle;

struct Shape; 

typedef struct
{
    double(*GetArea)(struct Shape*); // function pointer, return a double, is called GetArea, returns a shape  
    void (*GetBoundingBox)(struct Shape*, double *); 
} FunctionTable;


typedef union
{
    Circle circle; 
    Rectangle rectangle; 
    Triangle triangle; 
} ShapeUnion;

typedef enum
{
    Circleshape,
    Rectangleshape, 
    Triangleshape
} ShapeType;


struct Shape 
{
    ShapeUnion shapeunion; 
    ShapeType shapetype; 
    FunctionTable ft;
}; 

