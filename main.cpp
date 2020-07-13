#include <iostream>
#include <string>
#include "GenerateSequence.cpp"
#include "GenerateInstructions.cpp"
#include "CalculateNumbersOfDestroyedLines.cpp"
#include "BasicGamePlay.cpp"
#include <random>

using namespace std;

const bool NeedToGenerateSequence = true;
const bool NeedToGenerateInstructions = true;
const bool NeedToGenerateResults = true;
const string PathDataSet = "C:\\Users\\panen\\CLionProjects\\Tasks\\DataSet\\Data";
const string PathOutputSet = "C:\\Users\\panen\\CLionProjects\\Tasks\\OutputSet\\Output";
const string PathResult = "C:\\Users\\panen\\CLionProjects\\Tasks\\ResultForEveryTest";
int NumberOfTests = 4; //Number of tests
int NumberOfFigures = 4000; //Number of figures

int main() {
    /*double bestA, bestB, bestC, bestD;
    int BestTotal = 0;
    double Interval = 0.5;
    double mn = 0, mx = 6;
    for (double cA = mn; cA < mx; cA += Interval) {
        for (double cB = mn; cB < mx; cB += Interval) {
            for (double cC = mn; cC < mx; cC += Interval) {
                for (double cD = mn; cD < mx; cD += Interval) {
                    ParametrsForEvaluate::EvaluateA = cA;
                    ParametrsForEvaluate::EvaluateB = cB;
                    ParametrsForEvaluate::EvaluateC = cC;
                    ParametrsForEvaluate::EvaluateD = cD;
                    if (NeedToGenerateSequence) {
                        //srand(time(0));
                        GenerateAllTests(PathDataSet, NumberOfTests, NumberOfFigures);
                    }
                    if (NeedToGenerateInstructions) {
                        for (int i = 0; i < NumberOfTests; i++) {
                            ifstream FileIn(PathDataSet + NumToStr(i));
                            ofstream FileOut(PathOutputSet + NumToStr(i));
                            GenerateInstructions(FileIn, FileOut);
                        }
                    }
                    if (NeedToGenerateResults) {
                        ofstream FileOut(PathResult);
                        int TotalLines = 0;
                        for (int i = 0; i < NumberOfTests; i++) {
                            //cout << i << "\n";
                            ifstream FileIn(PathOutputSet + NumToStr(i));
                            TotalLines += CalculateNumbersOfDestroyedLines(FileIn, FileOut, i);
                        }
                        FileOut << "Total destroyed lines is " << TotalLines << "\n";
                        cout<<cA<<" "<<cB<<" "<<cC<<" "<<cD<<" "<<TotalLines<<"\n";
                        if (TotalLines >= BestTotal) {
                            bestA = cA;
                            bestB = cB;
                            bestC = cC;
                            bestD = cD;
                            BestTotal = TotalLines;
                        }
                    }
                }
            }
        }
    }
    cout<<bestA<<" "<<bestB<<" "<<bestC<<" "<<bestD<<"\n";
    cout<<BestTotal<<"\n";*/
    if (NeedToGenerateSequence) {
        //srand(time(0));
        GenerateAllTests(PathDataSet, NumberOfTests, NumberOfFigures);
    }
    if (NeedToGenerateInstructions) {
        for (int i = 0; i < NumberOfTests; i++) {
            ifstream FileIn(PathDataSet + NumToStr(i));
            ofstream FileOut(PathOutputSet + NumToStr(i));
            GenerateInstructions(FileIn, FileOut);
        }
    }
    if (NeedToGenerateResults) {
        ofstream FileOut(PathResult);
        int TotalLines = 0;
        for (int i = 0; i < NumberOfTests; i++) {
            //cout << i << "\n";
            ifstream FileIn(PathOutputSet + NumToStr(i));
            TotalLines += CalculateNumbersOfDestroyedLines(FileIn, FileOut, i);
        }
        FileOut << "Total destroyed lines is " << TotalLines << "\n";
    }
}