#ifndef _Human_H
#define _Human_H

#include "Organism.h"

class Human : public Organism {
public:
    Human();
    Human(City* city, int width, int height);
    ~Human();

    void move() override;
    void recruit();

    char getSymbol() const override;

private:
    enum { WEST, NORTH, EAST, SOUTH, NUM_DIRECTIONS };
    int turnsSurvived;
};

#endif