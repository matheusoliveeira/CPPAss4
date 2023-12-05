#include "Zombie.h"
#include "City.h"
#include "GameSpecs.h"
#include "Human.h"
#include <random>

Zombie::Zombie() : Organism(), turnsSinceLastMeal(0) {}

Zombie::Zombie(City* city, int width, int height) : Organism(city, width, height), turnsSinceLastMeal(0) {}

Zombie::~Zombie() {}

void Zombie::move() {

    if (hasMoved()) {
        return;  // If already moved, exit the function
    }


    // Use a better random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dirDistribution(0, NUM_DIRECTIONS - 1);

    Direction direction = static_cast<Direction>(dirDistribution(gen));
    moveInDirection(direction);

    // Increment turnsSinceLastMeal after each move
    incrementTurnsSinceLastMeal();

    // Mark the turn as completed
    endTurn();
}

void Zombie::moveInDirection(Direction direction) {
    int newX = x;
    int newY = y;

    switch (direction) {
        case Direction::WEST: newX--; break;
        case Direction::NORTH: newY--; break;
        case Direction::EAST: newX++; break;
        case Direction::SOUTH: newY++; break;
        case Direction::NORTHWEST: newX--; newY--; break;
        case Direction::NORTHEAST: newX++; newY--; break;
        case Direction::SOUTHWEST: newX--; newY++; break;
        case Direction::SOUTHEAST: newX++; newY++; break;
    }

    // Check if the new position is within the grid bounds and available
    if (newX >= 0 && newX < GRIDSIZE && newY >= 0 && newY < GRIDSIZE &&
        city->getOrganism(newX, newY) == nullptr) {
        // Move the zombie to the new position
        city->setOrganism(nullptr, x, y);  // Clear the current cell
        x = newX;
        y = newY;
        city->setOrganism(this, x, y);  // Set the zombie in the new cell
    }
}

char Zombie::getSymbol() const {
    return 'Z';
}

void Zombie::eat() {
    // Implement the eat logic for Zombies
    // For simplicity, let's assume zombies eat humans in adjacent cells

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newX = x + i;
            int newY = y + j;

            // Check if the new position is within the grid bounds
            if (newX >= 0 && newX < GRIDSIZE && newY >= 0 && newY < GRIDSIZE) {
                Organism* potentialPrey = city->getOrganism(newX, newY);
                if (dynamic_cast<Human*>(potentialPrey) != nullptr) {
                    // Found a human, "eat" it by removing it from the grid
                    city->setOrganism(nullptr, newX, newY);
                    return;  // Zombies eat only one human per turn
                }
            }
        }
    }
}

void Zombie::breed() {
    // Implement the breed logic for Zombies
    // For simplicity, let's assume zombies breed by creating a new zombie in an adjacent empty cell

    if (city->getGeneration() % ZOMBIE_BREED == 0) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int newX = x + i;
                int newY = y + j;

                // Check if the new position is within the grid bounds and available
                if (newX >= 0 && newX < GRIDSIZE && newY >= 0 && newY < GRIDSIZE &&
                    city->getOrganism(newX, newY) == nullptr) {
                    // Create a new zombie in the empty cell
                    city->setOrganism(new Zombie(city, newX, newY), newX, newY);
                    return;  // Zombies breed only once per turn
                }
            }
        }
    }
}


void Zombie::starve() {
    // Implement the starve logic for Zombies
    if (turnsSinceLastMeal >= ZOMBIE_STARVE) {
        // Convert back to an empty space
        city->setOrganism(nullptr, x, y);
        delete this;  // Optional: Free the memory occupied by the Zombie
    }
}

void Zombie::incrementTurnsSinceLastMeal() {
    turnsSinceLastMeal++;
}
