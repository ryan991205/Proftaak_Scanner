#ifndef MAZE_H
#define MAZE_H

#include <vector>

#include "Point.h"
#include "Vect.h"


struct Maze
{
    std::vector<Vect> walls;
    std::vector<Vect> solution;
    Point start;
    Point end;
};

#endif