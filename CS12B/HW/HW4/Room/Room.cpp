/**
*   @author - John Allard
*   @file   - Room.cpp
*   @data   - 12/02/2014
*   @info   - This is the source file that defines the Room class. This class is used in the Choose-Your-Own-Adventure (CYOA) game that I
*             am building as part of assignment 4 for CS12 at UCSC, Fall 2014. This class defines a singel room that a user can be in during any 
*             one stage of the game. A room will contain a name for the room, a series of descriptor strings about the room, and a series of options
*             for the user to choose which room to go to next. This class will serve as the vertices for the directed graph that is used to make the game work.
*
**/
#include "Room.h"

Room::Room() {
    this->setName("");
    this->num_desc = 0;
    this->max_desc = 100;
    this->descriptors = new std::string[max_desc];

    this->num_opt = 0;
    this->max_opt = 12;
    this->room_options = new std::string[max_opt];
}

Room::Room(std::string nm) {
    this->setName(nm);

    this->num_desc = 0;
    this->max_desc = 100;
    this->descriptors = new std::string[max_desc];

    this->num_opt = 0;
    this->max_opt = 12;
    this->room_options = new std::string[max_opt];
}

Room::Room(const Room & other) {

    this->setName(other.getName());
    this->num_desc = other.getNumDescriptors();
    this->max_desc = 2*num_desc+10;
    this->descriptors = new std::string[max_desc];

    this->num_opt = other.getNumOptions();
    this->max_opt = 12;
    this->room_options = new std::string[max_opt];

    for(int i = 0; i < num_desc; i++)
        descriptors[i] = other.getDescriptors()[i];

    for(int i = 0; i < num_desc; i++)
        room_options[i] = other.getOptions()[i];
}

Room::~Room() {

    if(this->room_options != nullptr)
        delete [] this->room_options;

    if(this->descriptors != nullptr)
        delete [] this->descriptors;
}

std::string Room::getName() const {
    return this->name;
}

bool Room::setName(std::string nm) {
    this->name = nm;
    return true;
}

std::string * Room::getDescriptors() const {
    return this->descriptors;
}

int Room::getNumDescriptors() const {
    return this->num_desc;
}

bool Room::setDescriptors(std::string * new_descriptors, int size) {
    if(size < 0)
        return false;

    this->descriptors = new_descriptors;
    this->num_desc = size;
    this->max_desc = size;

    return true;
}

bool Room::addDescriptor(std::string new_desc) {

    if(this->num_desc < this->max_desc) {
        descriptors[num_desc] = new_desc;
        this->num_desc++;
        return true;
    }
    std::cout << "case r\n";
    max_desc *= 2;
    std::string * temp = new std::string[max_desc];

    for(int i = 0; i < num_desc; i++) {
        temp[i] = descriptors[i];
    }

    temp[num_desc] = new_desc;
    num_desc++;

    std::cout << "case r\n";
    if(descriptors != nullptr)
        delete [] descriptors;
    std::cout << "case r\n";

    descriptors = temp;

    return true;

}


std::string * Room::getOptions() const {
    return this->room_options;
}

int Room::getNumOptions() const {
    return this->num_opt;
}

bool Room::setOptions(std::string * new_options, int size) {

    if(size < 0)
        return false;

    this->room_options = new_options;
    this->num_opt = size;
    this->max_opt = size;

    return true;
}

bool Room::addOption(std::string new_opt) {

    if(this->num_opt < this->max_opt) {
        room_options[num_opt] = new_opt;
        this->num_opt++;
        return true;
    }

    max_opt *= 2;
    std::string * temp = new std::string[max_opt];

    for(int i = 0; i < num_opt; i++) {
        temp[i] = room_options[i];
    }

    temp[num_opt] = new_opt;
    num_opt++;

    delete(room_options);

    room_options = temp;

    return true;
}

bool Room::operator==(const Room &other) const
{ 
    return (this->name == other.getName()) &&
           (this->num_desc == other.getNumDescriptors());
}

bool Room::operator!=(const Room &other) const
{ 
    return !(*this == other);
}

bool Room::operator=(const Room &other) {

    if(!room_options) delete [] room_options;
    if(!descriptors) delete [] descriptors;

    std::string temp = other.getName();
    this->setName(temp);
    this->num_desc = other.getNumDescriptors();
    this->max_desc = 2*num_desc+10;
    this->descriptors = new std::string[max_desc];

    this->num_opt = other.getNumOptions();
    this->max_opt = 12;
    this->room_options = new std::string[max_opt];

    for(int i = 0; i < num_desc; i++)
        descriptors[i] = other.getDescriptors()[i];

    for(int i = 0; i < num_desc; i++)
        room_options[i] = other.getOptions()[i];
}

std::ostream& operator<<(std::ostream& os, const Room& dt)
{
    os << dt.name;
    return os;
}


namespace std {

  template <>
  struct hash<Room>
  {
    std::size_t operator()(const Room& k) const
    {
      using std::size_t;
      using std::hash;
      using std::string;

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:
      if(k.getName().length())
        return hash<std::string>()(k.getName());
      else
        return hash<std::string>()("HelloTherexx");

    }
  };

}
