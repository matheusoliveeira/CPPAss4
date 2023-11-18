// Organism.cpp
#include "Organism.h"
#include "Human.h"
#include "GameSpecs.h"

Organism::Organism() : x(0), y(0), width(0), height(0), moved(false), city(nullptr) {}

Organism::Organism(City* city, int width, int height) : x(0), y(0), width(width), height(height), moved(false), city(city) {}

Organism::~Organism() {}

void Organism::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void Organism::endTurn() {
    moved = true;
}

bool Organism::isTurn() {
    return !moved;
}

std::ostream& operator<<(std::ostream& output, Organism* organism) {
    if (organism != nullptr) {
        // Example: Print 'H' for Humans and 'Z' for Zombies
        output << (dynamic_cast<Human*>(organism) != nullptr ? 'H' : 'Z');
    } else {
        output << SPACE_CH;  // Print empty space
    }
    return output;
}
