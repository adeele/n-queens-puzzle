#include <iostream>
#include "SolverDFS.h"
#include "ModelChess.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "No parameter provided!";
        return 0;
    }

    int size;
    sscanf(argv[1], "%d", &size);

    if (argc == 3) {
        int seed;
        sscanf(argv[2], "%d", &seed);
        srand(seed);

    } else {
        srand(time(NULL));
    }

    ModelChess modelChess(size);
    SolverDFS solverDFS;

    solverDFS.setModel(modelChess);
    shared_ptr<State> finalState = solverDFS.solve();

    return 0;
}