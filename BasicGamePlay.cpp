//
// Created by panen on 11.07.2020.
//

#pragma once
#include <string>
#include <vector>
#include <map>

using namespace std;

namespace FigDir {

    map<char, string> FIGURES = {{'O', "1100110000000000"},
                                 {'I', "1000100010001000"},
                                 {'S', "0110110000000000"},
                                 {'Z', "1100011000000000"},
                                 {'L', "1000100011000000"},
                                 {'J', "0100010011000000"},
                                 {'T', "1110010000000000"}
    };

    vector<string> dir = {"shift_left ", "shift_right "};
}

namespace ParametrsForEvaluate {
    double EvaluateA = 3;
    double EvaluateB = 1;
    double EvaluateC = 3;
    double EvaluateD = 1.5;
    //
    double costpit = 26.9;
    double costwell = 15.8;
    double cost_pit_in_col = 27.6;
    double cost_pit_in_row = 30.1;
    double cost_top = 25.6;
}

string RotateToLeftUp(string figure) { //Returns our figure after rotation in clockwise direction
    string res = "";
    res += figure.substr(12, 1) +
           figure.substr(8, 1) +
           figure.substr(4, 1) +
           figure.substr(0, 1) +
           figure.substr(13, 1) +
           figure.substr(9, 1) +
           figure.substr(5, 1) +
           figure.substr(1, 1) +
           figure.substr(14, 1) +
           figure.substr(10, 1) +
           figure.substr(6, 1) +
           figure.substr(2, 1) +
           figure.substr(15, 1) +
           figure.substr(11, 1) +
           figure.substr(7, 1) +
           figure.substr(3, 1);
    //move up
    while (true) {
        bool f = true;
        for (int i = 0; i < 4; i++)
            if (res[i]  == '1')
                f = false;
        if (!f)
            break;
        for (int i = 0; i <= 11; i++)
            res[i] = res[i + 4];
        for (int i = 12; i < 16; i++)
            res[i] = '0';
    }
    //move left
    while (true) {
        bool f = true;
        for (int i = 0; i < 16; i += 4)
            if (res[i] == '1')
                f = false;
        if (!f)
            break;
        for (int i = 0; i < 12; i++)
            res[4 * (i % 4) + i / 4] = res[4 * (i % 4) + i / 4 + 1];
        for (int i = 0; i < 4; i++)
            res[4 * i + 3] = '0';
    }
    return res;
}

bool SetFigureAndMoveDown(string figure, int indColumn, vector < vector < int > > &field) { //Returns 1 if we can set a figure, 0 otherwise
    int currRow = 20;
    do {
        bool canapply = true;
        for (int i = currRow; i > currRow - 4; i--) {
            for (int j = indColumn; j < indColumn + 4; j++) {
                if (figure[4 * (currRow - i) + (j - indColumn)] == '1') {
                    if (i < 0 || j >= 10) {
                        canapply = false;
                        continue;
                    }
                    canapply &= field[i][j] == 0;
                }
            }
        }
        if (!canapply)
            break;
    } while(currRow--);
    if (currRow == 20)
        return 0;
    for (int i = currRow + 1; i > (currRow + 1) - 4 && i >= 0; i--) {
        for (int j = indColumn; j < indColumn + 4 && j < 10; j++)
            field[i][j] |= figure[4 * (currRow + 1 - i) + (j - indColumn)] == '1';
    }
    return true;
}

int DestroyLines(vector < vector < int > > &field) { //Returns number of destroyed lines. Also destroy these lines in field
    int NumberOfDestroyed = 0;
    for (int i = 0; i < 21; i++) {
        bool filled = true;
        for (int j = 0; j < 10; j++)
            filled &= field[i][j] == 1;
        if (!filled)
            continue;
        NumberOfDestroyed++;
        for (int ii = i; ii < 21; ii++)
            for (int j = 0; j < 10; j++)
                field[ii][j] = (ii == 20 ? 0 : field[ii + 1][j]);
        i--;
    }
    return NumberOfDestroyed;
}

double evaluate(vector < vector < int > > field) { //Returns how bad this field is
    double cost = 0;
    /*for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 10; j++) {
            cost += ParametrsForEvaluate::EvaluateA * field[i][j] * exp(ParametrsForEvaluate::EvaluateB * i);
        }
    }*/
    int cnt_pit = 0;
    for (int i = 0; i < 21; i++)
        for (int j = 0; j < 10; j++) {
            if (field[i][j] == 1)
                continue;
            for (int ii = i + 1; ii < 21; ii++)
                if (field[ii][j] == 1){
                    cnt_pit++;
                    break;
                }
            }

    cost += ParametrsForEvaluate::costpit * cnt_pit;
    //cost += ParametrsForEvaluate::EvaluateC * exp(ParametrsForEvaluate::EvaluateD * cnt_pit);

    int cnt_well = 0;
    for (int i = 0; i < 21; i++)
        for (int j = 0; j < 10; j++) {
            if (field[i][j] == 1)
                continue;
            if ((j == 0 || field[i][j - 1]) &&
                    (j + 1 == 10 || field[i][j + 1]))
                cnt_well++;
        }

    cost += ParametrsForEvaluate::costwell * cnt_well;

    int cnt_pit_in_col = 0;
    for (int i = 0; i < 21; i++)
        for (int j = 0; j < 10; j++) {
            if (field[i][j])
                continue;
            cnt_pit_in_col += (i + 1 == 21 || field[i + 1][j]);
            cnt_pit_in_col += (i == 0 || field[i - 1][j]);
        }

    cost += ParametrsForEvaluate::cost_pit_in_col * cnt_pit_in_col;

    int cnt_pit_in_row = 0;
    for (int i = 0; i < 21; i++)
        for (int j = 0; j < 10; j++) {
            if (field[i][j])
                continue;
            cnt_pit_in_row += (j == 0 || field[i][j - 1]);
            cnt_pit_in_row += (j + 1 == 10 || field[i][j + 1]);
        }

    cost += ParametrsForEvaluate::cost_pit_in_row * cnt_pit_in_row;

    int top = 0;
    for (int i = 20; i >= 0; i--) {
        bool is1 = false;
        for (int j = 0; j < 10; j++)
            is1 |= field[i][j] == 1;
        if (is1) {
            top = i;
            break;
        }
    }

    cost += ParametrsForEvaluate::cost_top * top;

    //double EvaluateB = 2;
    //cost -= pow(EvaluateB,  top);
    //cost += cnt_pit * 1000;
    //return top;
    return cost;
}
