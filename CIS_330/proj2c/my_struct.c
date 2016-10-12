/* This file should contain the 9 functions defined in prototypes.h */

#include <prototypes.h>

void InitializeRectangle(struct Shape* shape, double minX, double maxX, double minY, double maxY)
{
 //Rectangle t;
    /*
 rectangle->minX = minX; 
 rectangle->minY = minY;
 rectangle->maxX = maxX; 
 rectangle->maxY = maxY; 
    */
    
    shape->shapeunion.rectangle.minX = minX;
    shape->shapeunion.rectangle.minY = minY; 
    shape->shapeunion.rectangle.maxX = maxX;
    shape->shapeunion.rectangle.maxY = maxY; 
    shape->ft.GetArea = GetRectangleArea;
    shape->ft.GetBoundingBox = GetRectangleBoundingBox;
    
}

double GetRectangleArea(struct Shape* shape)
{
    return ((shape->shapeunion.rectangle.maxX - shape->shapeunion.rectangle.minX) * (shape->shapeunion.rectangle.maxY - shape->shapeunion.rectangle.minY));
}

void GetRectangleBoundingBox(struct Shape * shape, double * Bbox)
{
    Bbox[0] = shape->shapeunion.rectangle.minX;
    Bbox[1] = shape->shapeunion.rectangle.maxX;
    Bbox[2] = shape->shapeunion.rectangle.minY; 
    Bbox[3] = shape->shapeunion.rectangle.maxY;
}


void InitializeCircle(struct Shape * shape, double radius, double origin, double originY)
{
    shape->shapeunion.circle.radius = radius; 
    shape->shapeunion.circle.origin = origin; 
    shape->shapeunion.circle.originY = originY;
    shape->ft.GetArea = GetCircleArea;
    shape->ft.GetBoundingBox = GetCircleBoundingBox;
}

double GetCircleArea(struct Shape * shape)
{
    return ((3.14159 * shape->shapeunion.circle.radius * shape->shapeunion.circle.radius));
}


void GetCircleBoundingBox(struct Shape* shape, double * Bbox)
{
    Bbox[0] = (shape->shapeunion.circle.origin - shape->shapeunion.circle.radius); 
    Bbox[1] = (shape->shapeunion.circle.origin + shape->shapeunion.circle.radius);
    Bbox[2] = (shape->shapeunion.circle.originY - shape->shapeunion.circle.radius);
    Bbox[3] = (shape->shapeunion.circle.originY + shape->shapeunion.circle.radius); 
}

void InitializeTriangle(struct Shape* shape, double pt1X, double pt2X, double minY, double maxY)
{
    shape->shapeunion.triangle.pt1X = pt1X;
    shape->shapeunion.triangle.pt2X = pt2X; 
    shape->shapeunion.triangle.minY = minY;
    shape->shapeunion.triangle.maxY = maxY; 
    shape->ft.GetArea = GetTriangleArea;
    shape->ft.GetBoundingBox = GetTriangleBoundingBox;
}


double GetTriangleArea(struct Shape* shape)
{
    return (((shape->shapeunion.triangle.pt2X - shape->shapeunion.triangle.pt1X) * (shape->shapeunion.triangle.maxY - shape->shapeunion.triangle.minY)/2));
}


void GetTriangleBoundingBox(struct Shape* shape, double * Bbox)
{
    Bbox[0] = shape->shapeunion.triangle.pt1X; 
    Bbox[1] = shape->shapeunion.triangle.pt2X; 
    Bbox[2] = shape->shapeunion.triangle.minY;
    Bbox[3] = shape->shapeunion.triangle.maxY;
}    