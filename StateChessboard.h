//
// Created by jedrek on 2016-12-03.
//

#ifndef PSZT1_STATECHESSBOARD_H
#define PSZT1_STATECHESSBOARD_H

#include "State.h"
#include <cstdlib>
#include <utility>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

class StateChessboard : public State {
public:
    long long int getHash() override;
    int getHeuristic() override;
    int getPossibleMoves() override;
    bool isEqual(State *stateToCompare) override;
    StateChessboard(int chessboardSizeToSet, int seed);
    StateChessboard(const StateChessboard &stateToAssign);
    bool move(unsigned int which, unsigned int where);
    void print();

private:
    int chessboardSize;
    int possibleMoves;
    vector<pair<int, int> > board;
    void normalise();
    void initRandom(int seed);
    int getCollisions();
};

#endif //PSZT1_STATECHESSBOARD_H