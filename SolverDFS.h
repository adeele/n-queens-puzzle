//
// Created by jedrek on 2016-12-03.
//

#ifndef PSZT1_SOLVERDFS_H
#define PSZT1_SOLVERDFS_H

#include "Solver.h"
#include <list>
#include <memory>
#include <iostream>

using namespace std;

/*
 * Represents solver using DFS algorithm to search through the graph
 */

class SolverDFS : public Solver{
    Model *model;

public:
    void setModel(Model &m);
    shared_ptr<State> solve();
};

#endif //PSZT1_SOLVERDFS_H