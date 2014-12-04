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

#include "CYOA.h"

CYOA::CYOA() {
    current_input = '\0';
}

CYOA::~CYOA() {

}


bool CYOA::startGame() {

}

char CYOA::getNextInput() {

}


bool CYOA::parseInputfile(std::string fn) {

    std::string * lines;
    int numLines = this->getFileLines(fn, lines);
    Room * currentRoom = new Room();

    if(numLines == -1)
        return false;

    char lastCommand = '_';
    for(int i  = 0; i < numLines; i++) {

        std::string line = lines[i];

        if(line.length() <= 1)
            continue;

        char command = line[0];

        int j = 1;
        for(; line[j] == ' '; j++);

        std::string input = line.substr(j);

        if(!this->validateCommand(command, lastCommand, input))
            return false;

        lastCommand = command;

        Room temp;

        switch(command) {

            case 'r' :
                temp.setName(input);
                if(this->graph.containsVertex(temp))
                    *currentRoom = graph.getVertex(temp);
                else {
                    graph.insertVertex(temp);
                    *currentRoom = temp;
                }
            break;
            

            case 'd' :
                temp = *currentRoom;

                if(!temp.addDescriptor(input))
                    return false;

                graph.updateVertex(*currentRoom, temp);

                *currentRoom = temp;
            break;
            

            case('o'):
                if(graph.getAdjVertices(*currentRoom).size() - currentRoom->getNumOptions() > 1)
                    return false;



            break;


            case('t'):

            break;



        }
    }

}

bool CYOA::validateCommand(char currentCommand, char lastCommand, std::string input) {

    // the first command must be a new room
    if(lastCommand == '_' && currentCommand != 'r')
        return false;

    switch(currentCommand) {

        case('r'):
            if(lastCommand == 'r')
                return false;
            if(lastCommand == 'o')
                return false;
        break;
        

        case('d'):

        break;
        

        case('o'):

        break;


        case('t'):

        break;

    }

    return true;
}


int CYOA::getFileLines(std::string fn, std::string * lines) {

    std::string line;
    int numlines = 0;
    int max_lines = 1000;
    lines = new std::string[max_lines];
    std::ifstream newfile (fn);

    if (newfile.is_open()) {

        while(getline (newfile,line)){
            lines[numlines++] = line;

            if(numlines >= 1000) {
                max_lines *= 2;
                std::string * temp = new std::string[max_lines];
                for(int i = 0; i < numlines; i++)
                    temp[i] = lines[i];

                delete [] lines;

                lines = temp;

            }
        }

    newfile.close();
    return numlines;
    }

    else
        return -1;

}
