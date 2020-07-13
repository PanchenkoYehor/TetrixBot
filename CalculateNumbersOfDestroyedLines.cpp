#pragma once
#include <fstream>
#include "BasicGamePlay.cpp"
#include <map>

bool Calculate(ifstream &in, ofstream &out, char type, int ind, vector < char > direction,
                vector < vector < int > > &field,int &NumbersOfDestroyedLines) { //Returns is game continuing?
    //What figure is it?
    string pos = FigDir::FIGURES[type];
    //Apply all moves
    int currj = ind - 1;
    for (char move : direction) {
        switch (move) {
            case 'l':
                currj--;
                if (currj < 0)
                    return 0;
                break;
            case 'r':
                currj++;
                if (currj >= 10)
                    return 0;
                break;
            case 'R':
                pos = RotateToLeftUp(pos);
                break;
            default:
                break;
        }
    }
    //cout<<"work\n";
    //Move down
    /*cout<<"before\n";
    for (int i = 20; i >= 0; i--, cout<<"\n")
        for (int j = 0; j < 10; j++)
            cout<<field[i][j];*/
    bool NotEnd = SetFigureAndMoveDown(pos, currj, field);
    /*cout<<"after\n";
    for (int i = 20; i >= 0; i--, cout<<"\n")
        for (int j = 0; j < 10; j++)
            cout<<field[i][j];*/
    if (!NotEnd)
        return 0;
    //Destroy lines
    NumbersOfDestroyedLines += DestroyLines(field);
    return true;
}

void PrintInfo(ofstream &out, string Verdict, int NumberOfTest,int NumbersOfDestroyedLines) {
    out<<NumberOfTest<<"\n";
    out<<"Number of destroyed lines is "<<NumbersOfDestroyedLines<<". "<<Verdict<<"\n";
}

int CalculateNumbersOfDestroyedLines(ifstream &in, ofstream &out, int NumberOfTest) {
    vector < vector < int > > field(21, vector < int > (10, 0));
    string Verdict = "Game was ended.\n";
    int NumbersOfDestroyedLines = 0;
    while (!in.eof()) {
        string type;
        in>>type;
        if (in.eof())
            break;
        int ind;
        in>>ind;
        //cout<<"look: "<<type<<" "<<ind<<"\n";
        string seq;
        getline(in, seq);
        getline(in, seq);
        //cout<<"seq = "<<seq<<"\n";
        vector < char > direction;
        seq += ' ';
        for (int i = 0; i < seq.size(); i++) {
            if (seq[i] != ' ')
                continue;
            if (i > 1 && seq[i - 2] == 'f')
                direction.push_back('l');
            else if (i > 1 && seq[i - 2] == 'h')
                direction.push_back('r');
            else if (seq[i - 1] == 'e')
                direction.push_back('R');
        }
        //cout<<"dir.size() = "<<direction.size()<<"\n";
        if (!Calculate(in, out, type[0], ind, direction, field, NumbersOfDestroyedLines)) {
            Verdict = "Game wasn't ended.\n";
            break;
        }
    }
    PrintInfo(out, Verdict, NumberOfTest, NumbersOfDestroyedLines);
    return NumbersOfDestroyedLines;
}
