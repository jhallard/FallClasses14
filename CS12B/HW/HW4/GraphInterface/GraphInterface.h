/**
*   @Author   - John H Allard Jr.
*   @File     - GraphInterface.h
*   @Data     - 11/11/2014
*   @Purpose  - Defines an interface for a graph data structure. As C++ has no true interfaces, this class consists purely of public virtual functions,
*               which ensures that the all of the graphs I build (un/directed, adjacency lists, adjacency matrices, etc), which will derive 
*               from this interface, must implement every function listed below. To see graph implementations that use this interface, look inside
*               of the GraphAdjList or GraphAdjMat directories. All code is open license and free to use, just leave some
*               sort of note in your source code giving credit to me and a link to my github (github.com/jhallard)
**/

#ifndef GraphInterface_h
#define GraphInterface_h

#include <unordered_map>
#include "../GraphAdjList/Edge/Edge.h"
#include "../GraphAdjList/Vertex/Vertex.h"

template<class VertexType>
class GraphInterface
{
public:

    // @func   - insertVertex
    // @args   - #1 The value of the node to be inserted
    // @return - Boolean indicating succes 
    virtual bool insertVertex(VertexType) = 0;

    // @func   - deleteVertex
    // @args   - Vertex data of the node to be deleted
    // @return - Boolean indicating success 
    virtual bool deleteVertex(VertexType) = 0;

    // @func   - deleteVertices
    // @args   - #1 Vector of Vertex data corresponding to the vertices to be added.
    // @return - Boolean indicating succes 
    virtual bool insertVertices(std::vector<VertexType>) = 0;

    // @func   - deleteVertices
    // @args   - #1 Vector of Vertex data corresponding to the vertices to be deleted.
    // @return - Boolean indicating success 
    virtual bool deleteVertices(std::vector<VertexType>) = 0;


    // @func   - insertEdge
    // @args   - #1 The "From" Node, #2 the "To" Node, #3 the weight for this new edge 
    // @return - Boolean indicating succes 
    virtual bool insertEdge(VertexType, VertexType, double = 1.0) = 0;

    // @func   - deleteEdge
    // @args   - #1 The "From" Node, #2 the "To" Node.
    // @return - Boolean indicating succes 
    virtual bool deleteEdge(VertexType, VertexType) = 0;

    // @func   - getNumVertices
    // @args   - None
    // @return - The number of vertices currently in the graph.
    virtual int getNumVertices() const = 0;

    // @func   - getNumEdges
    // @args   - None
    // @return - The number of edges currently in the graph.
    virtual int getNumEdges() const = 0;

    // @func   - containsVertex
    // @args   - #1 data associated with the vertex that you wish to query for existence 
    // @return - Bool corresponding to the existence of a vertex with the given data in this graph
    virtual bool containsVertex(VertexType) = 0;

    // @func   - getEdgeWeight
    // @args   - #1 data associated with vetex #1, data associated with vertex #2
    // @return - returns the weight of the edge, throws error if edge not found
    virtual double getEdgeWeight(VertexType, VertexType) = 0;

    // @func   - getAdjVertices
    // @args   - #1 Data contained in vertex that you wish to recieve a list of adjacent vertices of.
    // @return - Vector of pairs, first item is an adjacent vertex, second is the weight of the edge between the two vertices.
    virtual std::vector< std::pair<VertexType, double> > getAdjVertices(VertexType) = 0;

    // @func   - makeGraphDense
    // @args   - #1 Weight to assign to all edges in the new graph.
    // @return - Bool indicating success
    // @info   - This function removes all current edes from the graph, and instead makes a dense graph out of the current vertices with uniform
    //           edge weighting specified by the argument to the function.
    // virtual bool makeGraphDense(double weight = 1.0) = 0;

    // @func   - isConnected
    // @args   - None
    // @return - Bool indicating whether or not the graph is connected
    // @info   - This function searches through the given graph to see if any given vertex can be reached from any other given vertex
    virtual bool isConnected() = 0;

    // @func   - depthFirst
    // @args   - #1 Data associated with the starting vertex for the search, #2 function pointer that takes a set of vertex data as an argument
    // @return - Bool indicatingetN if the function could find the starting vertex based on arg#1
    // @info   - Performs a depth first traversal, calling the visit() function on each item. This function assumes that all vertex data is unique,
    //           so if this is a graph of strings, no two strings should be the same. This precondition allows us to use an std::unordered_map to keep
    //           track of the seen and unseen vertices.
    virtual bool depthFirst(VertexType, void visit(VertexType&)) = 0;

    // @func   - breadthFirst
    // @args   - #1 Data associated with the starting vertex for the search, #2 function pointer that takes a set of vertex data as an argument
    // @return - Bool indicating if the function could find the starting vertex based on arg#1
    // @info   - Performs a breadth first traversal, calling the visit() function on each item. This function assumes that all vertex data is unique,
    //           so if this is a graph of strings, no two strings should be the same. This precondition allows us to use an std::unordered_map to keep
    //           track of the seen and unseen vertices.
    virtual bool breadthFirst(VertexType, void visit(VertexType&)) = 0;

    // @func   - minimuminCut
    // @args   - none
    // @return - 2 column vector of vertices, each column representing one half of the cut. 
    // @info   - Partitions the current graph into two subsets that have at the minmum number of edges between them.
    virtual std::vector<std::vector<VertexType> > minimumCut() = 0;

    // @func   - minimuminSpanningTree
    // @args   - none
    // @return - A graph that represents the minimum spanning tree of the current graph object. 
    // @info   - This function is declared to return a GraphInterface object, but since GraphInterface is abstract, what will really happen is that any of the
    //           classes derived from this one will simply return a graph of their own type when implementing this function. (See uGraph for an example).
    virtual GraphInterface<VertexType> * minimumSpanningTree() = 0;

    // @func   - dijkstras
    // @args   - #1 Data contained in starting vertex for search
    // @return - Vector containing, in-order, the vertices to take to reach your goal. Empty if you are there or no path exists.
    // @info   - Performs the A* path-finding algorithm to get from a starting vertex to any goal vertex in a list of vertices. 
    virtual std::pair<std::unordered_map<VertexType, VertexType>, std::unordered_map<VertexType, double> > dijkstras(VertexType) = 0;

    // @func   - dijkstrasComputePath
    // @args   - #1 Source Vertex, #2 Dest Vertex
    // @return - A pair consisting of #1Vector of vertices that lead from the source vertex to the destination vertex along the shortest path, 
    //           #2 the net weight along that path betweent he two vertices.
    virtual std::pair<std::vector<VertexType>, double>dijkstrasComputePath(VertexType, VertexType) = 0;


    // @func   - aStar
    // @args   - #1 Data contained in starting vertex for search, #2 Vector of possible goal vertices to reach, #3 Pointer to a hueristic function on a given node
    // @return - Vector containing, in-order, the vertices to take to reach your goal. Empty if you are there or no path exists.
    // @info   - Performs the A* path-finding algorithm to get from a starting vertex to any goal vertex in a list of vertices. 
    virtual std::vector<VertexType> aStar(VertexType, std::vector<VertexType>, double hueristic(VertexType&, VertexType&)) = 0;


};

#endif