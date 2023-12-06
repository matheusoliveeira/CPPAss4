#include "GameSpecs.h"
#include "City.h"
#include "Organism.h"
#include "Human.h"

#include <random>
#include <vector>

using namespace std;

Human::Human(City* city, int x, int y): Organism(city, x, y){
    timeTillBreed = HUMAN_BREED;
}

void Human::breed(){
    if (timeTillBreed > 0) return;
    vector<int> validMoves = getMovesToEmptyCells(x, y);
    if (validMoves.size() == 0) return;
    int randomMove = validMoves[city->generateRandomNumber(0, validMoves.size() - 1)];
    int newX = x;
    int newY = y;
    getCoordinate(newX, newY, randomMove);
    city->grid[newX][newY] = new Human(city, newX, newY);
    timeTillBreed = HUMAN_BREED;
}