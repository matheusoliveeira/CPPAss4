#include "Zombie.h"
#include "City.h"
#include "GameSpecs.h"
#include "Human.h"
#include <random>
#include <vector>

using namespace std;

vector<int> Zombie::getMovesToHumans(int x, int y) const {
    vector<int> movesToHumans;
    int tempX, tempY;
    for (Direction move = LEFT; move <= DOWN_RIGHT; move = static_cast<Direction>(static_cast<int>(move) + 1)) {
        tempX = x;
        tempY = y;
        getCoordinate(tempX, tempY, move);
        if (!isValidCoordinate(tempX, tempY)) continue;
        if (city->grid[tempX][tempY] == nullptr) continue;
        if (city->grid[tempX][tempY]->getType() == HUMAN_CH)
            movesToHumans.push_back(move);
    }

    return movesToHumans;
}

Zombie::Zombie(City* city, int x, int y): Organism(city, x, y){
    timeTillStarve = ZOMBIE_STARVE;
    timeTillBreed = ZOMBIE_BREED;
}

void Zombie::breed(){
    timeTillBreed--;
    if (timeTillBreed > 0) return;
    vector<int> validMoves = getMovesToEmptyCells(x, y);
    if (validMoves.size() == 0) return;
    int randomMove = validMoves[city->generateRandomNumber(0, validMoves.size() - 1)];
    int newX = x;
    int newY = y;
    getCoordinate(newX, newY, randomMove);
    city->grid[newX][newY] = new Zombie(city, newX, newY);
    timeTillBreed = ZOMBIE_BREED;
}

void Zombie::move(){
    if (timeStepCount == city->timeStepCount) return;
    vector<int> movesToHumans = getMovesToHumans(x, y);
    if (movesToHumans.size() == 0){
        Organism::move();
        timeTillStarve--;
        return;
    }
    timeStepCount++;
    timeTillStarve = ZOMBIE_STARVE;
    int randomMove = movesToHumans[city->generateRandomNumber(0, movesToHumans.size() - 1)];
    int antX = x;
    int antY = y;
    getCoordinate(antX, antY, randomMove);
    delete city->grid[antX][antY];
    city->grid[antX][antY] = this;
    city->grid[x][y] = nullptr;
    x = antX;
    y = antY;
}
