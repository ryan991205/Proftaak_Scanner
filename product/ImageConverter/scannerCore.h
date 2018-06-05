#ifndef SCANNERCORE_H
#define SCANNERCORE_H

struct Point2i
{
    int x;
    int y;
};

struct Line 
{
    Point2i beginPoint; 
    Point2i endPoint; 
};

#endif