#include <iostream>
#include <chrono>
#include <thread>

#include "City.h"

using namespace std;

void ClearScreen()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int main(){
    City city;

    chrono::milliseconds interval = chrono::duration_cast<chrono::milliseconds>(chrono::duration<double>(PAUSE_SECONDS));

    while (city.countType(HUMAN_CH) > 0 && city.countType(ZOMBIE_CH) > 0 && ((city.getGeneration() + 1) < ITERATIONS)) {
        this_thread::sleep_for(interval);
        ClearScreen();
        cout << city;
        cout << "GENERATION: " << (city.getGeneration() + 1) << endl;
        cout << "HUMANS: " << city.countType(HUMAN_CH) << endl;
        cout << "ZOMBIES: " << city.countType(ZOMBIE_CH) << endl;
        city.takeTimeStep();

    }

    // last print
    ClearScreen();
    cout << city;
    cout << "GENERATION: " << (city.getGeneration() + 1) << endl;
    cout << "HUMANS: " << city.countType(HUMAN_CH) << endl;
    cout << "ZOMBIES: " << city.countType(ZOMBIE_CH) << endl;

    return 0;
}
