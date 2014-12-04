/**
*   @author - John Allard
*   @file   - CYOA.h
*   @data   - 12/02/2014
*   @info   - This is the header file that declares the CYOA class. CYOA stands for choose-your-own-adventure, and this class encapsulates this game. 
*             The purpose of this class is to remove and encapsulate any game-logic from a main function. All the main function should have to do is
*             CYOA->run(), gather std::input from the user, pass input to this class, and wait to see if any exceptions occur.
*             This class should handle the rest of the games functionality.
*
**/

#ifndef _CYOA_H_
#define _CYOA_H_

#include "../Room/Room.h"
#include "../Stack/Stack.h"
#include "../GraphAdjList/DirectedGraph/dGraph.h"

#include <fstream>
#include <iostream>

class CYOA {


public:

    ////////////////////////////////////////
    ////// Public Interface Functions //////
    ////////////////////////////////////////
    CYOA();

    ~CYOA();

    bool parseInputfile(std::string);

    bool startGame();

private:

    //////////////////////////////////////
    ////// Private Member Functions //////
    //////////////////////////////////////
    char getNextInput();

    int getFileLines(std::string, std::string *);

    bool validateCommand(char, char, std::string);



    //////////////////////////////////////
    ///////// Private Data ///////////////
    //////////////////////////////////////
    dGraph<Room> graph;

    Stack history_stack;

    char current_input;

};

#include "CYOA.cpp"
#endif