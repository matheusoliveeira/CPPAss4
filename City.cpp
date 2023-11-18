// City.cpp
#include <cstdlib>

#include "City.h"
#include "Organism.h"  // Include Organism for printing organism characters
#include "GameSpecs.h"
#include "Human.h"
#include "Zombie.h"

City::City() : generation(0) {
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            grid[i][j] = nullptr;  // Initialize each cell to nullptr
        }
    }

    // Initialize random seed
    srand(static_cast<unsigned int>(time(nullptr)));

    // Create and place initial humans
    for (int i = 0; i < HUMAN_STARTCOUNT; ++i) {
        int x = rand() % GRID_WIDTH;  // Random x coordinate within grid width
        int y = rand() % GRID_HEIGHT; // Random y coordinate within grid height

        // Check if the chosen cell is empty before placing a human
        if (grid[x][y] == nullptr) {
            grid[x][y] = new Human(this, x, y);
        }
            // If the cell is occupied, decrement the loop counter to try again
        else {
            --i;
        }
    }

    // Create and place initial zombies
    for (int i = 0; i < ZOMBIE_STARTCOUNT; ++i) {
        int x = rand() % GRID_WIDTH;  // Random x coordinate within grid width
        int y = rand() % GRID_HEIGHT; // Random y coordinate within grid height

        // Check if the chosen cell is empty before placing a zombie
        if (grid[x][y] == nullptr) {
            grid[x][y] = new Zombie(this, x, y);
        }
            // If the cell is occupied, decrement the loop counter to try again
        else {
            --i;
        }
    }
}

City::~City() {
    // Clean up memory if needed
}

Organism* City::getOrganism(int x, int y) {
    // Implement logic to get organism at a specific position
    return grid[y][x];
}

void City::setOrganism(Organism* organism, int x, int y) {
    // Implement logic to set organism at a specific position
    grid[y][x] = organism;
}

void City::move() {
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            Organism* organism = grid[i][j];
            if (organism != nullptr && organism->isTurn()) {
                organism->move();
            }
        }
    }
}

bool City::hasDiversity() {
    cout << "Debug: Inside City::hasDiversity()" << endl;
    bool hasHumans = false;
    bool hasZombies = false;

    // Iterate through the grid to check for humans and zombies
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            Organism* organism = grid[i][j];
            if (organism != nullptr) {
                // Check if the organism is a Human
                if (dynamic_cast<Human*>(organism) != nullptr) {
                    hasHumans = true;
                }
                    // Check if the organism is a Zombie
                else if (dynamic_cast<Zombie*>(organism) != nullptr) {
                    hasZombies = true;
                }
            }
        }
    }

    // Return true if both humans and zombies exist
    return hasHumans && hasZombies;
}

void City::reset() {
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            Organism* organism = grid[i][j];
            if (organism != nullptr) {
                organism->endTurn();  // Reset the moved flag for each organism
            }
        }
    }
}

void City::countOrganisms() {
    // Implement logic to count and display the number of organisms
}

int City::countType(char organismType) {
    // Implement logic to count organisms of a specific type
}

int City::getGeneration() {
    return generation;
}

std::ostream& operator<<(std::ostream& output, City& city) {
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            Organism* organism = city.grid[y][x];
            if (organism != nullptr) {
                // Check the type of organism and print the appropriate symbol
                if (dynamic_cast<Human*>(organism) != nullptr) {
                    output << 'H';  // 'H' for Human
                } else if (dynamic_cast<Zombie*>(organism) != nullptr) {
                    output << 'Z';  // 'Z' for Zombie
                }
            } else {
                output << SPACE_CH;  // Print empty space
            }
        }
        output << std::endl;  // Move to the next line after each row
    }
    return output;
}
