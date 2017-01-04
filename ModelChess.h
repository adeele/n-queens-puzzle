//
// Created by jedrek on 2016-12-03.
//

#ifndef PSZT1_MODELCHESS_H
#define PSZT1_MODELCHESS_H

#include "Model.h"

class ModelChess: public Model {
    int chessboardSize;

public:
    ModelChess(int chessboardSizeToSet);
    shared_ptr<State> getStartState() override;
    vector<pair<shared_ptr<State>, int>> getNextStates(shared_ptr<State> currentState) override;
    bool isFinalState(shared_ptr<State> currentState) override;
};

#endif //PSZT1_MODELCHESS_H