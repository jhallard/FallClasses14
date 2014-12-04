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

    if(numLines == -1)
        return false;




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
