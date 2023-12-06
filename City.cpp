// City.cpp
#include <cstdlib>
#include <random>

#include "City.h"
#include "Organism.h"
#include "GameSpecs.h"
#include "Human.h"
#include "Zombie.h"

using namespace std;

int City::generateRandomNumber(int startRange, int endRange) const {
    return rand() % (endRange - startRange + 1) + startRange;
}

City::City(){
    srand(time(NULL));
    timeStepCount = 0;
    for (int x = 0; x < GRID_SIZE; x++)
        for (int y = 0; y < GRID_SIZE; y++)
            grid[x][y] = nullptr;

    int x,y;
    int zombieCount = 0;
    int humanCount = 0;

    // add zombies
    while (zombieCount < ZOMBIE_START_COUNT){
        x = generateRandomNumber(0, GRID_SIZE - 1);
        y = generateRandomNumber(0, GRID_SIZE - 1);
        if (grid[x][y] != nullptr) continue;
        grid[x][y] = new Zombie(this, x, y);
        zombieCount++;
    }

    // add humans
    while (humanCount < HUMAN_START_COUNT){
        x = generateRandomNumber(0, GRID_SIZE - 1);
        y = generateRandomNumber(0, GRID_SIZE - 1);
        if (grid[x][y] != nullptr) continue;
        grid[x][y] = new Human(this, x, y);
        humanCount++;
    }
}

void City::takeTimeStep(){
    timeStepCount++;

    // move zombies
    for (int x = 0; x < GRID_SIZE; x++){
        for (int y = 0; y < GRID_SIZE; y++){
            if (grid[x][y] == nullptr) continue;
            if (grid[x][y]->getType() == ZOMBIE_CH)
                grid[x][y]->move();
        }
    }

    // move humans
    for (int x = 0; x < GRID_SIZE; x++){
        for (int y = 0; y < GRID_SIZE; y++){
            if (grid[x][y] == nullptr) continue;
            if (grid[x][y]->getType() == HUMAN_CH)
                grid[x][y]->move();
        }
    }

    for (int x = 0; x < GRID_SIZE; x++){
        for (int y = 0; y < GRID_SIZE; y++){
            if (grid[x][y] == nullptr) continue;
            grid[x][y]->breed();
        }
    }

    for (int x = 0; x < GRID_SIZE; x++){
        for (int y = 0; y < GRID_SIZE; y++){
            if (grid[x][y] == nullptr) continue;
            if (grid[x][y]->starves()){
                delete grid[x][y];
                grid[x][y] = nullptr;
            }
        }
    }
}

bool City::hasDiversity() {
    bool hasHumans = false;
    bool hasZombies = false;

    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j] != nullptr) {
                // Check if the organism is a Human
                if (grid[i][j]->getType() == HUMAN_CH) {
                    hasHumans = true;
                }
                    // Check if the organism is a Zombie
                else if (grid[i][j]->getType() == ZOMBIE_CH) {
                    hasZombies = true;
                }
            }
        }
    }

    // Return true if both humans and zombies exist
    return hasHumans && hasZombies;
}

int City::getGeneration() {
    return timeStepCount;
}

int City::countType(char organismType) {
    int count = 0;

    // Iterate through the grid to count organisms of a specific type
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j] != nullptr && grid[i][j]->getType() == organismType) {
                count++;
            }
        }
    }

    return count;
}

std::ostream& operator<<(std::ostream& output, const City& city) {
    for (int x = 0; x < GRID_SIZE; x++){
        for (int y = 0; y < GRID_SIZE; y++){
            if (city.grid[x][y] != nullptr) {
                if (city.grid[x][y]->getType() == ZOMBIE_CH) {
                    output << "\033[38;5;" << ZOMBIE_COLOR << "m";
                    output << 'Z' << "  ";
                } else if (city.grid[x][y]->getType() == HUMAN_CH) {
                    output << "\033[38;5;" << HUMAN_COLOR << "m";
                    output << 'H' << "  ";
                }
                output << "\033[0m"; // Reset text color to default
            } else {
                output << SPACE_CH << "  ";
            }
        }
        output << std::endl;
    }

    return output;
}

