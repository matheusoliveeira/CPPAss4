#include "Human.h"
#include "City.h"
#include "GameSpecs.h"

#include <random>

Human::Human() : Organism(), turnsSurvived(0) {}

Human::Human(City* city, int width, int height) : Organism(city, width, height), turnsSurvived(0) {}

Human::~Human() {}

void Human::move() {

    if (hasMoved()) {
        return;  // If already moved, exit the function
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dirDistribution(0, NUM_DIRECTIONS - 1);

    int direction = dirDistribution(gen);
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

        // Increment turns survived after each move
        turnsSurvived++;

        // Check if the human has survived for a certain number of turns
        if (turnsSurvived >= TURNS_TO_SURVIVE) {
            recruit();  // Initiate recruitment
            turnsSurvived = 0;  // Reset turnsSurvived after recruitment
        }
    }

    // Mark the turn as completed
    endTurn();
}

char Human::getSymbol() const {
    return HUMAN_CH;  // Replace this with the actual symbol for Human
}

void Human::recruit() {
    // Implement the recruit logic for Humans
    // This is where a new Human is created in an adjacent empty space

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newX = x + i;
            int newY = y + j;

            // Check if the new position is within the grid bounds and available
            if (newX >= 0 && newX < GRIDSIZE && newY >= 0 && newY < GRIDSIZE &&
                city->getOrganism(newX, newY) == nullptr) {
                // Create a new human in the empty cell
                city->setOrganism(new Human(city, newX, newY), newX, newY);
                return;  // Humans recruit only once per turn
            }
        }
    }
}