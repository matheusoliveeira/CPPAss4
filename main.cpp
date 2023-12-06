#include <iostream>
#include <chrono>
#include <thread>

#include "City.h"

using namespace std;

void ClearScreen()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

typedef Organism* OrganismPtr;
typedef City* CityPtr;

int main(){
    City city;

    chrono::milliseconds interval = chrono::duration_cast<chrono::milliseconds>(chrono::duration<double>(PAUSE_SECONDS));

    while (city.hasDiversity() && city.getGeneration() < ITERATIONS) {
        this_thread::sleep_for(interval);
        ClearScreen();
        cout << city;
        cout << "GENERATION: " << city.getGeneration() << endl;
        cout << "HUMANS: " << city.countType(HUMAN_CH) << endl;
        cout << "ZOMBIES: " << city.countType(ZOMBIE_CH) << endl;
        city.takeTimeStep();

    }

    // last print
    ClearScreen();
    cout << city;
    cout << "GENERATION: " << city.getGeneration() << endl;
    cout << "HUMANS: " << city.countType(HUMAN_CH) << endl;
    cout << "ZOMBIES: " << city.countType(ZOMBIE_CH) << endl;

    return 0;
}
