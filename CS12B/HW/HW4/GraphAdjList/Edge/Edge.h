/**
*   @Author   - John H Allard Jr.
*   @File     - Edge.h
*   @Data     - 11/11/2014
*   @Purpose  - This is the definition of the Edge class, which will be used by the different Graph classes in this directory. 
*               uEdge is a simple data structure that contains references to the endpoint that it points to, it doesn't need to know where it is pointing from
*               because it will be in a list associated with the other vertex. This edge will also contain a weight. This wieght will have a default
*               value of 1, so if the user wishes to implement an unweighted graph they can still use this class
**/

#ifndef  EDGE_H
#define  EDGE_H


#include "../Vertex/Vertex.h"

template <class VertexType>
class Edge
{
public:
    // @func - Constructor
    // @args - #1 Vertex that the edge points to, #2 the weighting of the edge
    Edge(Vertex<VertexType> *, double = 1.0);

    // @func   - getVertex
    // @args   - None
    // @return - The vertex object pointed to by this edge. 
    Vertex<VertexType> * getVertex() const;

    // @func   - setVertex
    // @args   - Pointer to the vertex that you wish to set
    // @return - Bool indicating success or failure
    bool setVertex(Vertex<VertexType> *);

    // @func   - getNext
    // @args   - None
    // @return - The next edge in the list of outgoing edges contained by a single vertex
    Edge * getNext() const;

    // @func   - setNext #1
    // @args   - #1 Pointer to the next Edge object
    // @return - The vertex object pointed to by this edge. 
    bool setNext(Edge *);


    // @func - setWeight 
    // @arg  - #1 A double value representing the weight of the edge
    // @ret  - bool indicating success
    bool setWeight(double);


    // @func - getWeight 
    // @arg  - none
    // @ret  - the weight assocaited with this edge
    double getWeight() const;


private:

    // @info - The vertex that the edge is pointing to
    Vertex<VertexType> * vertex;

    // @info - The weight associated with this vertex, default value will be 1.0
    double weight;

    // @info - A pointer to the next edge object in the list
    Edge * nextEdge;

};

#include "Edge.cpp"
#endif