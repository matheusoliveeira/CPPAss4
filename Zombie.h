#ifndef _Zombie_H
#define _Zombie_H

#include "Organism.h"
#include "City.h"

class Zombie : public Organism {
public:
    Zombie();
    Zombie(City* city, int width, int height);
    ~Zombie();

    void move() override;
    void eat();
    void breed();
    void starve();

    char getSymbol() const override;

private:
    enum class Direction { WEST, NORTH, EAST, SOUTH, NORTHWEST, NORTHEAST, SOUTHWEST, SOUTHEAST };
    static const int NUM_DIRECTIONS = 8;
    int turnsSinceLastMeal;

    void moveInDirection(Direction direction);
    void incrementTurnsSinceLastMeal();
};

#endif