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

/*
 * Represents chessboard state with deployed queens
 */

class StateChessboard : public State {
    int chessboardSize;
    int possibleMoves;
    vector<pair<int, int> > board;
    void initRandom(int seed);
    void normalise();
    int getCollisions();

public:
    StateChessboard(int chessboardSizeToSet, int seed);
    StateChessboard(const StateChessboard &stateToAssign);
    int getPossibleMoves() override;
    long long int getHash() override;
    int getHeuristic() override;
    bool isEqual(State *stateToCompare) override;
    bool move(unsigned int which, unsigned int where);
    void print();
    bool areIndirectStates(State *middleState, State *lastState);

    /*
     * Struct created in case to make it possible to put states in set
     * Provides state hash function
     */
    struct Hasher {
        std::size_t operator() (std::shared_ptr<State> const &state) const {
            return (size_t) state->getHash();
        }
    };

    /*
     * Struct created in case to make it possible to put states in set
     * Gives information how to compare two states
     */
    struct Comparer {
        size_t operator() (std::shared_ptr<State> const &a,
                           std::shared_ptr<State> const &b) const {
            return a->isEqual(&(*b));
        }
    };
};

#endif //PSZT1_STATECHESSBOARD_H