//
// Created by jedrek on 2016-12-03.
//

#include "ModelChess.h"
#include "StateChessboard.h"

/*
 * Constructor
 * Creates model with specified size of the board
 *
 * @param size of a board to set
 */
ModelChess::ModelChess(int chessboardSizeToSet) {
    chessboardSize = chessboardSizeToSet;
}

/*
 * Generates start state of the model.
 *
 * @return start state generated randomly
 */
shared_ptr<State> ModelChess::getStartState() {
    shared_ptr<State> startState(new StateChessboard(chessboardSize, rand()));
    return startState;
}

/*
 * Finds states neighbouring with the state given.
 * Every neighbour found could have its specified potential to be the best choice; that's the promising feature, but it
 * is not useful for our solver, so we just left it here, mocked with 1.
 *
 * @param base state to find its neighbours
 * @return found adjacent states with their potential
 */
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

/*
 * Checks if the state given is the final state - where queens do not collide with each other
 *
 * @param state to check
 * @return true if given state is final, false oterwise.
 */
bool ModelChess::isFinalState(shared_ptr<State> currentState) {
    StateChessboard *startState = static_cast<StateChessboard*>(currentState.get());
    return startState->getHeuristic() == 0;
}
