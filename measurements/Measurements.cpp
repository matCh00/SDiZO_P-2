#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <chrono>
#include "Measurements.h"
using namespace std;
using namespace std::chrono;


void algorithm_measurement(){

    double final_time = 0;

    for (int i = 0; i < number; i++) {

        random graph

        //początek pomiaru
        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        algorytm

        //koniec pomiaru
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time = duration_cast<duration<double>>(t2 - t1);
        final_time += (double)time.count();
    }

    ofstream measurement;
    measurement.open("RESULT.txt", ios::app);

    measurement << endl << " FIND  rozmiar: " << size << "  liczba operacji: " << number << "  generowane max: " << max << endl
                << "  czas: " << fixed << setprecision(10) << final_time << endl << "średnia: " << setprecision(10) << final_time / number << endl;

    measurement.close();
}