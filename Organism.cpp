// Organism.cpp
#include "Organism.h"
#include "Human.h"
#include "GameSpecs.h"

std::vector<int> Organism::getMovesToEmptyCells(int x, int y) const {
    std::vector<int> movesToEmptyCells;
    int tempX, tempY;
    for (int move = LEFT; move <= UP; move++){
        tempX = x;
        tempY = y;
        getCoordinate(tempX, tempY, move);
        if (!isValidCoordinate(tempX, tempY)) continue;
        if (city->grid[tempX][tempY] == nullptr)
            movesToEmptyCells.push_back(move);
    }
    return movesToEmptyCells;
}

bool Organism::isValidCoordinate(int x, int y) const {
    if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE)
        return false;
    return true;
}

void Organism::getCoordinate(int& x, int& y, int move) const {
    if (move == LEFT) x--;
    if (move == RIGHT) x++;
    if (move == DOWN) y--;
    if (move == UP) y++;
}

Organism::Organism(City* city, int x, int y){
    this->city = city;
    this->x = x;
    this->y = y;
    timeTillBreed = 0;
    timeStepCount = city->timeStepCount;
}

void Organism::move() {
    if (timeStepCount == city->timeStepCount) return;
    timeStepCount++;
    timeTillBreed--;

    // Generate a random move in the allowed range (up, down, left, or right)
    int randomMove = city->generateRandomNumber(LEFT, DOWN);
    while (randomMove % 2 == 0) {
        // If the randomly generated move is diagonal, regenerate until it's not
        randomMove = city->generateRandomNumber(LEFT, DOWN);
    }

    int newX = x;
    int newY = y;
    getCoordinate(newX, newY, randomMove);

    if (isValidCoordinate(newX, newY) && city->grid[newX][newY] == nullptr) {
        // If the new position is valid and empty, move the organism
        city->grid[x][y] = nullptr;
        city->grid[newX][newY] = this;
        x = newX;
        y = newY;
    }
}
