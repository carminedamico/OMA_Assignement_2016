#ifndef COIOTE_HEURISTIC_HEURISTIC_H
#define COIOTE_HEURISTIC_HEURISTIC_H

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <list>
#include <map>
#include <deque>

using namespace std;

struct Data {
    double**** costs;
    int* n;
    int* activities;
    int*** usersCell;
};

enum eFeasibleState {
    FEASIBLE,
    NOT_FEASIBLE_DEMAND,
    NOT_FEASIBLE_FLOW,
    NOT_FEASIBLE_USERS
};

class Agent {
public:

    int j;
    int m;
    int t;
    int n;
    Agent(int j, int m, int t, int n) {
        this->j = j;
        this->m = m;
        this->t = t;
        this->n = n;
    }
};

class Cell {
public:
    
    int i;
    double partialObjFunc;
    int activities;
    deque<Agent> usedAgents;
    Cell(int i, int n, double Obj) {
        this->i = i;
        this->activities = n;
        this->partialObjFunc = Obj;
    }
};

class Solution {
public:
    
    int cellsWithActivitiesLeft;
    vector<Cell> cells;
    double objFunc;
    int*** usersCell;
};

class Heuristic{
private:
    
    int nTimeSteps;
    int nCustomerTypes;
    int nCells;

    Data problem;

    bool hasSolution;
    double epsilon;
    Solution B;
    Solution R;
    Solution S;
    int**** solution;

    void copyDataStructure(Solution* Y, Solution* X);

public:
    
    Heuristic(){};
    double* bestSolution;
    bool bestSolutionKnown;

    Heuristic(string path);

    void Metaheuristic(vector<double>& stat);

    void solveGreedy();

    void gentlemanGreedy();

    void gentlemanAgreement();

    void gentlemenClub(int n);

    void getStatSolution(vector<double>& stat);

    void printProblem();

    void writeKPI(string path, string nameInstance, vector<double> stat);

    void writeSolution(string path);

    eFeasibleState isFeasible(string path);
};

#endif //COIOTE_HEURISTIC_HEURISTIC_H
