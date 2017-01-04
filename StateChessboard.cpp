//
// Created by jedrek on 2016-12-03.
//

#include "StateChessboard.h"


// Returns state's hash for easy comparison
long long int StateChessboard::getHash() {
    long long hash = 0;

    for (auto i : board) {
        hash += (i.first + 1) * (i.second + 1) * (i.second + 1);
    }

    return hash;
}

int StateChessboard::getHeuristic() {
    return getCollisions();
}

bool StateChessboard::isEqual(State *stateToCompare) {
    StateChessboard *chessboardStateToCompare = static_cast<StateChessboard *>(stateToCompare);
    chessboardStateToCompare->normalise();
    normalise();

    return equal(board.begin(), board.end(), chessboardStateToCompare->board.begin(), chessboardStateToCompare->board.end());
}

StateChessboard::StateChessboard(int chessboardSizeToSet, int seed) {
    chessboardSize = chessboardSizeToSet;
    possibleMoves = 8;
    initRandom(seed);
}

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

StateChessboard::StateChessboard(const StateChessboard &stateToAssign) {
    chessboardSize = stateToAssign.chessboardSize;
    board = stateToAssign.board;
    possibleMoves = 8;
}

// Returns number of NOT properly ordered queens
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

int StateChessboard::getPossibleMoves() {
    return possibleMoves;
}

void StateChessboard::normalise() {
    std::sort(board.begin(), board.end(), [](auto &left, auto &right) {
        return left.second < right.second ||
               (left.second == right.second && left.first < right.first);
    });
}

void StateChessboard::print() {
    int *array = new int[chessboardSize * chessboardSize]();
    int count = 1;

    for (auto i : board) {
        array[i.first + chessboardSize * i.second] = count++;
    }

    for (int i = 0; i < chessboardSize; i++) {
        for (int j = 0; j < chessboardSize; j++) {
            cout << " " << array[i * chessboardSize + j];
        }

        cout << endl;
    }

    cout << endl;
}
