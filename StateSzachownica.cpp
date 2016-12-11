//
// Created by jedrek on 2016-12-03.
//

#include "StateSzachownica.h"

// Returns state's hash for easy comparison
long long int StateSzachownica::getHash() {
    long long h = 0;

    for (auto i : board) {
        h += (i.first + 1) * (i.second + 1) * (i.second + 1);
    }

    return h;
}

int StateSzachownica::getHeuristic() {
    return getCollisions();
}

bool StateSzachownica::isEqual(State *s) {
    StateSzachownica *ss = static_cast<StateSzachownica *>(s);
    ss->normalise();
    normalise();

    return equal(board.begin(), board.end(), ss->board.begin(), ss->board.end());

}

StateSzachownica::StateSzachownica(int nsize, int seed) {
    n = nsize;
    initRand(seed);
}

void StateSzachownica::initRand(int seed) {
    int count = n;
    srand(seed);

    int *ar = new int[n * n];
    for (int a = 0; a < n * n; a++) {
        ar[a] = 0;
    }

    vector<pair<int, int> > list;
    while (count) {
        int x = rand() % n;
        int y = rand() % n;
        if (ar[x + n * y] == 0) {
            ar[x + n * y] = count--;
            list.push_back(make_pair(x, y));
        }
    }

    board = list;
    delete ar;
}

StateSzachownica::StateSzachownica(const StateSzachownica &c) {
    n = c.n;
    board = c.board;
}

// Returns number of NOT properly ordered queens
int StateSzachownica::getCollisions() {
    int *xs = new int[n];
    int *ys = new int[n];
    int *diagsr = new int[2 * n ]; // \ diagonal
    int *diagsl = new int[2 * n ]; // / diagonal

    memset(xs, 0, n* sizeof(int));
    memset(ys, 0, n* sizeof(int));
    memset(diagsr, 0, (2 * n)* sizeof(int));
    memset(diagsl, 0, (2 * n)* sizeof(int));

    for (auto i: board) {
        xs[i.first]++;
        ys[i.second]++;
        diagsr[i.first + i.second]++;
        diagsl[i.first - i.second + n - 1]++;
    }

    int collisions = 0;
    for (auto i: board) {
          if (xs[i.first] > 1 ||
              ys[i.second] > 1 ||
              diagsr[i.first + i.second] > 1 ||
              diagsl[i.first - i.second + n - 1] > 1)
            collisions++;
    }

    return collisions;
}

bool StateSzachownica::move(unsigned int which, unsigned int where) {
    if (which >= n) return false;
    if (where >= 8) return false;

    pair<int, int> chess = board.at(which);

    switch (where) {
        case 0: {
            chess.first--;
            chess.second--;
            break;
        }
        case 1: {

            chess.second--;
            break;
        }
        case 2: {
            chess.first++;
            chess.second--;
            break;
        }
        case 3: {
            chess.first++;
            break;
        }
        case 4: {
            chess.first++;
            chess.second++;
            break;
        }
        case 5: {
            chess.second++;
            break;
        }
        case 6: {
            chess.first--;
            chess.second++;
            break;
        }
        case 7: {
            chess.first--;
            break;
        }
        default:;
    }

    if (chess.first >= 0 && chess.first < n && chess.second >= 0 && chess.second < n) {
        auto findIter = find(board.begin(), board.end(), chess);
        if (findIter == board.end()) {
            board.at(which) = chess;
            return true;
        }
    }

    return false;
}

void StateSzachownica::normalise() {
    std::sort(board.begin(), board.end(), [](auto &left, auto &right) {
        if (left.second < right.second) {
            return true;
        } else if (left.second == right.second) {
            return left.first < right.first;
        }

        return false;
    });
}

void StateSzachownica::print() {
    int *ar = new int[n*n];
    for (int b = 0; b < n*n; b++) {
        ar[b]=0;
    }

    int count=1;
    for(auto i : board){
        ar[i.first+n*i.second]=count++;
    }

    cout<<getHash()<<" "<<getHeuristic()<<endl;

    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
            cout<<' '<<ar[a*n+b];
        }
        cout<<endl;
    }
}
