GraphAdjList
===============

#### Overview

This directory contains all types of graph objects derived from the `GraphInterface` class and use an adjacency list to internally represent the graph data structure (as apposed to an adjacency matrix, etc).

An adjacency list consists of a vertex and a list  of edges that eminate from this vertex to the other vertices in the map, along with the weight associated with those edges.  Thus if some vertex v had edges connected it with vertices a, b, c, d, and e, the adj list for vertex v would look like :
 * `v -> a* -> b* -> c* -> d* -> e* -> null`

Where x* is an edge that leads from vertex v to vertex x. Thus to find all of the edges that eminate from a given vertex v, you just need to traverse the list of edges on the AdjList that contains vertex v. This above is just one adjacency list, our graph will have a single adjacency list for each vertex in the graph. So our graph data structure will look more like this :

 1. `   a  -> c* -> d* -> null        `
 2. `   b  -> v* -> d* -> e* -> null  `
 3. `   c  -> a* -> v* -> e* -> null  `
 4. `   d  -> a* -> b* -> null        `
 5. `   e  -> b* -> c* -> v* -> null  `
 6. `   v  -> b* -> c* -> null        `

As of now, there are two types of graphs that use an adjacency list implementation. They are uGraph (undirected graph) and dGraph(DirectedGraph). Both rely on the same AdjList, Vertex, and Edge classes to accomplish their implementations.

#### uGraph
An undirected graph, this means that inserting an edge between any two vertices will actually insert two edges into our adjacency list representation with the same weight. 
TODO

#### dGraph 
A typical directed graph.
TODO


