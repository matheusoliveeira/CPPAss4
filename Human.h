#ifndef _Human_H
#define _Human_H

#include "Organism.h"
#include "City.h"

class Human: public Organism {

public:
    Human(): Organism(){}
    Human(City* city, int x, int y);
    void breed();
    int getType(){ return HUMAN_CH; }

};

#endif