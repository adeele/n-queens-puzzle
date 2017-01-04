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

class SolverDFS : public Solver{
private:
        Model *model;

public:
    void setModel(Model &m);
    shared_ptr<State> solve();
};

#endif //PSZT1_SOLVERDFS_H