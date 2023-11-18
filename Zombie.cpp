#include "Zombie.h"
#include "City.h"
#include "GameSpecs.h"

Zombie::Zombie() : Organism() {}

Zombie::Zombie(City* city, int width, int height) : Organism(city, width, height) {}

Zombie::~Zombie() {}

void Zombie::move() {
    // Implement the move logic for Zombies
}

void Zombie::eat() {
    // Implement the eat logic for Zombies
}

void Zombie::breed() {
    // Implement the breed logic for Zombies
}

void Zombie::starve() {
    // Implement the starve logic for Zombies
}
