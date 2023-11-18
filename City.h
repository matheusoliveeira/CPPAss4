#ifndef _CITY_H
#define _CITY_H

#include <iostream>

using namespace std;

class Organism;  // Forward declaration

const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;

class City {
protected:
    Organism* grid[GRID_HEIGHT][GRID_WIDTH];
    int generation;

public:
    City();
    virtual ~City();

    Organism* getOrganism(int x, int y);
    void setOrganism(Organism* organism, int x, int y);

    void move();
    bool hasDiversity();
    void reset();
    void countOrganisms();
    int countType(char organismType);
    int getGeneration();

    friend ostream& operator<<(ostream& output, City& city);
};

#endif
