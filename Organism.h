// Organism.h
#ifndef _Organism_H
#define _Organism_H

#include <iostream>
#include "City.h"

class City;  // Forward declaration

class Organism {
protected:
    int x;
    int y;
    int width;
    int height;
    bool moved;
    City* city;

    enum { WEST, NORTH, EAST, SOUTH, NUM_DIRECTIONS };

public:
    Organism();
    Organism(City* city, int width, int height);
    virtual ~Organism();

    virtual void move() = 0;
    void setPosition(int x, int y);
    void endTurn();
    bool isTurn();

    friend std::ostream& operator<<(std::ostream& output, Organism* organism);
};

#endif
