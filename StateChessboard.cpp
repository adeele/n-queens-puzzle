//
// Created by jedrek on 2016-12-03.
//

#include "StateChessboard.h"

/*
 * Randomizes queens' placing on the chessboard.
 *
 * @param number, depending on which positions for queens are chosen.
 */
void StateChessboard::initRandom(int seed) {
    int count = chessboardSize;
    int *array = new int[chessboardSize * chessboardSize]();
    srand(seed);

    vector<pair<int, int> > list;
    while (count) {
        int x = rand() % chessboardSize;
        int y = rand() % chessboardSize;

        if (array[x + chessboardSize * y] == 0) {
            array[x + chessboardSize * y] = count--;
            list.push_back(make_pair(x, y));
        }
    }

    board = list;
    delete array;
}

/*
 * Changes queens order into reading's direction to make e.g. comparison easier.
 */
void StateChessboard::normalise() {
    std::sort(board.begin(), board.end(), [](auto &left, auto &right) {
        return left.second < right.second ||
               (left.second == right.second && left.first < right.first);
    });
}

/*
 * Computes how many queens are not colliding with each other
 *
 * @return number of NOT properly ordered queens
 */
int StateChessboard::getCollisions() {
    int *horizontal = new int[chessboardSize]();
    int *vertical = new int[chessboardSize]();
    int *majorDiagonal = new int[2 * chessboardSize](); // \ diagonal
    int *minorDiagonal = new int[2 * chessboardSize](); // / diagonal

    for (auto i: board) {
        horizontal[i.first]++;
        vertical[i.second]++;
        majorDiagonal[i.first + i.second]++;
        minorDiagonal[i.first - i.second + chessboardSize - 1]++;
    }

    int collisions = 0;
    for (auto i: board) {
        if (horizontal[i.first] > 1 ||
            vertical[i.second] > 1 ||
            majorDiagonal[i.first + i.second] > 1 ||
            minorDiagonal[i.first - i.second + chessboardSize - 1] > 1)
            collisions++;
    }

    return collisions;
}

/*
 * Constructor
 * Creates chessboard state with given size of the board and queens placed randomly.
 *
 * @param size of chessboard (also number of queens to set up)
 * @param call parameter to the random number generator
 */
StateChessboard::StateChessboard(int chessboardSizeToSet, int seed) {
    chessboardSize = chessboardSizeToSet;
    possibleMoves = 8;
    initRandom(seed);
}

/*
 * Constructor
 * Creates new state copying the state given as a parameter
 *
 * @param state to copy
 */
StateChessboard::StateChessboard(const StateChessboard &stateToAssign) {
    chessboardSize = stateToAssign.chessboardSize;
    board = stateToAssign.board;
    possibleMoves = 8;
}

/*
 * Provides an information about number of possible moved for the state
 * @return number of possible moves
 */
int StateChessboard::getPossibleMoves() {
    return possibleMoves;
}

/*
 * Provides access to the private method to get information how far the solution is.
 *
 * @return heuristic distance from the solution
 */
int StateChessboard::getHeuristic() {
    return getCollisions();
}

/*
 * Computes state's hash for easier comparison and to make it possible to put states in set
 *
 * @return state's hash
 */
long long int StateChessboard::getHash() {
    long long hash = 0;

    for (auto i : board) {
        hash += (i.first + 1) * (i.second + 1) * (i.second + 1);
    }

    return hash;
}

/*
 * Compares the state on witch this method is called with another one, given as a function parameter.
 *
 * @param state to compare with
 * @return true if states are equal, false otherwise
 */
bool StateChessboard::isEqual(State *stateToCompare) {
    StateChessboard *chessboardStateToCompare = static_cast<StateChessboard *>(stateToCompare);
    chessboardStateToCompare->normalise();
    normalise();

    return equal(board.begin(), board.end(), chessboardStateToCompare->board.begin(), chessboardStateToCompare->board.end());
}

/*
 * Moves queen if the move is permitted, i.e. place to move is in chessboard bound and there is no other queen on chosen
 * position.
 * For queen x, there are at most 8 possible moves in our case, which is presented in the `image` below; of course
 * queens can move further away on chessboard, but our states are representing only indirect states, in purpose to make
 * the calculations nicer.
 * 1 2 3
 * 8 x 4
 * 7 6 5
 *
 * @param specifies which queen is about to move
 * @param direction to move queen
 *
 * @return true if the queen has been moved, false otherwise
 */
bool StateChessboard::move(unsigned int which, unsigned int where) {
    if (which >= chessboardSize || where >= possibleMoves) {
        return false;
    }

    pair<int, int> chess = board.at(which);

    if (where == 2 || where == 3 || where == 4) {
        chess.first++;
    }

    if (where == 0 || where == 6 || where == 7) {
        chess.first--;
    }

    if (where == 4 || where == 5 || where == 6) {
        chess.second++;
    }

    if (where == 0 || where == 1 || where == 2) {
        chess.second--;
    }

    if (chess.first >= 0 && chess.first < chessboardSize && chess.second >= 0 && chess.second < chessboardSize) {
        auto findIter = find(board.begin(), board.end(), chess);

        if (findIter == board.end()) {
            board.at(which) = chess;
            return true;
        }
    }

    return false;
}

/*
 * Prints the state out
 */
void StateChessboard::print() {
    char *array = new char[chessboardSize * chessboardSize];

    for (int i = 0; i < chessboardSize * chessboardSize; i++) {
        array[i] = 'o';
    }

    for (auto i : board) {
        array[i.first + chessboardSize * i.second] = 'x';
    }

    for (int i = 0; i < chessboardSize; i++) {
        for (int j = 0; j < chessboardSize; j++) {
            cout << " " << array[i * chessboardSize + j];
        }

        cout << endl;
    }

    cout << endl;
}

/*
 * Checks if state provided as a first parameter is indirect state between two others
 *
 * @param state to check if can be omitted
 * @param helper parameter to decide if middle state is indirect
 * @return true if middle state can be omitted, false otherwise
 */
bool StateChessboard::areIndirectStates(State *middleState, State *lastState) {
    StateChessboard *middleChessboardState = static_cast<StateChessboard *>(middleState);
    StateChessboard *lastChessboardState = static_cast<StateChessboard *>(lastState);

    for (auto i : board) {
        auto findInMiddle = find(middleChessboardState->board.begin(), middleChessboardState->board.end(), i);
        auto findInLast = find(lastChessboardState->board.begin(), lastChessboardState->board.end(), i);

        if (findInMiddle == middleChessboardState->board.end() && findInLast == lastChessboardState->board.end()) {
            for (auto j : middleChessboardState->board) {
                auto findInFirst = find(board.begin(), board.end(), j);
                findInLast = find(lastChessboardState->board.begin(), lastChessboardState->board.end(), j);

                if (findInFirst == board.end() && findInLast == lastChessboardState->board.end()) {
                    for (auto k : lastChessboardState->board) {
                        findInFirst = find(board.begin(), board.end(), k);
                        findInMiddle = find(middleChessboardState->board.begin(), middleChessboardState->board.end(), k);

                        if (findInFirst == board.end() && findInMiddle == middleChessboardState->board.end()) {
                            int dx1 = j.first - i.first;
                            int dy1 = j.second - i.second;
                            int dx2 = k.first - j.first;
                            int dy2 = k.second - j.second;

                            if (dx1 == dx2 && dy1 == dy2) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}
