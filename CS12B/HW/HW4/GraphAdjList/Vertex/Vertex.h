/**
*   @Author   - John H Allard Jr.
*   @File     - Vertex.h
*   @Data     - 11/11/2014
*   @Purpose  - This is the definition of the vertex class, which will be used by the different Graph classes in this directory. This class is small, and serves
*               the purpose of wrapping a small amount of data and functions together to simplify the process of working with vertices in the Graph classes.
**/
#ifndef MY_VERTEX_H
#define MY_VERTEX_H

template<class VertexType>
class Vertex
{

public:

    // @func - Constructor #1
    // @args - none
    Vertex();

    // @func - Constructor #2
    // @args - #1 Data associated with the vertex, #2 Index associated with the vertex
    Vertex(VertexType);

    // Get the data that the vertex contains (templated)
    VertexType getData() const;

    // set the data that the vertex contains
    bool setData(VertexType);

private:

    // Data that the vertex contains
    VertexType data;

};
#include "Vertex.cpp"
#endif