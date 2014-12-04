#include "Vertex.h"

// @func - Constructor #1
// @args - none
template<class VertexType> 
Vertex<VertexType>::Vertex()  {

}

// @func - Constructor #2
// @args - #1 Data associated with the vertex, #2 Index associated with the vertex
template<class VertexType> 
Vertex<VertexType>::Vertex(VertexType newdata) : data(newdata){ }


// Get the data that the vertex contains (templated)
template<class VertexType> 
VertexType Vertex<VertexType>::getData() const{
    return this->data;
}

// set the data that the vertex contains
template<class VertexType> 
bool Vertex<VertexType>::setData(VertexType newData) {
    this->data = newData;
    return true;
}
