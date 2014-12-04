/**
*   @author - John Allard
*   @file   - Room.h
*   @data   - 12/02/2014
*   @info   - This is the header file that declares the Room class. This class is used in the Choose-Your-Own-Adventure (CYOA) game that I
*             am building as part of assignment 4 for CS12 at UCSC, Fall 2014. This class defines a singel room that a user can be in during any 
*             one stage of the game. A room will contain a name for the room, a series of descriptor strings about the room, and a series of options
*             for the user to choose which room to go to next. This class will serve as the vertices for the directed graph that is used to make the game work.
*
**/

#ifndef _ROOM_H_
#define _ROOM_H_

#include <string>
#include <iostream>

class Room {

public:
    Room();
    Room(std::string);

    ~Room();

    std::string getName() const;
    bool setName(std::string);

    std::string * getDescriptors() const;
    int getNumDescriptors() const;
    bool setDescriptors(std::string *, int);
    bool addDescriptor(std::string);

    std::string * getOptions() const;
    int getNumOptions() const;
    bool setOptions(std::string *, int);
    bool addOption(std::string);

    bool operator==(const Room &other) const;
    bool operator!=(const Room &other) const;

    friend std::ostream& operator<<(std::ostream& os, const Room& dt);


private:
    std::string name;
    std::string * descriptors;
    std::string * room_options;
    int num_desc, num_opt;
    int max_desc, max_opt;

};

#include "Room.cpp"
#endif 