#include <iostream>
#include "SolverDFS.h"
#include "ModelChess.h"

using namespace std;
/*
 * @author Jędrzej Kalisiak
 * @author Adrianna Małkiewicz
 * @author Aleksandra Rybak
 * @version 1.0
 */

/*
 * Gets chessboard size (obligatory) and seed to generate start state (optional) from command line.
 * Sets up random generator - with seed if given, or with current time if not.
 * Creates model, adds solver and solves the problem.
 */

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "No parameter provided!" << endl;
        return 0;
    }

    int size;
    sscanf(argv[1], "%d", &size);

    if (size < 4) {
        cout << "Minimum size of chessboard is 4!" << endl;
        return 0;
    }

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