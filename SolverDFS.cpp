//
// Created by jedrek on 2016-12-03.
//

#include "SolverDFS.h"

void SolverDFS::setModel(Model &m) {
    model = &m;
}

shared_ptr<State> SolverDFS::solve() {
    shared_ptr<State> startState = model->getStartState();
    list<shared_ptr<State>> statesToVisit;
    list<shared_ptr<State>> visitedStates;
    startState->print();

    if (model->isFinalState(startState)) {
        startState->print();
        return startState;
    }

    statesToVisit.push_front(startState);
    visitedStates.push_front(startState);

    while (true) {
        vector<pair<shared_ptr<State>, int>> nextStatesWithStatus = model->getNextStates(statesToVisit.front());
        statesToVisit.pop_front();

        for (auto currentStateWithStatus : nextStatesWithStatus) {
            bool wasVisited = false;

            // Checks if next state hasn't been already visited
            for (auto i : visitedStates) {
                if (i->getHash() == currentStateWithStatus.first->getHash() &&
                    i->isEqual(currentStateWithStatus.first.get())) {
                    wasVisited = true;
                    break;
                }
            }

            if (!wasVisited) {
                if (model->isFinalState(currentStateWithStatus.first)) {
                    currentStateWithStatus.first->print();
                    return currentStateWithStatus.first;
                }

                statesToVisit.push_front(currentStateWithStatus.first);
                visitedStates.push_front(currentStateWithStatus.first);
            }
        }
    }
}
