//
// Created by panen on 10.07.2020.
//
#pragma once
#ifndef TASKS_GENERATESEQUENCE_H
#define TASKS_GENERATESEQUENCE_H

#include <fstream>
#include <random>
#include <string>
#include <time.h>

using namespace std;

void Generate_Sequence(ofstream &out, int NumberOfFigures) {
    //out.open();
    string fig[7] = {"O", "I", "S", "Z", "L", "J", "T"};
    //srand(time(0));
    //srand(12345 );
    for (int i = 0; i < NumberOfFigures; i++) {
        int f = rand() % 7;
        int pos = rand() % 10 + 1;
        if ((f == 0 && pos <= 9) ||
            (f == 1 && pos <= 10) ||
            (f == 2 && pos <= 8) ||
            (f == 3 && pos <= 8) ||
            (f == 4 && pos <= 9) ||
            (f == 5 && pos <= 9) ||
            (f == 6 && pos <= 8)
                ) {
            out<<fig[f]<<" "<<pos<<"\n"; } else i--;
    }
    out<<"0\n";
    //out.close();
}



#endif //TASKS_GENERATESEQUENCE_H
