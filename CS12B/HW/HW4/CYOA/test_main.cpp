#include <iostream>
#include <string>
#include "../Room/Room.h"
#include "../Stack/Stack.h"
#include "../GraphAdjList/DirectedGraph/dGraph.h"
#include "CYOA.h"

int main() {

    CYOA theGame; // our game object

    if(!theGame.parseInputFile("CYOA/new.adventure"))
        std::cout << "Input File Parsing Failed";

    theGame.startGame();


    return 0;
}