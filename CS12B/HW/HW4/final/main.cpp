#include <iostream>
#include <string>
#include "Room.h"
#include "Stack.h"
#include "dGraph.h"
#include "CYOA.h"

int main(int arc, char *argv[]) {

    if(arc < 2) {
        std::cout << "ERROR : Must Enter A File As Arg[1]\n";
        return 0;
    }

    std::string fn(argv[1]);

    CYOA theGame; // our game ourbject

    if(!theGame.parseInputFile(fn)) {
        std::cout << "Input File Parsing Failed";
        return 1;
    }

    if(!theGame.startGame())
        return 1;

    return 0;
}