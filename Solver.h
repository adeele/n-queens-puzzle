//
// Created by jedrek on 2016-12-03.
//

#ifndef PSZT1_SOLVER_H
#define PSZT1_SOLVER_H

#include "Model.h"

/*
 * Interface
 * Represents generic solver for a problem
 */

class Solver {
public:
    virtual void setModel(Model &model) = 0;
    virtual shared_ptr<State> solve() = 0;
    virtual ~Solver() {} ;
};

#endif //PSZT1_SOLVER_H