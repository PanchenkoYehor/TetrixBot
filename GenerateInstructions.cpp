#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "BasicGamePlay.cpp"

using namespace std;

void MakeBestMove(ifstream &in, ofstream &out, string s, vector < vector < int > > &field) {
    string ask = "";
    int pos;
    in>>pos;
    pos--;
    //cout<<s<<" "<<pos<<"\n";
    double bestval = INT64_MAX;
    int best_cnt_rot = 0;
    int best_pos = 0;
    vector < vector < int > > bestfield(21, vector < int > (10, 0));
    vector < vector < int > > curr(21, vector < int > (10, 0));
    string currstr = FigDir::FIGURES[s[0]];
    int move_left = pos;
    pos = 0;
    for (int p = 0; p < 10; p++) {
        for (int rot = 0; rot < 4; rot++, currstr = RotateToLeftUp(currstr)) {
            vector < pair<int,int> > v;
            for (int i = 0; i < 16; i++)
                if (currstr[i] == '1')
                    v.push_back(make_pair(20 - (i / 4), p + (i % 4)));
            bool cor = true;
            for (auto i : v)
                if (i.second >= 10)
                    cor = false;
            if (!cor) {
                /*for (int rest_rot = rot; rest_rot < 4; rest_rot++)
                    currstr = Rotate(currstr);
                break;*/
                continue;
            }

            for (int i = 0; i < 21; i++)
                for (int j = 0; j < 10; j++)
                    curr[i][j] = field[i][j];
            while (true) { //move down
                bool can = true;
                for (auto i : v)
                    if (i.first - 1 < 0 || curr[i.first - 1][i.second] == 1)
                        can = false;
                if (!can)
                    break;

                for (auto &i : v)
                    i.first--;
            }
            for (auto i : v)
                curr[i.first][i.second] = 1;

            for (int i = 0; i < 21; i++) {
                bool can = true;
                for (int j = 0; j < 10; j++)
                    if (curr[i][j] == 0)
                        can = false;
                if (can) {
                    for (int ii = i; ii + 1 < 21; ii++)
                        for (int j = 0; j < 10; j++)
                            curr[ii][j] = curr[ii + 1][j];
                    for (int j = 0; j < 10; j++)
                        curr[20][j] = 0;
                    i--;
                }
            }
            //cout<<"pass\n";
            //cout<<p<<" "<<rot<<" "<<evaluate()<<"\n";
            /*int top = 0;
            for (int i = 0; i < 20; i++)
                for (int j = 0; j < 10; j++)
                    if (curr[i][j] == '1')
                        top = i;*/
            if (evaluate(curr) < bestval) {
                bestval = evaluate(curr);
                best_cnt_rot = rot;
                best_pos = p;
                for (int i = 0; i < 21; i++)
                    for (int j = 0; j < 10; j++)
                        bestfield[i][j] = curr[i][j];
            }
            //cout<<"end\n";
        }
    }

    for (int i = 0; i < 21; i++)
        for (int j = 0; j < 10; j++)
            field[i][j] = bestfield[i][j];

    bool isprinted = false;
    //cout<<"best_pos = "<<best_pos<<"\n";
    //cout<<"pos = "<<pos<<"\n";

    vector < string > asks;
    for (int i = 0; i < best_cnt_rot; i++) {
        ask += "rotate ";
        asks.push_back("rotate ");
    }
    for (int i = 0; i < abs(best_pos - pos); i++) {
        ask += FigDir::dir[best_pos > pos];
        asks.push_back(FigDir::dir[best_pos > pos]);
    }

    /*if (ask.size() == 0) {
        ask += (pos < 5 ? (dir[1] + dir[0]) : (dir[0] + dir[1]));
        asks.push_back(pos < 5 ? (dir[1] + dir[0]) : (dir[0] + dir[1]));
    }*/

    //asks.push_back(best_pos < 5 ? dir[1] : dir[0]);


    /*if (asks.size() && asks[0] == dir[1]) {
        reverse(asks.begin(), asks.end());
    }*/
    //asks.push_back(best_pos < 5 ? dir[0] : dir[1]);
    //cout<<s<<" "<<(pos + 1)<<"\n";
    out<<s<<" "<<move_left + 1<<"\n";
    //cout<<ask<<"\n";
    for (int i = 0; i < move_left; i++)
        out<<FigDir::dir[0];
    for (int i = 0; i < asks.size(); i++)
        out<<asks[i];
    //cout<<asks.back().substr(0, asks.back().size() - 1);
    /*for (int i = 0; i < move_left; i++)
        cout<<dir[1];*/
    out<<"\n";
}

void GenerateInstructions(ifstream &in, ofstream &out) {
    vector < vector < int > > field(21, vector < int > (10, 0));
    while (true) {
        string s;
        in>>s;
        if (in.eof())
            return;
        if (s == "0")
            break;
        MakeBestMove(in, out, s, field);
    }
}