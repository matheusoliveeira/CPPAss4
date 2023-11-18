//This supposes that city->step() calls the move method of each organism in the city
//in a single pass causing each to perform all tasks that it can.

#include <iostream>
#include <chrono>
#include <thread>
#include "Organism.h"
#include "City.h"
#include "GameSpecs.h"

using namespace std;

void ClearScreen()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int main() {
    City* city = new City();

    chrono::milliseconds interval = chrono::duration_cast<chrono::milliseconds>(chrono::duration<double>(PAUSE_SECONDS));

    while (city->hasDiversity() && city->getGeneration() < ITERATIONS) {
        cout << "inside loop" << endl;
        this_thread::sleep_for(interval);
        ClearScreen();
        city->move();
        city->reset();
        city->countOrganisms();
        cout << *city;
        cout << "GENERATION " << city->getGeneration() << endl;
        cout << "HUMANS: " << city->countType(HUMAN_CH) << endl;
        cout << "ZOMBIES: " << city->countType(ZOMBIE_CH) << endl;

        // Debug statement
        cout << "Debug: End of loop iteration" << endl;
    }

    delete city; // Don't forget to free the memory

    return 0;
}
