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
    graph.setIsMultiGraph(true);
}

CYOA::~CYOA() {

}


bool CYOA::startGame() {

    if(!graph.getNumVertices())
        return false;

    current_input = 't'; //getNextInput();
    Room current_room = graph.getVertex(first_room);

    printInfo(current_room);

    while(current_input != 'q') {
        std::cout << "\n\n";

        auto edges = graph.getAdjVertices(current_room);

        switch(current_input) {

            case 't' : break; // default first case

            case 'z' :
            if(history_stack.getNumItems() <= 1) {
                std::cout << "Already at First Room\n";
                break;
            }
            
            history_stack.pop();
            current_room = graph.getVertex(history_stack.peek());
            break;


            case 'r' :
            history_stack.clear();
            current_room = graph.getVertex(first_room);
            history_stack.push(first_room.getName());
            break;


            case 'y' :
            std::cout << current_room.getName() << "--";
            for(auto edge : edges)
                std::cout << edge.first.getName() << ", ";
            std::cout << "\n\n";
            break;


            default :
            int edge_choice = current_input - 'a'; 

            if(edge_choice >= edges.size()) {
                std::cout << "There are not " << edge_choice << " Options Available \n";
                break;
            }

            std::string * opt = current_room.getOptions();
            std::string temp = opt[edge_choice];

            // if it's a cycle back to the same room
            if(temp == current_room.getName())
                break;

            Room new_room;
            new_room = edges[edge_choice].first;
            current_room = graph.getVertex(new_room);
            history_stack.push(current_room.getName());
            printInfo(current_room);
            break;
        }
        current_input = getNextInput();
    }

}

bool CYOA::printInfo(Room room) {
    std::string * temp = room.getDescriptors();
    for(int i = 0; i < room.getNumDescriptors(); i++)
        std::cout << temp[i] << "\n";
    std::cout << "\n";

    temp = room.getOptions();
    for(int i = 0; i < room.getNumOptions(); i++)
        std::cout << (char)('a'+i) << ".) " << temp[i] << "\n";
}

char CYOA::getNextInput() {

    while(true) {
        char inp = getchar();
        std::cin.get();

        // std::cout << (int)inp << "__" << (int)'a' << "__" << (int)'l' << "\n\n";

        if((inp >= 'a' && inp <= 'l') || inp == 'q' || inp == 'r' || inp == 'y' || inp == 'z')
            return inp;
        else
            std::cout << "Invalid Input, Try Again : \n";
    }

}


bool CYOA::parseInputFile(std::string fn) {

    // reset member values
    graph = dGraph<Room>();
    history_stack = Stack();

    int numLines = -1;
    char lastCommand = '_';
    Room currentRoom;
    bool seen_first_room = false;

    lines = this->getFileLines(fn, numLines);

    if(numLines == -1)
        return false;

    for(int i = 0; i < numLines; i++) {

        std::string line = lines[i];

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

        switch(command) {
        case 'r' :
            
            temp.setName(input);
            if(graph.containsVertex(temp)) {
                currentRoom = graph.getVertex(temp);
            }
            else {
                if(!seen_first_room) {
                    this->first_room = temp;
                    seen_first_room = true;
                }
                graph.insertVertex(temp);
                currentRoom = temp;
            }
        break;
            

        case 'd' :
            
            temp = currentRoom;

            if(!temp.addDescriptor(input)) 
                return false;
            

            if(!graph.updateVertex(currentRoom, temp))
                return false;
           
            currentRoom = temp;
        break;
        

        case('o'):
            // If this fails it means the user tried to add another option without fitting a tag to the previous option
            if(graph.getAdjVertices(currentRoom).size() > currentRoom.getNumOptions())
                return false;
          

            temp = currentRoom;
            temp.addOption(input);

            if(!graph.updateVertex(currentRoom, temp))
                return false;
           
            currentRoom = temp;
        break;


        case('t'):
            // If this fails it means the user is trying to add a tag when there is no current option
            if((graph.getAdjVertices(currentRoom).size() - currentRoom.getNumOptions()) != -1)
                return false;
            // if the vertex to bridge to is already in the map, just set an edge between the two.
            if(graph.containsVertex(input)) {
                graph.insertEdge(currentRoom, Room(input));
            }
            // else we have to create the new vertex and wait for it's internals to be updated later
            else {
                graph.insertVertex(Room(input));
                graph.insertEdge(currentRoom, Room(input));
            }   

        break;

        } // end switch statement
    } // end for-loop
    
    graph.printGraph();
    return true;
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
