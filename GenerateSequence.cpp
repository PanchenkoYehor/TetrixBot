#pragma once
#include <string>
#include <fstream>
#include <algorithm>
#include "GenerateSequence.h"

using namespace std;

string NumToStr(int num) {
    string res;
    while (num) {
        res += '0' + num % 10;
        num /= 10;
    }
    reverse(res.begin(), res.end());
    return (res.empty() ? "0" : res);
}

void GenerateAllTests(string Pattern, int T, int NumberOfFigures) {
    for (int i = 0; i < T; i++) {
        string NameFile = Pattern + NumToStr(i);
        ofstream FileOut(NameFile);
        Generate_Sequence(FileOut, NumberOfFigures);
        FileOut.close();
    }
}