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
#include <memory>

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

    struct Hasher {
        std::size_t operator() (std::shared_ptr<State> const &state) const {
            return (size_t) state->getHash();
        }
    };

    struct Comparer {
        size_t operator() (std::shared_ptr<State> const &a,
                           std::shared_ptr<State> const &b) const {
            return a->isEqual(&(*b));
        }
    };

private:
    int chessboardSize;
    int possibleMoves;
    vector<pair<int, int> > board;
    void normalise();
    void initRandom(int seed);
    int getCollisions();
};

#endif //PSZT1_STATECHESSBOARD_H