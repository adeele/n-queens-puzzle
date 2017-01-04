//
// Created by jedrek on 2016-12-03.
//

#ifndef PSZT1_MODEL_H
#define PSZT1_MODEL_H

#include <vector>
#include <memory>
#include "State.h"

using namespace std;

class Model {
public:
    virtual shared_ptr<State> getStartState() = 0;
    virtual vector<pair<shared_ptr<State>, int> > getNextStates(shared_ptr<State> s) = 0;
    virtual bool isFinalState(shared_ptr<State> s) = 0;
};

#endif //PSZT1_MODEL_H