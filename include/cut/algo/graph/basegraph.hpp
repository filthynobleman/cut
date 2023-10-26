/**
 * @file        basegraph.hpp
 * 
 * @brief       An abstract class representing a graph.
 * 
 * @details     This file contains the declaration of the abstract class
 *              cut::BaseGraph, which provides a basic interface for handling
 *              graphs.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-10-26
 */
#pragma once

#include <utility>


namespace cut
{


/**
 * @brief       A data structure representing an ordered graph edge.
 * 
 * @details     The cut::GraphEdge data structure represents an ordered edge inside
 *              a directed graph.\n 
 *              The structure provides basic compatibility with the C++ STL.
 */
struct GraphEdge
{
    /**
     * @brief       The source node.
     * 
     * @details     The source node. Starting end point of the edge.
     */
    size_t Src;

    /**
     * @brief       The destination node.
     * 
     * @details     The destination node. Final end point of the edge.
     */
    size_t Dst;

    /**
     * @brief       Creates a new cut::GraphEdge.
     * 
     * @details     This constructor initializes a new cut::GraphEdge with the
     *              given end points.
     * 
     * @param Src The source node.
     * @param Dst The destination node.
     */
    GraphEdge(int Src, int Dst);

    /**
     * @brief       Creates a new cut::GraphEdge.
     * 
     * @details     This constructor initializes a new cut::GraphEdge with the
     *              given end points, represented as a std::pair.\n 
     *              The member <code>first</code> represents the source node,
     *              while the member <code>second</code> represents the destintaion node.
     * 
     * @param Edge The end points.
     */
    GraphEdge(const std::pair<int, int>& Edge);

    /**
     * @brief       Copy constructor.
     * 
     * @details     This constructor initializes a new graph edge as a copy of
     *              the given edge.
     * 
     * @param Edge The edge to copy.
     */
    GraphEdge(const cut::GraphEdge& Edge);

    /**
     * @brief       Assignment operator.
     * 
     * @details     This operator modifies this cut::GraphEdge to make it
     *              equal to the given edge.
     * 
     * @param Edge The edge to copy.
     * @return cut::GraphEdge& This edge after the assignment.
     */
    cut::GraphEdge& operator=(const cut::GraphEdge& Edge);


};

    

class BaseGraph
{
public:
    BaseGraph() = default;
    ~BaseGraph() = default;

    virtual size_t NumNodes() = 0;
    virtual size_t NumEdges() = 0;
};


} // namespace cut
