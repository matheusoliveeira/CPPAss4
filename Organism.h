// Organism.h
#ifndef _Organism_H
#define _Organism_H

#include <iostream>
#include <vector>

#include "City.h"

class City;

class Organism {

protected:
    City *city;
    int x;
    int y;
    int timeTillBreed;
    int timeStepCount;
    //given a coordinate of the cell (x,y),
    //returns a list of valid moves to adjacent empty cells
    std::vector<int> getMovesToEmptyCells(int x, int y) const;
    bool isValidCoordinate(int x, int y) const;
    //given a valid move from grid[x][y],
    //updates x and y according to the move
    void getCoordinate(int& x, int& y, int move) const;

public:
    Organism(): city(nullptr), x(0), y(0), timeTillBreed(0), timeStepCount(0){}
    Organism(City *city, int x, int y);
    virtual void breed() = 0;
    virtual void move();
    virtual int getType() = 0;
    virtual bool starves() { return false; }

};

#endif
