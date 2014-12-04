/**
*   @author - John Allard
*   @file   - Stack.h
*   @data   - 12/02/2014
*   @info   - This is my implementation of a stack data structure for use in assignment 4, CS12B, UCSC. This stack will keep 
*             track of the order of the room that are visited by the user, and will allow us to backtrack if needed 
*
**/

#include "Stack.h"

Stack::Stack() {
    this->num_items = 0;
    this->max_items = 100;

    this->stack_arr = new std::string[max_items];
}

Stack::~Stack() {

    if(stack_arr != nullptr)
        delete [] stack_arr;
}

std::string Stack::peek() const {
    if(!num_items)
        return std::string ();

    return this->stack_arr[num_items-1];
}

bool Stack::pop() {
    if(!num_items)
        return false;

    stack_arr[num_items--] = "";

    return true;
}

bool Stack::push(std::string new_item) {

    if(num_items < max_items) {
        stack_arr[num_items++] = new_item;
        return true;
    }

    max_items *= 2;

    std::string * temp = new std::string[max_items];

    for(int i = 0; i < num_items; i++)
        temp[i] = stack_arr[i];

    temp[num_items++] = new_item;

    delete [] stack_arr;

    stack_arr = temp;

    return true;

}

int Stack::getNumItems() const {
    return this->num_items;
}