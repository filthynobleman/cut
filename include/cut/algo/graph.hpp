/**
 * @file        graph.hpp
 * 
 * @brief       A class representing a weighted graph.
 * 
 * @details     This file provides the declaration of a class that represents
 *              a weighted (directed or undirected) graph.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-11-15
 */
#pragma once

#include <cut/algo/adjlist.hpp>
#include <unordered_map>


namespace cut
{

/**
 * @brief       Hash structure for integers pairs used by cut::Graph.
 * 
 * @details     Hash structure for integers pairs used by cut::Graph.
 */
struct GraphPairHash
{
    std::size_t operator()(const std::pair<int, int>& P) const noexcept;
};


/**
 * @brief       A data structure representing the edge of a graph.
 * 
 * @details     This data structure represents the edge of a cut::Graph.\n 
 *              Independently if the graph is directed or not, a cut::GraphEdge
 *              always represents a directed edge.
 */
struct GraphEdge
{
    /**
     * @brief       The source node.
     * 
     * @details     The source node.
     */
    int Src;

    /**
     * @brief       The destination node.
     * 
     * @details     The destination node.
     */
    int Dst;

    /**
     * @brief       The edge weight.
     * 
     * @details     The edge weight.
     */
    double Weight;

    /**
     * @brief       Construct a new graph edge.
     * 
     * @details     This constructor initializes a new cut::GraphEdge with
     *              the given source node, destination node and weight.\n 
     *              By default, the weight is <code>1.0</code>, which can
     *              be useful for implementing unweighted graphs.
     * 
     * @param Src The source node.
     * @param Dst The destination node.
     * @param Weight The edge weight.
     */
    GraphEdge(int Src, int Dst, double Weight = 1.0);

    /**
     * @brief       Copy constructor.
     * 
     * @details     This constructor initializes a new cut::GraphEdge as a
     *              copy of the given one.
     * 
     * @param GE The graph edge to copy.
     */
    GraphEdge(const cut::GraphEdge& GE);

    /**
     * @brief       Assignment-copy operator.
     * 
     * @details     This constructor updates this cut::GraphEdge to make it
     *              a copy of the given one.
     * 
     * @param GE The graph edge to copy.
     * @return cut::GraphEdge& This edge after the assignment.
     */
    cut::GraphEdge& operator=(const cut::GraphEdge& GE);
};



/**
 * @brief       A class representing a weighted graph.
 * 
 * @details     The class cut::Graph provides a general interface for handling
 *              graph structures.\n 
 *              While the backend implementation can handle weighted directed graphs,
 *              the class provides an easy interface to make the graph 
 *              unweighted/undirected, according to the user's needs.\n 
 *              While the graph can be updated and modified, the class also
 *              allows for finalizing it, making it a read-only graph to
 *              enhance efficiency.
 */
class Graph
{
private:
    /**
     * @brief       The backend adjacency list.
     * 
     * @details     The backend adjacency list that realizes the connectivity.
     */
    cut::BaseAdjacencyList& m_AL;

    /**
     * @brief       The weight map.
     * 
     * @details     The map that stores the weights of all the edges.
     */
    std::unordered_map<std::pair<int, int>, double, GraphPairHash> m_Weights;

    /**
     * @brief       Whether or not the graph is directed.
     * 
     * @details     Whether or not the graph is directed.
     */
    bool m_Directed;

    /**
     * @brief       Whether or not the graph is weighted.
     * 
     * @details     Whether or not the graph is weighted.
     */
    bool m_Weighted;


public:
    Graph(/* args */);
    ~Graph();
};



} // namespace cut
