#include <iostream>
#include <string>
#include "../Room/Room.h"
#include "../Stack/Stack.h"
#include "../GraphAdjList/DirectedGraph/dGraph.h"
#include "CYOA.h"

int main() {

    dGraph<Room> graph;
    Stack mystack;
    Room myRoom("hello");

    for(int i = 0; i < 10000; i++) {
        mystack.push("hey, there");
    }
    return 0;
}