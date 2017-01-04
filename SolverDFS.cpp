//
// Created by jedrek on 2016-12-03.
//

#include <unordered_set>
#include "SolverDFS.h"
#include "StateChessboard.h"

void SolverDFS::setModel(Model &m) {
    model = &m;
}

// TODO path stats
shared_ptr<State> SolverDFS::solve() {
    shared_ptr<State> startState = model->getStartState();
    list<shared_ptr<State>> statesToVisit;
    unordered_set<shared_ptr<State>, StateChessboard::Hasher, StateChessboard::Comparer> visitedStates;
    startState->print();

    if (model->isFinalState(startState)) {
        startState->print();
        return startState;
    }

    statesToVisit.push_front(startState);
    visitedStates.insert(startState);

    while (true) {
        vector<pair<shared_ptr<State>, int>> nextStatesWithStatus = model->getNextStates(statesToVisit.front());
        statesToVisit.pop_front();

        for (auto currentStateWithStatus : nextStatesWithStatus) {
            if (visitedStates.count(currentStateWithStatus.first) == 0) {
                if (model->isFinalState(currentStateWithStatus.first)) {
                    currentStateWithStatus.first->print();
                    return currentStateWithStatus.first;
                }

                statesToVisit.push_front(currentStateWithStatus.first);
                visitedStates.insert(currentStateWithStatus.first);
            }
        }
    }
}