//
// Created by jedrek on 2016-12-03.
//

#include <unordered_set>
#include <stack>
#include "SolverDFS.h"
#include "StateChessboard.h"

/*
 * Sets up a model for solver to solve
 *
 * @param model to solve
 */
void SolverDFS::setModel(Model &modelToSet) {
    model = &modelToSet;
}

/*
 * Solves the problem using interface provided by state and model.
 * Prints out whole path from start state to the final state.
 * Counts how many times the algorithm had to come back becouse of there was no more neighbours to find check.
 *
 * @return final state found
 */
shared_ptr<State> SolverDFS::solve() {
    shared_ptr<State> startState = model->getStartState();
    stack<shared_ptr<State>> statesToVisit;
    unordered_set<shared_ptr<State>, StateChessboard::Hasher, StateChessboard::Comparer> visitedStates;
    statesToVisit.push(startState);
    int deadStates = 0;

    while (!model->isFinalState(statesToVisit.top())) {
        vector<pair<shared_ptr<State>, int>> nextStatesWithStatus = model->getNextStates(statesToVisit.top());
        visitedStates.insert(statesToVisit.top());
        bool deadState = true;

        for (auto currentStateWithStatus : nextStatesWithStatus) {
            if (visitedStates.count(currentStateWithStatus.first) == 0) {
                statesToVisit.push(currentStateWithStatus.first);
                deadState = false;
                break;
            }
        }

        if (deadState) {
            statesToVisit.pop();
            deadStates++;
        }
    }

    /*
     * Printing out results
     */
    shared_ptr<State> finalState = statesToVisit.top();
    int indirectStatesInPath = statesToVisit.size();
    stack<StateChessboard*> tmp;

    while (statesToVisit.size() > 2) {
        StateChessboard *a = static_cast<StateChessboard*>(statesToVisit.top().get());
        statesToVisit.pop();
        tmp.push(a);

        shared_ptr<State> b = statesToVisit.top();
        statesToVisit.pop();
        shared_ptr<State> c = statesToVisit.top();

        if (!a->areIndirectStates(b.get(), c.get())) {
            statesToVisit.push(b);
        }
    }

    while (!statesToVisit.empty()) {
        StateChessboard *a = static_cast<StateChessboard*>(statesToVisit.top().get());
        statesToVisit.pop();
        tmp.push(a);
    }

    cout << " SCIEZKA: " <<endl;

    int directStatesInPath = tmp.size();

    while (!tmp.empty()) {
        tmp.top()->print();
        tmp.pop();
    }

    cout << indirectStatesInPath << " stanow posrednich" << endl;
    cout << directStatesInPath << " stanow bezposrednich" << endl;
    cout << deadStates << " powrotow" << endl << endl;

    cout << " START " << endl;
    startState->print();
    cout << " KONIEC " << endl;
    finalState->print();

    return finalState;
}