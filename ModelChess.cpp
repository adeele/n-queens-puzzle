//
// Created by jedrek on 2016-12-03.
//

#include "ModelChess.h"
#include "StateChessboard.h"

int seed = 777;

shared_ptr<State> ModelChess::getStartState() {
    shared_ptr<State> startState(new StateChessboard(chessboardSize, seed));
    return startState;
}

vector<pair<shared_ptr<State>, int>> ModelChess::getNextStates(shared_ptr<State> currentState) {
    StateChessboard *currentChessboardState = static_cast<StateChessboard*>(currentState.get());
    vector<pair<shared_ptr<State>, int>> nextStatesWithStatus;
    int possibleMoves = currentChessboardState->getPossibleMoves();

    for (int i = 0; i < chessboardSize; i++) {
        for (int j = 0; j < possibleMoves; j++) {
            shared_ptr<State> currentState(new StateChessboard(*currentChessboardState));

            if (static_pointer_cast<StateChessboard>(currentState)->move(i, j)){
                nextStatesWithStatus.push_back(make_pair(currentState, 1));
            }
        }
    }

    return nextStatesWithStatus;
}

bool ModelChess::isFinalState(shared_ptr<State> currentState) {
    StateChessboard *startState = static_cast<StateChessboard*>(currentState.get());
    return startState->getHeuristic() == 0;
}

ModelChess::ModelChess(int chessboardSizeToSet) {
    chessboardSize = chessboardSizeToSet;
}