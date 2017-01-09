//
// Created by jedrek on 2016-12-03.
//

#ifndef PSZT1_STATE_H
#define PSZT1_STATE_H
/*
 * Interface
 * Gives a definition for some state of a problem
 */

class State {
public:
    virtual long long getHash() = 0;
    virtual int getHeuristic() = 0;
    virtual bool isEqual(State *s) = 0;
    virtual void print() = 0;
    virtual int getPossibleMoves() = 0;
};
#endif //PSZT1_STATE_H