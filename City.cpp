// City.cpp
#include <cstdlib>
#include <random>

#include "City.h"
#include "Organism.h"
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
        int x = rand() % (GRID_WIDTH / 2);  // Random x coordinate within half of the grid width
        int y = rand() % (GRID_HEIGHT / 2); // Random y coordinate within half of the grid height

        // Distribute humans in each quadrant
        x += (i % 2) * (GRID_WIDTH / 2);    // Shift x coordinate for alternating columns
        y += (i / (HUMAN_STARTCOUNT / 2)) * (GRID_HEIGHT / 2);   // Shift y coordinate for each quadrant

        // Check if the chosen cell is empty before placing a human
        if (grid[x][y] == nullptr) {
            grid[x][y] = new Human(this, x, y);
        } else {
            --i;
        }
    }

    // Create and place initial zombies
    for (int i = 0; i < ZOMBIE_STARTCOUNT; ++i) {
        int x = rand() % (GRID_WIDTH / 2);  // Random x coordinate within half of the grid width
        int y = rand() % (GRID_HEIGHT / 2); // Random y coordinate within half of the grid height

        // Distribute zombies in each quadrant
        x += (i % 2) * (GRID_WIDTH / 2);    // Shift x coordinate for alternating quadrants
        y += (i / (ZOMBIE_STARTCOUNT / 2)) * (GRID_HEIGHT / 2); // Shift y coordinate for each quadrant

        // Check if the chosen cell is empty before placing a zombie
        if (grid[x][y] == nullptr) {
            grid[x][y] = new Zombie(this, x, y);
        } else {
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

    incrementGeneration();
}

bool City::hasDiversity() {
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

//void City::reset() {
//    for (int i = 0; i < GRID_HEIGHT; ++i) {
//        for (int j = 0; j < GRID_WIDTH; ++j) {
//            Organism* organism = grid[i][j];
//            if (organism != nullptr) {
//                organism->endTurn();  // Reset the moved flag for each organism
//            }
//        }
//    }
//}

void City::resetMoved() {
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            Organism* organism = grid[i][j];
            if (organism != nullptr) {
                organism->resetMoved();  // Call a function to reset hasMoved flag
            }
        }
    }
}

void City::countOrganisms() {
    int totalOrganisms = 0;

    // Iterate through the grid to count all organisms
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            if (grid[i][j] != nullptr) {
                totalOrganisms++;
            }
        }
    }
}

int City::countType(char organismType) {
    int count = 0;

    // Iterate through the grid to count organisms of a specific type
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            Organism* organism = grid[i][j];
            if (organism != nullptr && organism->getSymbol() == organismType) {
                count++;
            }
        }
    }

    return count;
}

int City::getGeneration() {
    return generation;
}

std::ostream& operator<<(std::ostream& output, City& city) {
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            Organism* organism = city.grid[y][x];
            if (organism != nullptr) {
                // Check the type of organism and print the appropriate symbol with color
                if (dynamic_cast<Human*>(organism) != nullptr) {
                    output << "\033[38;5;" << HUMAN_COLOR << "m";  // Set text color for humans
                    output << 'H' << "  ";  // 'H' for Human with space
                } else if (dynamic_cast<Zombie*>(organism) != nullptr) {
                    output << "\033[38;5;" << ZOMBIE_COLOR << "m";  // Set text color for zombies
                    output << 'Z' << "  ";  // 'Z' for Zombie with space
                }
                output << "\033[0m";  // Reset text color to default
            } else {
                output << SPACE_CH << "  ";  // Print empty space with space
            }
        }
        output << std::endl;  // Move to the next line after each row
    }
    return output;
}

