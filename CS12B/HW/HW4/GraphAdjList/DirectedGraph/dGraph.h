/**
*   @Author   - John H Allard Jr.
*   @File     - dGraph.h
*   @Date     - 11/12/2014
*   @Repo     - https://github.com/jhallard/DataStructures/Graphs
*   @Purpose  - This is my declaration of the dGraph (directed Graph) class. This class represents a templated, 
*               directed graph, upon which a user can perform operation like searches, path finding, and other things. 
*               This class was implemented as part of my C++. Data Structures personal project. All code is open license and free to use, just leave some
*               sort of note in your source code giving credit to me and a link to my github (github.com/jhallard)
*
*   @Details  - This class uses a series of adjacency lists to represent a graph data structure. An adjacency list consista vertex and a list 
*               of edges that eminate from this vertex to the other vertices in the map, along with the weight associated with those edges. 
*               Thus if some vertex v had edges connected it with vertices a, b, c, d, and e, the adj list for vertex v would look like :
*               v -> a* -> b* -> c* -> d* -> null
*               Where x* is an edge that leads from vertex v to vertex x. Thus to find all of the edges that eminate from a given vertex v, you just need to
*               traverse the list of edges on the AdjList that contains vertex v.
*               This above is just one adjacency list, our graph will have a single adjacency list for each vertex in the graph. So our graph data structure
*               will look more like this :
*               -----------------------------------
*             1 |   a  -> c* -> d* -> null        |
*             2 |   b  -> v* -> d* -> e* -> null  |
*             3 |   c  -> a* -> v* -> e* -> null  |
*             4 |   d  -> a* -> b* -> null        | 
*             5 |   e  -> b* -> c* -> v* -> null  |
*             6 |   v  -> b* -> c* -> null        |
*               -----------------------------------
*
*               Inheritance Hierarchy :
*               This class inherits from the pure, virtual GraphInterface class (GraphInterface/GraphInterface.h). This interface specifies exactly what functions
*               both the undirected and directed graph classes that I make must publically implement. This is done to help ensure that the all user interaction
*               with the graph in well planned out, consistent, and doesn't derive itself in any way from the implementation details of the graph. This should allow
*               me to make amny different representations of graphs (adjlist's, adjmatrices, etc.) that can all be used in the exact same way by the user.
*
*               Time Complexity :
*               Below is a break down of the time and space complexity for the various operations performed by this graph.
*               #TODO - List Big-O's for all of the important functions in this class.
**/

#ifndef D_GRAPH_A_LIST_H
#define D_GRAPH_A_LIST_H

#include <stdexcept>
#include <vector>
#include <string>
#include <stdexcept>
#include <deque>
#include <unordered_map>
#include <set>
#include <iostream>         // needed for printGraph function..
#include <limits>
#include <random>

#include "../../GraphInterface/GraphInterface.h"
#include "../AdjacencyList/AdjList.h"
#include "../Vertex/Vertex.h"
#include "../Edge/Edge.h"


template <class VertexType> // VertexType is whatever type of data you want your vertices to hold (ints, strings, custom classes, etc.)
class dGraph : public GraphInterface <VertexType>
{


//////////////////////////////////////////////////////
////////         PUBLIC INTERFACE       //////////////
//////////////////////////////////////////////////////
public:

    // @func - Constructor#1
    // @args - None
    // @info - Initializes everything to empty
    dGraph();

    // @func  - Constructor#2
    // @args  - #1 String that contains the filename from which to load a graph
    // @error - Can throw IO error if invalid filename or file structure to build graph 
    dGraph(std::string fn);

    // @func  - Copy Constructor
    // @args  - dGraph object that you wish to make this a copy of
    dGraph(const dGraph<VertexType> &);

    // @func  - Destructor
    // @info  - Cleans up the dynamically allocated AdjList objects contains in the list vector.
    ~dGraph();

    // @func   - insertVertex
    // @args   - #1 The value of the node to be inserted
    // @return - Boolean indicating succes 
    bool insertVertex(VertexType);

    // @func   - deleteVertex
    // @args   - none
    // @return - Boolean indicating success 
    bool deleteVertex(VertexType);

    // @func   - getAllVertices
    // @args   - none
    // @return - Vector of the data contained inside all vertices. 
    std::vector<VertexType> getAllVertices();

    // @func   - updateVertex
    // @args   - #1 - Data contained by the vertex to be updated, #2 The new data to insert into that verex
    // @return - Boolean indicating success, returns false if it can't find the vertex to update.
    bool updateVertex(VertexType, VertexType);

    // @func   - deleteVertices
    // @args   - #1 Vector of Vertex data corresponding to the vertices to be added.
    // @return - Boolean indicating succes 
    bool insertVertices(std::vector<VertexType>);

    // @func   - deleteVertices
    // @args   - #1 Vector of Vertex data corresponding to the vertices to be deleted.
    // @return - Boolean indicating success 
    bool deleteVertices(std::vector<VertexType>);

    // @func   - insertEdge
    // @args   - #1 The "From" Node, #2 the "To" Node, #3 The weight for this new edge 
    // @return - Boolean indicating succes 
    bool insertEdge(VertexType, VertexType, double = 1.0);

    // @func   - deleteEdge
    // @args   - #1 The "From" Node, the "To" Node. 
    // @return - Boolean indicating succes 
    bool deleteEdge(VertexType, VertexType);

    // @func   - numVertices
    // @args   - None
    // @return - The number of vertices currently in the graph.
    int getNumVertices() const;

    // @func   - numEdges
    // @args   - None
    // @return - The number of edges currently in the graph.
    int getNumEdges() const;

    // @func   - containsVerex
    // @args   - #1 data associated with the vertex that you wish to query for existence 
    // @return - Bool corresponding to the existence of a vertex with the given data in this graph
    bool containsVertex(VertexType);

    // @func   - getEdgeWeight
    // @args   - #1 data associated with vetex #1, data associated with vertex #2
    // @return - returns the weight of the edge, throws error if edge not found
    double getEdgeWeight(VertexType, VertexType);

    // @func   - getAdjVertices
    // @args   - Data contained in vertex that you wish to recieve a list of adjacent vertices of.
    // @return - Vector of pairs, first item is the vertex that the edge points to, second is the weight of that edge.
    std::vector< std::pair<VertexType, double> > getAdjVertices(VertexType);

    // @func   - printGraph
    // @args   - none
    // @return - none
    // @info   - prints the adjecency list representation of the graph to the console.
    void printGraph();

    // @func   - isConnected
    // @args   - None
    // @return - Bool indicating whether or not the graph is connected
    // @info   - This function uses BFS to search to see if any given vertex can be reached from any other given vertex
    bool isConnected();

    // @func   - setIsMultiGraph
    // @args   - boolean to be stored in isMultiGraph
    // @return - Bool indicating success
    bool setIsMultiGraph(bool);

    // @func   - getIsMultiGraph
    // @args   - None
    // @return - Bool value of isMultiGraph
    bool getIsMultiGraph();

    // @func   - depthFirst
    // @args   - #1 Data associated with the starting vertex for the search, #2 function pointer that takes a set of vertex data as an argument
    // @return - Bool indicating if the function could find the starting vertex based on arg#1
    // @info   - Performs a depth first traversal, calling the visit() function on each item. This function assumes that all vertex data is unique,
    //           so if this is a graph of strings, no two strings should be the same. This precondition allows us to use an std::unordered_map to keep
    //           track of the seen and unseen vertices.
    bool depthFirst(VertexType, void visit(VertexType&));

    // @func   - breadthFirst
    // @args   - #1 Data associated with the starting vertex for the search, #2 function pointer that takes a set of vertex data as an argument
    // @return - Bool indicating if the function could find the starting vertex based on arg#1
    // @info   - Performs a breadth first traversal, calling the visit() function on each item. This function assumes that all vertex data is unique,
    //           so if this is a graph of strings, no two strings should be the same. This precondition allows us to use an std::unordered_map to keep
    //           track of the seen and unseen vertices.
    bool breadthFirst(VertexType, void visit(VertexType&));

    // @func   - minimuminCut
    // @args   - none
    // @return - 2 column vector of vertices, each column representing one half of the cut. 
    // @info   - Partitions the current graph into two subsets that have at the minmum number of edges between them.
    std::vector<std::vector<VertexType> > minimumCut();

    // @func   - minimuminSpanningTree
    // @args   - none
    // @return - A graph that represents the minimum spanning tree of the current graph object. 
    // @info   - This function will return another dGraph object that has the edges reduces to those that exist in the minimum spanning tree
    //           of the veritces in this graph. Will throw an exception is the graph is not connected. 
    dGraph<VertexType> * minimumSpanningTree();

    // @func   - dijkstras
    // @args   - #1 Data contained in starting vertex for search
    // @return - A pair containing two maps. The first map takes a vertex and returns the previuos vertex in the path there from the source vertex. 
    //           The second map takes a vertex and gives the total weight that it takes to get there from the source vertex.
    // @info   - Performs Dijkstra's path-finding algorithm to get from a starting vertex to any goal vertex in the map, throws an exception if
    //           the source vertex is not contained in the map.
    typename dGraph<VertexType>::dist_prev_pair dijkstras(VertexType);

    // @func   - dijkstrasComputePath
    // @args   - #1 Source Vertex, #2 Dest Vertex
    // @return - A pair consisting of #1Vector of vertices that lead from the source vertex to the destination vertex along the shortest path, 
    //           #2 the net weight along that path betweent he two vertices.
    std::pair<std::vector<VertexType>, double> dijkstrasComputePath(VertexType, VertexType);


    // @func   - aStar
    // @args   - #1 Data contained in starting vertex for search, #2 Vector of possible goal vertices to reach, #3 Pointer to a hueristic function on a given node
    // @return - Vector containing, in-order, the vertices to take to reach your goal. Empty if you are there or no path exists.
    // @info   - Performs the A* path-finding algorithm to get from a starting vertex to any goal vertex in a list of vertices. 
    std::vector<VertexType> aStar(VertexType, std::vector<VertexType>, double hueristic(VertexType&, VertexType&));



//////////////////////////////////////////////////////
////////           PRIVATE DATA      /////////////////
//////////////////////////////////////////////////////
private:
    // @typedef - (too long to retype)
    // @info    - This is a pair of unordered_maps that is returned from the dijkstras algorithm to the helper function. Contained inside these two maps
    //            is both the shortest path from the source vertex to any other node in the graph, and the net weight along that path. These two maps are 
    //            decoded inside the helper function to return a single shortest path between two vertices, so the user doesn't have to decode it themselves.
    typedef std::pair<std::unordered_map<VertexType, VertexType>, std::unordered_map<VertexType, double> > dist_prev_pair;
    
    // @member - numVertices
    // @info   - Number of vertices currently in the graph
    int numVertices;

    // @member - numEdges
    // @info   - Number of Edges currently in the graph
    int numEdges;

    // @member - list
    // @info   - A vector of pointers to adjacency lists, one adjlist for each vertex in our graph. Each adjlist represents that vertex and all of the edges eminating
    //           from it to other vertices in the graph
    std::vector< AdjList<VertexType> * > list;

    // @member - lookupMap
    // @info   - Allows us to look up where in our vector of vertices a vertex with a given set of VertexData is. This allows us
    //           to have an (amortized) O(1) lookup time to find a Vertex given a piece of VertexData, as apposed to scanning linearly through
    //           our vector of AdjLists. 
    //           KeyType - VertexData (int, string, double, etc. Chosen at runtime by the user)
    //           Value   - A pointer to the AdjList object for the Vertex that contains the data contained by the key.
    std::unordered_map<VertexType,  AdjList<VertexType> *> lookupMap;

    // @member - isMultiGraph
    // @info   - This is intended to be used by the minimumCut function, because it requires that duplicate edges be valid. Setting this to true
    //           will change the AdjList class to not reject duplicate edges, but it will still reject edges between the same vertex.
    bool isMultiGraph;

    // @member - connectivityCount
    // @info   - Used by the isConnected function to count reachable vertices
    int connectivityCount;



//////////////////////////////////////////////////////
////////       PRIVATE FUNCTIONS     /////////////////
//////////////////////////////////////////////////////

    // @func   - findVertex
    // @args   - #1 Value contained in the vertex to be found
    // @return - pointer to the vertex to be found, null if not found
    // @info   - Goes through our vector of vertices and find which one (if any) contain the data given by the argument
    AdjList<VertexType> *  findVertex(VertexType);


};

#include "dGraph.cpp"
#endif