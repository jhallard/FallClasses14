/**
*   @Author   - John H Allard Jr.
*   @File     - uGraph.h
*   @Date     - 11/12/2014
*   @Repo     - https://github.com/jhallard/DataStructures/Graphs
*   @Purpose  - This is my definition of the uGraph (undirected Graph) class. This class represents a templated, 
*               undirected graph, upon which a user can perform operations like searches, path finding, minimium-cut, etc. 
*               This class was implemented as part of my C++ Data Structures personal project. All code is open license and free to use,
*                just leave some sort of note in your source code giving credit to me and a link to my github (github.com/jhallard)
*
*   @Details  - This class uses a series of adjacency lists to represent a graph data structure. An adjacency list consists of a vertex and a list 
*               of edges that eminate from this vertex to the other vertices in the map, along with the weight associated with those edges. 
*               Thus if some vertex v had edges connected it with vertices a, b, c, d, and e, the adj list for vertex v would look like :
*               v -> a* -> b* -> c* -> d* -> e* -> null
*               Where x* is an edge that leads from vertex v to vertex x. Thus to find all of the edges that eminate from a given vertex v, 
*               you just need to traverse the list of edges on the AdjList that contains vertex v.
*               This above is just one adjacency list, our graph will have a single adjacency list for each vertex in the graph. So our graph
*                data structure will look more like this :
*               -----------------------------------
*    vertex 1 : |   a  -> c* -> d* -> null        |
*    vertex 2 : |   b  -> v* -> d* -> e* -> null  |
*    vertex 3 : |   c  -> a* -> v* -> e* -> null  |
*    vertex 4 : |   d  -> a* -> b* -> null        | 
*    vertex 5 : |   e  -> b* -> c* -> v* -> null  |
*    vertex 6 : |   v  -> b* -> c* -> null        |
*               -----------------------------------
*
*               Inheritance Hierarchy :
*               This class inherits from the pure, virtual GraphInterface class (../../GraphInterface/GraphInterface.h). This interface specifies 
*               exactly what functions both the undirected and directed graph classes that I make must publically implement. This is done 
*               to help ensure that the all user interaction with the graph in well planned out, consistent, and doesn't derive itself in any way 
*               from the implementation details of the graph. This should allow me to make many different representations of graphs 
*               (adjlist's, adjmatrices, etc.) that can all be used in the exact same way by the user.
*
*               Time Complexity :
*               Below is a break down of the time and space complexity for the various operations performed by this graph.
*               #TODO - List Big-O's for all of the important functions in this class.
**/

#include "uGraph.h"


////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////         PUBLIC FUNCTIONS        //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

// @func - Constructor#1
// @args - None
// @info - Initializes everything to empty
template<class VertexType>
uGraph<VertexType>::uGraph() : numEdges(0), numVertices(0), connectivityCount(0), isMultiGraph(false) {
    
}

// @func  - Constructor#2
// @args  - #1 String that contains the filename from which to load a graph
// @error - Can throw IO error if invalid filename or file structure to build graph is given
template<class VertexType>
uGraph<VertexType>::uGraph(std::string fn){

// #TODO Load the file given by 'fn' into the graph.
    
}

// @func  - Copy Constructor
// @args  - #1 uGraph object that you wish to make this a copy of
template<class VertexType>
uGraph<VertexType>::uGraph(const uGraph<VertexType> & toCopy) {

    auto ourVertices = this->getAllVertices();
    // Go through, delete, and clean up all vertices and edges.z
    for(auto i : ourVertices) {
        this->deleteVertex(i);
    }

    for(auto i : toCopy.getAllVertices()) {
        std::vector<std::pair<VertexType, double> > edges = toCopy.getAdjVertices(i);
        this->insertVertex(i);

        for(auto j : edges) {
            this->insertEdge(i, j.first, j.second);
        }
    }
}


// @func  - Destructor
// @info  - Cleans up the dynamically allocated AdjList objects contains in the list vector.
template<class VertexType>
uGraph<VertexType>::~uGraph() {
    for(int i = 0; i < list.size(); i++)
        delete(list[i]);

    list.clear();
}


// @func   - insertNode
// @args   - #1 The value of the node to be inserted
// @return - Boolean indicating succes 
template<class VertexType>
bool uGraph<VertexType>::insertVertex(VertexType data) {

    // if true then a vertex with the same data is already in our graph, so return false
    if(lookupMap.find(data) != lookupMap.end())
        return false;

    // Start by creating a new vertex
    Vertex<VertexType> newVertex;

    // Set the data of that vertex accordingly
    if(!newVertex.setData(data))
        return false;

    // allocate a new adjacency list on the heap for the new vertex
    AdjList<VertexType> * newList = new AdjList<VertexType>(newVertex);

    newList->setIsMultiGraph(this->isMultiGraph);

    // push the new AdjList onto the vector of AdjLists
    list.push_back(newList);

    // insert the new vertex into our map for easy future lookup
    lookupMap.insert(std::pair<VertexType, AdjList<VertexType> * >(data, newList));

    // increment number of vertices
    numVertices++;

    return true;
    
}

// @func   - deleteVertices
// @args   - #1 Vector of Vertex data corresponding to the vertices to be added.
// @return - Boolean indicating success, is false if any of the individual insertions fail
template<class VertexType>
bool uGraph<VertexType>::insertVertices(std::vector<VertexType> vertices) {

    bool ret = true;

    for(auto i :vertices) {
        if(!this->insertVertex(i))
            ret = false;
    }

    return ret;

}

// @func   - getAllVertices
// @args   - none
// @return - Vector of the data contained inside all vertices. 
template<class VertexType>
std::vector<VertexType> uGraph<VertexType>::getAllVertices() {
    std::vector<VertexType> ret;
    for(auto i : list)
        ret.push_back(i->getVertex()->getData());

    return ret;

}

// @func   - deleteVertices
// @args   - #1 Vector of Vertex data corresponding to the vertices to be deleted.
// @return - Boolean indicating success, is false if any of the individual deletions fail
template<class VertexType>
bool uGraph<VertexType>::deleteVertices(std::vector<VertexType> vertices) {

    bool ret = true;

    for(auto i :vertices) {
        if(!this->deleteVertex(i))
            ret = false;
    }

    return ret;
}


// @func   - deleteNode
// @args   - none
// @return - Boolean indicating success
// @info   - Because this is an undirected graph, we not only have to delete the vertex in question and any edges that
//           eminate from it, but we also have to go to the other vertices and delete any edges that end at the vertex
//           to be deleted. Thankfully, because of our use of maps and pointers this isn't difficult nor too costly. Running time
//           should be O(n) where n is the number of edges that leave the vertex to be deleted.
template<class VertexType>
bool uGraph<VertexType>::deleteVertex(VertexType data) {

    AdjList<VertexType> *  adjList = this->findVertex(data);

    // if value returned in the end of the vector, the vertex doesn't exist
    if(adjList == nullptr)
        return false;

    std::vector<Edge<VertexType> *> edges = adjList->getAllEdges();

    int numEdgesToDelete = edges.size();


    // Here we go through all of the edges eminating from the vertex to be deleted, and delete the symmetric edges that
    // point back to this vertex to be deleted. The is a nuance of our implementation, an undirected graph in this implementation
    // consists of pairs of edges between abridged vertices with equal weights.
    for(auto edge : edges) {

        // locate the adjacency list of the vertex on the other end of the edge from the vertex to be deleted
        AdjList<VertexType> * temp = findVertex(edge->getVertex()->getData());

        if(temp == nullptr) // this condition shouldn't occur but just for safety it's here
            continue;

        // delete that vertices edge with the vertex to be deleted
        temp->deleteEdge(data);

        
    }

    // finally remove the node for the current vertex from our map of vertices.
    auto get = lookupMap.find(data);

    // if true then a vertex with the given data does not exist in our map, which is a problem, and means our internal structure
    // is inconsistent, we'll just return false and turn a blind eye.
    if(get == lookupMap.end())
        return false;
    else 
        lookupMap.erase(get);

    for(typename std::vector<AdjList<VertexType> *>::iterator it = list.begin() ; it != list.end(); ++it) {

        AdjList<VertexType> * adj1 = *it;

        if(adj1->getVertex()->getData() == data) {
            AdjList<VertexType> * toDelete = adj1;
            list.erase(it);
            delete(toDelete);
            break;
        }
    }        

    // decrement the number of vertices
    numVertices--;

    // decrement the number of edges by the number of edges that were attached to the vertex we just destroyed.
    numEdges -= numEdgesToDelete;

    return true;
    
}


// @func   - insertEdge
// @args   - #1 The "From" Node, the "To" Node, the weight for this new edge 
// @return - Boolean indicating succes 
template<class VertexType>
bool uGraph<VertexType>::insertEdge(VertexType v1, VertexType v2, double weight) {

    // This assumes we don't want edges between the same vertex
    if(v1 == v2)
        return false;

   AdjList<VertexType> *  adj1 = this->findVertex(v1);
   AdjList<VertexType> *  adj2 = this->findVertex(v2);

    // if value returned in the end of the vector, the vertex doesn't exist
    if(adj1 == nullptr || adj2 == nullptr) 
        return false;
    
    // add an edge from vertex 1 to vertex 2
    if(adj1->addEdge(adj2->getVertex(), weight) && adj2->addEdge(adj1->getVertex(), weight)) {
        numEdges++;
        return true;
    }

    return false;
    
}


// @func   - deleteEdge
// @args   - #1 The "From" Node, the "To" Node. #Note These two vertices define the edge
// @return - Boolean indicating succes 
template<class VertexType>
bool uGraph<VertexType>::deleteEdge(VertexType v1, VertexType v2) {

   AdjList<VertexType> *  adj1 = this->findVertex(v1);
   AdjList<VertexType> *  adj2 = this->findVertex(v2);

    // if value returned in the end of the vector, the vertex doesn't exist
    if(adj1 == nullptr || adj2 == nullptr)
        return false;

    // delete an edge from vertex 1 to vertex 2
    if(!adj1->deleteEdge(adj2->getVertex()) || !adj2->deleteEdge(adj1->getVertex()) ) {
        return false;
    }
    
    numEdges--;
    return true;
    
}


// @func   - getNumVertices
// @args   - None
// @return - The number of vertices currently in the graph.
template<class VertexType>
int uGraph<VertexType>::getNumVertices() const {

    return this->numVertices;
}


// @func   - getNumEdges
// @args   - None
// @return - The number of edges currently in the graph.
template<class VertexType>
int uGraph<VertexType>::getNumEdges() const{

    return this->numEdges;
}


// @func   - containsVerex
// @args   - #1 data associated with the vertex that you wish to query for existence 
// @return - Bool corresponding to the existence of a vertex with the given data in this graph
template<class VertexType>
bool uGraph<VertexType>::containsVertex(VertexType v) {

    return (nullptr != findVertex(v));
}


// @func   - getEdgeWeight
// @args   - #1 data associated with vetex #1, data associated with vertex #2
// @return - returns the weight of the edge, throws error if edge not found
// @TODO   - Figure out how to implement this without exceptions, although that would
//           most likely imply putting restrictions on the weighting (e.g. wt >= 0)
template<class VertexType>
double uGraph<VertexType>::getEdgeWeight(VertexType v1, VertexType v2) {

   AdjList<VertexType> *  adj1 = this->findVertex(v1);
   AdjList<VertexType> *  adj2 = this->findVertex(v2);

    // if value returned in the end of the vector, the vertex doesn't exist
    if(adj1 == nullptr || adj2 == nullptr)
        throw std::logic_error("Can't find Vertices in Graph");

    Edge<VertexType> * temp =  adj1->getEdge(adj2->getVertex());

    if(temp == nullptr)
        throw std::logic_error("No Edge Exists Between Given Vertices");

    return temp->getWeight();
}



// @func   - getAdjVertices
// @args   - Data contained in vertex that you wish to recieve a list of adjacent vertices of.
// @return - Vector of pairs, first item is the vertex that the edge points to, second is the weight of that edge.
template<class VertexType>
std::vector< std::pair<VertexType, double> > uGraph<VertexType>::getAdjVertices(VertexType v1){

    std::vector< std::pair<VertexType, double> > retVector;

    AdjList<VertexType> *  adj1 = findVertex(v1);

    if(adj1 == nullptr)
        return retVector;

    std::vector<Edge<VertexType> *> edgeList = adj1->getAllEdges();

    for(auto edge : edgeList)  {
        retVector.push_back(std::pair<VertexType, double>(edge->getVertex()->getData(), edge->getWeight()));
    }

    return retVector;
}


// @func   - printGraph
// @args   - none
// @return - none
// @info   - prints the adjecency list representation of the graph.
template<class VertexType> void uGraph<VertexType>::printGraph() {
    
    for(auto vertex : list) {
        std::cout << "Vertex : " << vertex->getVertex()->getData() << " -> ";

        std::vector<Edge<VertexType> *> edges = vertex->getAllEdges(); 

        for(auto edge : edges) {
            std::cout << edge->getVertex()->getData() << ", ";
        }

        std::cout << "\n";
    }
    std::cout << "\n\n\n";
}


// @func   - isConnected
// @args   - None
// @return - Bool indicating whether or not the graph is connected
// @info   - This function searches through the given graph to see if any given vertex can be reached from any other given vertex
template<class VertexType>
bool uGraph<VertexType>::isConnected() {

    this->connectivityCount = 0;

    auto f = [](VertexType&) -> void { int x = 0; }; // dummy function that needs to be passed in to BFS

    this->breadthFirst(list[0]->getVertex()->getData(), f);

    return connectivityCount == list.size();
}


// @func   - setIsMultiGraph
// @args   - boolean to be stored in isMultiGraph
// @return - Bool indicating success
template<class VertexType>
bool uGraph<VertexType>::setIsMultiGraph(bool val) {

    this->isMultiGraph = val;

    for(auto i : list) {
        i->setisMultiGraph(val);
    }

    return true;
}

// @func   - getIsMultiGraph
// @args   - None
// @return - Bool value of isMultiGraph
template<class VertexType>
bool uGraph<VertexType>::getIsMultiGraph() {
    return isMultiGraph;
}


// @func   - depthFirst
// @args   - #1 Data associated with the starting vertex for the search, #2 function pointer that takes a set of vertex data as an argument
// @return - Bool indicating if the function could find the starting vertex based on arg#1
// @info   - Performs a depth first traversal, calling the visit() function on each item. This function assumes that all vertex data 
//           is unique, so if this is a graph of strings, no two strings should be the same. This precondition allows us to use a 
//           std::unordered_map to keep track of the seen and unseen vertices.
template<class VertexType>
bool uGraph<VertexType>::depthFirst(VertexType rootData, void visit(VertexType&)) {

    // Our deque object, stores the vertices as they appear to the search
    // We actually use it as a stack for this problem, by inserting and removing from the 
    // back of the queue 
    std::deque<Vertex<VertexType> *> q;

    // A map that allows us to 'mark' the vertices when they've been seen.
    // maps a set of unique vertex data to a bool that is true if that data has been seen before
    typename std::unordered_map<VertexType, bool> marked;

    AdjList<VertexType> *  rootVert = findVertex(rootData);

    if(rootVert == nullptr)
        return false;

    marked.insert(std::pair<VertexType, bool>(rootData, true));
    q.push_back(rootVert->getVertex());

    while(q.size()) {

        Vertex<VertexType> * tempVert = q.back();q.pop_back();
        AdjList<VertexType> *  adj = findVertex(tempVert->getData());

        if(adj == nullptr) 
            return false;

        connectivityCount++;

        // visit the node that we just popped off the stack
        VertexType tempData = adj->getVertex()->getData();
        if(visit != nullptr)
            visit(tempData);

        std::vector<Edge<VertexType> *> edges = adj->getAllEdges();

        for(int i = 0; i < edges.size(); i++) {

            Vertex<VertexType> * tempVert = edges[i]->getVertex();
            VertexType tempData = tempVert->getData();
            typename std::unordered_map<VertexType, bool>::const_iterator get = marked.find(tempData);

            if(get == marked.end()) {
                marked.insert(std::pair<VertexType, bool>(tempVert->getData(), true));
                q.push_back(tempVert);
            }
        }

    }

    return true;
    
}


// @func   - breadthFirst
// @args   - #1 Data associated with the starting vertex for the search, #2 function pointer that takes a set of vertex data as an argument
// @return - Bool indicating if the function could find the starting vertex based on arg#1
// @info   - Performs a breadth first traversal, calling the visit() function on each item. This function assumes that all vertex data
//           is unique, so if this is a graph of strings, no two strings should be the same. This precondition allows us to use an
//           std::unordered_map to keeptrack of the seen and unseen vertices.
template<class VertexType>
bool uGraph<VertexType>::breadthFirst(VertexType rootData, void visit(VertexType&)) {

    // Our queue object, stores the vertices as they appear to the search
    std::deque<Vertex<VertexType> *> q;

    // A map that allows us to 'mark' the vertices when they've been seen.
    // maps a set of unique vertex data to a bool that is true if that data has been seen before
    typename std::unordered_map<VertexType, bool> marked;

    AdjList<VertexType> *  rootVert = findVertex(rootData);

    if(rootVert == nullptr)
        return false;


    marked.insert(std::pair<VertexType, bool>(rootData, true));
    q.push_back(rootVert->getVertex());

    while(q.size()) {

        Vertex<VertexType> * tempVert = q.front();q.pop_front();
        AdjList<VertexType> *  adj = findVertex(tempVert->getData());

        connectivityCount++; // used internally

        if(adj == nullptr)
            return false;

        VertexType tempData = adj->getVertex()->getData();
        if(visit != nullptr)
            visit(tempData);

        std::vector<Edge<VertexType> *> edges = adj->getAllEdges();

        // Go through all of the edges associated with the current vertex
        for(int i = 0; i < edges.size(); i++) {

            Vertex<VertexType> * tempVert = edges[i]->getVertex();
            VertexType tempData = tempVert->getData();

            typename std::unordered_map<VertexType, bool>::const_iterator get = marked.find(tempData);

            // if the current vertex hasn't been seen
            if(get == marked.end()) {
                // mark the vertex
                marked.insert(std::pair<VertexType, bool>(tempVert->getData(), true));
                // enqueue the new vertex
                q.push_back(tempVert);
            }

        }

    }

    return true;
}

// @func   - minimumCut
// @args   - none
// @return - 2 column vector of vertices, each column representing one half of the cut. 
// @info   - Partitions the current graph into two subsets that have at the minmum number of edges between them.
// @TODO   - Currently in beta-stage, needs to be tested and debugged. Is semi-working through.
template<class VertexType>
std::vector<std::vector<VertexType> > uGraph<VertexType>::minimumCut() {

    srand(time(0));
    int lowest = std::numeric_limits<int>::max();
    std::vector<std::vector<VertexType> > ret;
    std::vector< AdjList<VertexType> * > finalList;

    // the following are used to choose an edge to contract randomly
    std::random_device rd;
    std::mt19937 gen(rd());
    

    for(int i = 0; i < 3; i++) {

        std::unordered_map<VertexType, std::vector<VertexType> > collapsed;

        std::vector< AdjList<VertexType> * > newList = list;

        for(auto i : list) {

            collapsed.insert(std::pair<VertexType, std::vector<VertexType> >(i->getVertex()->getData(), std::vector<VertexType>()));
            AdjList<VertexType> * newAdj = new AdjList<VertexType>();
            newAdj->setVertex(i->getVertex()->getData());
            newAdj->setIsMultiGraph(true);

            newList.push_back(newAdj);

            std::vector<Edge<VertexType> *> edges = i->getAllEdges();

            for(auto j : edges) {
                newList.back()->addEdge(j->getVertex(), j->getWeight()); 
            }
        }

        // While we haven't reduced the graph to 2 vertices
        while(newList.size() > 2) {

            std::uniform_int_distribution<> dist_Vert(0, newList.size()-1);
            int randVertex = dist_Vert(gen);

            auto adj1 = newList[randVertex];

            std::vector<Edge<VertexType> *> edges = adj1->getAllEdges();

            if(!edges.size()) 
                continue;

            std::uniform_int_distribution<> dist_Edges(0, edges.size()-1);
            int randEdge = dist_Edges(gen);

            AdjList<VertexType> * adj2 = nullptr;
            

            typename std::vector<AdjList<VertexType> *>::iterator vertToDelete;
            for(typename std::vector<AdjList<VertexType> *>::iterator it = newList.begin() ; it != newList.end(); ++it) {

                AdjList<VertexType> * tempAdj = *it;

                if(tempAdj->getVertex()->getData() ==  edges[randEdge]->getVertex()->getData()) {
                    adj2 = tempAdj;
                    vertToDelete = it;
                    break;
                }
            }   

            if(adj2 == nullptr) {
                adj1->deleteEdge(edges[randEdge]->getVertex());
                continue;
            }
            // 
            // std::cout << "mid";
            // std::cout << adj1->getVertex()->getData() << " :: " << adj2->getVertex()->getData() << "\n";

            std::vector<Edge<VertexType> *> edges2 = adj2->getAllEdges();

            // std::cout << "mid2";
            for(auto i : edges2) {
                AdjList<VertexType> * tempAdj;
                for(auto j : newList) {
                    if(j->getVertex()->getData() == i->getVertex()->getData()) {
                        tempAdj = j;
                        break;
                    }
                }
                adj1->addEdge(tempAdj->getVertex(), i->getWeight());
            }

            // std::cout << "mid3";

            if(collapsed.find(adj1->getVertex()->getData()) != collapsed.end()) {
                // std::cout << "t1";
                collapsed.at(adj1->getVertex()->getData()).push_back(adj2->getVertex()->getData());
                // std::cout << "t2";
                auto delVert = collapsed.find(adj2->getVertex()->getData());
                // std::cout << "t3";
                if(delVert != collapsed.end()) {
                    collapsed.erase(delVert);
                    // std::cout << "t4";
                }
            } 

            newList.erase(vertToDelete);
            // std::cout << "end\n";
        }

        if(lowest > newList[0]->getAllEdges().size()) {
            lowest = newList[0]->getAllEdges().size();
            finalList = newList;
        }
    }
    uGraph<VertexType> * retGraph = new uGraph<VertexType>();

    // retGraph->printGraph();

    std::cout << "Vertex 1 " << finalList[0]->getVertex()->getData() << "\n\n\n";
    std::cout << "Vertex 2 " << finalList[1]->getVertex()->getData() << "\n";
    std::cout << "Edges " <<finalList[0]->getAllEdges().size() << "\n";

    delete(retGraph);

    return ret;
}


// @func   - minimumSpanningTree
// @args   - none
// @return - A graph that represents the minimum spanning tree of the current graph object. 
// @info   - This function will return another uGraph object that has the edges reduces to those that exist in the minimum 
//           spanning tree of the veritces in this graph. Will throw an exception is the graph is not connected. Prims alg. 
//           is used to find the min. spanning tree, and the source vertex is the first vertex that was stored into the graph.
template<class VertexType>
uGraph<VertexType> * uGraph<VertexType>::minimumSpanningTree() {

    // A non connected graph cannot be spanned, without this we risk an infinite loop
    if(!this->isConnected())
        throw std::logic_error("Graph is not Connected\n");

    uGraph<VertexType> * newGraph = new uGraph();

    std::unordered_map<VertexType, std::pair<VertexType, double> > set; // maps a vertex to a weight and the vertex that connects to it
    std::unordered_map<VertexType, bool> mst_set;
    double imax = std::numeric_limits<double>::infinity();

    for(int i = 0; i < list.size(); i++) {
        VertexType tempData = list[i]->getVertex()->getData();
        set.insert(std::pair<VertexType, std::pair<VertexType, double> >(tempData, std::pair<VertexType, double>(tempData, imax)));
        newGraph->insertVertex(tempData);
    }

    set.at(list[0]->getVertex()->getData()).second = 0;

    while(mst_set.size() != list.size()) {
        double temp = imax; // lowest weight found
        int index = 0;   // index of the vertex with the lowest wieght found

        // VERY inneficient! Here we scan linearly through all vertices to find the smallest, we need a priority queue!
        for(int i = 0; i < list.size(); i++) {

            if(mst_set.find(list[i]->getVertex()->getData()) == mst_set.end()) {

                if(set.at(list[i]->getVertex()->getData()).second <= temp) {
                    temp = set.at(list[i]->getVertex()->getData()).second;
                    index = i;
                }
            }
        }



        // Take the vertex with the smallest weight and mark it as connected to our min tree
        mst_set.insert(std::pair<VertexType, bool>(list[index]->getVertex()->getData(), true));

        // add the lowest-weighted edge between the two appropriate vertices in our min tree
        newGraph->insertEdge(set.at(list[index]->getVertex()->getData()).first, list[index]->getVertex()->getData(), temp);                                                 

        // Get all of that vertices neighbors
        std::vector<Edge<VertexType> *> edges = list[index]->getAllEdges();

        // Update the weighting of the vertices that are neighbors of the last vertex
        for(auto edge : edges) {
            if(edge->getWeight() < set.at(edge->getVertex()->getData()).second) 
                set.at(edge->getVertex()->getData()) = std::pair<VertexType, double>(list[index]->getVertex()->getData(), edge->getWeight());
            
        }

    }

    return newGraph;
}


// @func   - dijkstras
// @args   - #1 Data contained in starting vertex for search
// @return - A pair containing two maps. The first map takes a vertex and returns the previuos vertex in the path there from the source vertex. 
//           The second map takes a vertex and gives the total weight that it takes to get there from the source vertex.
// @info   - Performs Dijkstra's path-finding algorithm to get from a starting vertex to any goal vertex in the map, throws an exception if
//           the source vertex is not contained in the map.
template<class VertexType>
typename uGraph<VertexType>::dist_prev_pair uGraph<VertexType>::dijkstras(VertexType source) {

    if(this->findVertex(source) == nullptr)
        throw std::logic_error("Source Vertex Not in Graph\n");

    // This function takes two pairs<weight, Vertex> and does the comparison only on the weight, not the vertex data. This is passed
    // into our std::set object to allow it to order the nodes according the lowest weight, which gives us a priority queue.
    auto f = [](const std::pair<double, VertexType> & a, const std::pair<double, VertexType> & b) -> bool { return  a.first < b.first; };

    // This is probably the ugliest thing I've ever written, but it's just a set that contains a vertex and the weight associated with it. 
    // we also have to pass in a pointer to a function that can compare two of these pairs based on the weight and not the Vertex Data.
    std::set<std::pair<double, VertexType>, bool (*)(const std::pair<double, VertexType> & a, const std::pair<double, VertexType> & b) > queue (f);

    double max_weight = std::numeric_limits<double>::infinity();

    typename uGraph<VertexType>::dist_prev_pair ret; // a pair of maps, this returns both the path between the nodes and the net weight along each path
                                                     // to the user-accessible interface function 
    std::unordered_map<VertexType, double> dist;     // Maps a vertex to it's distance from the source vertex
    std::unordered_map<VertexType, VertexType> prev; // Maps a given vertex to the previous vertex that we took to get there
    std::unordered_map<VertexType, bool> scanned;    // Maps a given vertex to a bool, letting us know if we have examine all of it's neighbors.

    dist.reserve(this->getNumVertices());
    prev.reserve(this->getNumVertices());


    for(auto vertex : list) { // Initialize the distances to infinity for all vertices
        if(vertex->getVertex()->getData() != source)
            dist.insert(std::pair<VertexType, double>(vertex->getVertex()->getData(), max_weight));
        else
            dist.insert(std::pair<VertexType, double>(vertex->getVertex()->getData(), 0));
        queue.insert(std::pair<double, VertexType>(dist.at(vertex->getVertex()->getData()), vertex->getVertex()->getData()));
    }

    while(!queue.empty()) {

        // grab from the front of the queue
        double current_dist = queue.begin()->first;
        AdjList<VertexType> * current_vert = this->findVertex(queue.begin()->second);
        queue.erase(queue.begin());
        scanned.insert(std::pair<VertexType,bool>(current_vert->getVertex()->getData(), true));

        auto edges = current_vert->getAllEdges();

        for(auto edge : edges) {

            AdjList<VertexType> * temp_vert = this->findVertex(edge->getVertex()->getData());
            VertexType temp_data = temp_vert->getVertex()->getData();

            double temp_weight = edge->getWeight() + current_dist;

            if(scanned.find(temp_data) == scanned.end() && temp_weight <= dist.at(temp_data)) {
                queue.erase(std::make_pair(dist.at(temp_data), temp_data));
                dist.at(temp_data) = temp_weight;
                if(prev.find(temp_data) == prev.end())
                    prev.insert(std::pair<VertexType, VertexType>(temp_data, current_vert->getVertex()->getData()));
                else
                    prev.at(temp_data) = current_vert->getVertex()->getData();
                queue.insert(std::make_pair(dist.at(temp_data), temp_data));
            }

        }
    }

    ret.first = prev;
    ret.second = dist;

     return ret;
}

// @func   - dijkstrasComputePath
// @args   - #1 Source Vertex, #2 Dest Vertex
// @return - A pair consisting of #1Vector of vertices that lead from the source vertex to the destination vertex along the shortest path, 
//           #2 the net weight along that path betweent he two vertices.
// @info   - This function exists to allow the user to retrieve a vector containing the edges to travel along to complete the shortest path
//           between two given vertices, Dijkstras algorithm returns the shortest path to *every* other vertex and the output must be decoded 
//           to find the path between the source and any other specific vertex.
template<class VertexType>
std::pair<std::vector<VertexType>, double> uGraph<VertexType>::dijkstrasComputePath(VertexType src, VertexType dest) {

    std::unordered_map<VertexType, VertexType> prev;
    std::unordered_map<VertexType, double> dist;
    std::vector<VertexType> path;
    std::pair<std::vector<VertexType>, double> ret;

    if(this->findVertex(src) == nullptr || this->findVertex(dest) == nullptr)
        throw std::logic_error("SRC or DEST Vertices Do Not Exist in Graph\n");

    if(src == dest) {
        path.push_back(dest);
        ret.first = path;
        ret.second = 0.0;
        return ret;
    }

    typename uGraph<VertexType>::dist_prev_pair the_pair = this->dijkstras(src);
    prev = the_pair.first;
    dist = the_pair.second;


    VertexType prev_vert = dest;
    path.push_back(dest);
    int count = 0;
    while(prev_vert != src && count < list.size()) {

        if(prev.find(prev_vert) == prev.end()) {
            return std::pair<std::vector<VertexType>, double>();
        }
        prev_vert = prev.at(prev_vert);
        path.push_back(prev_vert); 
        count++;
    }

    std::vector<VertexType> temp; temp.reserve(list.size());

    while(path.size()) {
        temp.push_back(path.back());
        path.pop_back();
    }

    ret.first = temp;
    ret.second = dist.at(dest);

    return ret;
}

// @func   - aStar
// @args   - #1 Data contained in starting vertex for search,  #2 Pointer to a hueristic function on a given node
// @return - Vector containing, in-order, the vertices to take to reach your goal. Empty if you are there or no path exists.
// @info   - Performs the A* path-finding algorithm to get from a starting vertex to any goal vertex in a list of vertices. 
template<class VertexType>
std::vector<VertexType> uGraph<VertexType>::aStar(VertexType, std::vector<VertexType>, double hueristic(VertexType&, VertexType&)) {

     // #TODO - Implement A* Path-finding algorithm

}


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////         PRIVATE FUNCTIONS        //////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// @func   - findVertex
// @args   - #1 Value contained in the vertex to be found
// @return - Pointer to the AdjList containing the vertex in queston. nullptr if not found (possibly should throw exception?)
// @info   - Goes through our vector of vertices and find which one (if any) contain the data given by the argument
template<class VertexType>
AdjList<VertexType> * uGraph<VertexType>::findVertex(VertexType data) {

    auto get = lookupMap.find(data);

    // if true then a vertex with the given data does not exist in our map, so return nullptr.
    if(get == lookupMap.end()) 
        return nullptr;
    
    return get->second;
 }







