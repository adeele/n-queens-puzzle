#include <iostream>
#include "SolverDFS.h"
#include "ModelChess.h"

using namespace std;

int main() {
    ModelChess modelChess(5);
    SolverDFS solverDFS;

    solverDFS.setModel(modelChess);
    shared_ptr<State> finalState = solverDFS.solve();

    return 0;
}