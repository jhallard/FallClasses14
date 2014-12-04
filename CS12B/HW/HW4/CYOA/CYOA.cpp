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


bool CYOA::parseInputFile(std::string fn) {

    int numLines = -1;
    char lastCommand = '_';
    Room currentRoom;

    lines = this->getFileLines(fn, numLines);

    if(numLines == -1)
        return false;

    for(int i = 0; i < numLines; i++) {

        std::string line = lines[i];

        // std::cout << "\n" << line << "\n";

        if(line.length() <= 1)
            continue;

        char command = line[0];

        int j = 1;
        for(; line[j] == ' '; j++);

        std::string input = line.substr(j, line.length());

        if(!this->validateCommand(command, lastCommand, input)) {
            
            return false;
        }

        lastCommand = command;

        Room temp;

        std::cout << command << " - " << input << "\n";

        switch(command) {
        case 'r' :
            std::cout << "case r\n\n";
            temp.setName(input);
            if(graph.containsVertex(temp)) {
                currentRoom = graph.getVertex(temp);
            }
            else {
                graph.insertVertex(temp);
                currentRoom = temp;

            }
        break;
            

        case 'd' :
            std::cout << "case d\n\n";
            temp = currentRoom;

            if(!temp.addDescriptor(input)) 
                return false;
            

            if(!graph.updateVertex(currentRoom, temp)) {
                return false;
            }

            currentRoom = temp;
        break;
        

        case('o'):
        std::cout << "case o\n\n";
            // If this fails it means the user tried to add another option without fitting a tag to the previous option
            if(graph.getAdjVertices(currentRoom).size() > currentRoom.getNumOptions())
                return false;
          

            temp = currentRoom;
            temp.addOption(input);

            if(!graph.updateVertex(currentRoom, temp)) {
                return false;
            }

            currentRoom = temp;

        break;


        case('t'):
            std::cout << "case t\n\n";
            // If this fails it means the user is trying to add a tag when there is no current option
            if((graph.getAdjVertices(currentRoom).size() - currentRoom.getNumOptions()) != -1) {
                std::cout << graph.getAdjVertices(currentRoom).size() << " _ " << currentRoom.getNumOptions() << "\n\n";
                return false;
            }
            
            std::cout << "b: " << graph.getAdjVertices(currentRoom).size() << "\n";
            // if the vertex to bridge to is already in the map, just set an edge between the two.
            if(graph.containsVertex(input)) {
                graph.insertEdge(currentRoom, Room(input));
            }
            // else we have to create the new vertex and wait for it's internals to be updated later
            else {
                graph.insertVertex(Room(input));
                graph.insertEdge(currentRoom, Room(input));
            }   

            std::cout << "a: " << graph.getAdjVertices(currentRoom).size() << "\n";

        break;

        } // end switch statement
    } // end for-loop
    
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


std::string * CYOA::getFileLines(std::string fn, int & numLines) {

    std::string line;
    numLines = 0;
    int max_lines = 1000;
    lines = new std::string[max_lines];
    std::ifstream newfile(fn);

    if (newfile.is_open()) {

        while(getline (newfile,line)){
            lines[numLines++] = line;
            // std::cout << line << "\n";
            if(numLines >= max_lines) {
                max_lines *= 2;
                std::string * temp = new std::string[max_lines];

                for(int i = 0; i < numLines; i++)
                    temp[i] = lines[i];

                lines = temp;
            }
        }

        newfile.close();
        return lines;
    }
    else {
        numLines = -1;
        return nullptr;
    }

}
