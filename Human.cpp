#include "Human.h"
#include "GameSpecs.h"
#include "City.h"

Human::Human() : Organism() {}

Human::Human(City* city, int width, int height) : Organism(city, width, height) {}

Human::~Human() {}

void Human::move() {
    // Implement the move logic for Humans
    // Example: Move randomly in any direction (up, down, left, or right)
    int direction = rand() % NUM_DIRECTIONS;
    int newX = x;
    int newY = y;

    switch (direction) {
        case WEST: newX--; break;
        case NORTH: newY--; break;
        case EAST: newX++; break;
        case SOUTH: newY++; break;
    }

    // Check if the new position is within the grid bounds
    if (newX >= 0 && newX < GRIDSIZE && newY >= 0 && newY < GRIDSIZE) {
        // Move the human to the new position
        city->setOrganism(nullptr, x, y);  // Clear the current cell
        x = newX;
        y = newY;
        city->setOrganism(this, x, y);  // Set the human in the new cell
    }

    // Mark the turn as completed
    endTurn();
}

void Human::recruit() {
    // Implement the recruit logic for Humans
    // This is where a new Human is created in an adjacent empty space
}
