#include <iostream>
#include <string>
#include "../Room/Room.h"
#include "../Stack/Stack.h"
#include "../GraphAdjList/DirectedGraph/dGraph.h"
#include "CYOA.h"

int main() {

    CYOA theGame;

    if(!theGame.parseInputFile("CYOA/testinput.txt"))
        std::cout << "NONONONO";

    theGame.startGame();
    return 0;
}