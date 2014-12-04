/**
*   @author - John Allard
*   @file   - Stack.h
*   @data   - 12/02/2014
*   @info   - This is my implementation of a stack data structure for use in assignment 4, CS12B, UCSC. This stack will keep 
*             track of the order of the room that are visited by the user, and will allow us to backtrack if needed 
*
**/

#ifndef _MY_STACK_H_
#define _MY_STACK_H_

#include <string>

class Stack {

public:

    Stack();

    ~Stack();

    std::string peek() const;
    bool pop();

    bool push(std::string);

    int getNumItems() const;

private:
    std::string * stack_arr;
    int num_items, max_items;
};

#include "Stack.cpp"

#endif