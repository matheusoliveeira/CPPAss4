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

public:
    Organism();
    Organism(City* city, int width, int height);
    virtual ~Organism();

    virtual void move() = 0;
    void setPosition(int x, int y);
    void endTurn();
    bool isTurn();

    bool hasMoved() const;  // Function to check if the organism has moved
    void resetMoved();  // Function to reset the moved flag

    friend std::ostream& operator<<(std::ostream& output, Organism* organism);
    virtual char getSymbol() const = 0;
};

#endif
