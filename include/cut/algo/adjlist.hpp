/**
 * @file        adjlist.hpp
 * 
 * @brief       Classes implementing adjacency lists.
 * 
 * @details     This file contains the declaration of different classes
 *              that provide an interface for adjacency lists.\n 
 *              The file contains an abstract class cut::BaseAdjacencyList, which
 *              provides the common interface to access an adjacency list,
 *              and two classes cut::AdjacencyList and cut::CompatAdjacencyList,
 *              respectively implementing an adjacency list with a flexible
 *              implementation and an adjacency list for efficient reading and
 *              slow writing.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-11-15
 */
#pragma once

#include <vector>


namespace cut
{
    
/**
 * @brief       Abstract base class for adjacency lists.
 * 
 * @details     This class provides an abstract interface that defines the
 *              common methods for the adjacency lists.\n 
 *              This adjacency list defines a map from the integer range [0, n]
 *              to the subsets of the integers. Differently from the most
 *              common implementations of adjacency lists, that are though for
 *              handling graph structures, this is a more general representation
 *              that allows for connecting different sets of values.
 */
class BaseAdjacencyList
{
public:
    /**
     * @brief       Base constructor.
     * 
     * @details     This constructor initializes an empty adjacency list.
     */
    BaseAdjacencyList();

    /**
     * @brief       Copy constructor.
     * 
     * @details     This constructor initializes an adjacency list as a
     *              copy of the given one.
     * 
     * @param AL The list to copy.
     */
    BaseAdjacencyList(const cut::BaseAdjacencyList& AL);

    /**
     * @brief       Assignment-copy operator.
     * 
     * @details     This operator updates this adjacency list to make
     *              it equal to the given one.
     * 
     * @param AL The list to copy.
     * @return cut::BaseAdjacencyList& This list after the assignment.
     */
    virtual cut::BaseAdjacencyList& operator=(const cut::BaseAdjacencyList& AL) = 0;

    /**
     * @brief       Destroy the BaseAdjacencyList object.
     * 
     * @details     Default destructor.
     */
    virtual ~BaseAdjacencyList();



    /**
     * @brief       Number of nodes of the list.
     * 
     * @details     This method returns the number of nodes composing
     *              this adjacency list.
     * 
     * @return int The number of nodes in the list.
     */
    virtual int NumNodes() const = 0;

    /**
     * @brief       Number of connections in the list.
     * 
     * @details     This method returns the total number of connections that
     *              compose this adjacency list.
     * 
     * @return int The number of connections in the list.
     */
    virtual int NumConnections() const  = 0;

    /**
     * @brief       Number of adjacents of node i.
     * 
     * @details     This method returns the number of connections going
     *              out from node i.
     * 
     * @throws cut::OutOfBoundError if <code>i >= NumNodes()</code>.
     * 
     * @param i The index of a node.
     * @return int The number of connections in the node.
     */
    virtual int NumAdjacents(int i) const = 0;


    /**
     * @brief       Return an adjacent to node i.
     * 
     * @details     This method returns the adjacent in position
     *              <code>idx</code> in the list of adjacents of node
     *              <code>i</code>.
     * 
     * @throws cut::OutOfBoundError if <code>idx >= NumAdjacents(i)</code>.
     *              
     * @param i The index of a node.
     * @param idx The index of an adjancent.
     * @return int The adjacent of the given node in the given position.
     */
    virtual int GetAdjacent(int i, int idx) const  = 0;

    /**
     * @brief       Syntactic sugar for <code>GetAdjacent()</code>.
     * 
     * @details     Syntactic sugar for <code>GetAdjacent()</code>.
     * 
     * @throws cut::OutOfBoundError if <code>idx >= NumAdjacents(i)</code>.
     *              
     * @param i The index of a node.
     * @param idx The index of an adjancent.
     * @return int The adjacent of the given node in the given position.
     */
    virtual int operator()(int i, int idx) const;
};



/**
 * @brief       A flexible implementation of the cut::BaseAdjacencyList interface.
 * 
 * @details     The class cut::AdjacencyList provides a flexible implementation
 *              of the abstract interface cut::BaseAdjacencyList.\n 
 *              This class provides operations for modifying and updating the list,
 *              but it is not the most efficient for read-only accesses.
 */
class AdjacencyList : public cut::BaseAdjacencyList
{
protected:
    /**
     * @brief       The list of lists implementing the adjacency list.
     * @details     The list of lists implementing the adjacency list.
     */
    std::vector<std::vector<int>> m_Adj;

    /**
     * @brief       The total number of connections.
     * @details     The total number of connections.
     */
    int m_NConnections;

public:
    /**
     * @brief       Construct a new AdjacencyList with N nodes.
     * 
     * @details     This constructor initializes an adjacency list with 
     *              N nodes.\n 
     *              The list has no connections.
     * 
     * @param N The number of nodes.
     */
    AdjacencyList(int N);

    /**
     * @brief       Construct a new AdjacencyList from a list of connections.
     * 
     * @details     This constructor initializes an adjacency list from the
     *              given list of connections.\n 
     *              For each connection in the list, the first value identifies
     *              the node, while the second value identifies the adjacent.
     * 
     * @param Connections A list of connections.
     */
    AdjacencyList(const std::vector<std::pair<int, int>>& Connections);

    /**
     * @brief       Copy constructor.
     * 
     * @details     This constructor initializes an adjacency list as a
     *              copy of the given one.
     * 
     * @param AL The list to copy.
     */
    AdjacencyList(const cut::BaseAdjacencyList& AL);

    /**
     * @brief       Move constructor.
     * 
     * @details     This constructor initializes an adjacency list by moving
     *              the memory from the given adjacency list.\n 
     *              This constructor invalidates the input.
     * 
     * @param AL The adjacency list to move.
     */
    AdjacencyList(cut::AdjacencyList&& AL);

    virtual cut::BaseAdjacencyList& operator=(const cut::BaseAdjacencyList& AL) override;

    /**
     * @brief       Assignment-move operator.
     * 
     * @details     This operator updates this adjacency list by moving
     *              the memory from the given adjacency list.\n 
     *              This operator invalidates the input.
     * 
     * @param AL The adjacency list to move.
     */
    virtual cut::AdjacencyList& operator=(cut::AdjacencyList&& AL);
    virtual ~AdjacencyList();

    virtual int NumNodes() const override;
    virtual int NumConnections() const override;
    virtual int NumAdjacents(int i) const override;
    virtual int GetAdjacent(int i, int idx) const override;

    /**
     * @brief       Add a new node to the list.
     * 
     * @details     This method adds a new node to the list, and assigns to
     *              it the index <code>NumNodes()</code>.
     */
    virtual void AddNode();

    /**
     * @brief       Insert a new node in the given position.
     * 
     * @details     This method adds a new node to the list, and assigns it
     *              the index <code>i</code>.\n 
     *              All the nodes that previously had index <code>j >= i</code>
     *              are incremented by one, but their list are left unchanged.
     * 
     * @throws cut::OutOfBoundError if <code>i >= NumNodes()</code>.
     * 
     * @param i The index where to insert the new node.
     */
    virtual void InsertNode(int i);

    /**
     * @brief       Swaps the connection lists of the given nodes.
     * 
     * @details     This method swaps the connection list of node <code>i</code>
     *              with the connection list of node <code>j</code>.\n 
     *              If <code>i == j</code> the method does nothing.
     * 
     * @throws cut::OutOfBoundError if <code>i >= NumNodes()</code>.
     * @throws cut::OutOfBoundError if <code>j >= NumNodes()</code>.
     * 
     * @param i The index of a node.
     * @param j The index of a node.
     */
    virtual void SwapNodes(int i, int j);

    /**
     * @brief       Removes the given node.
     * 
     * @details     This method removes the node with index <code>i</code> from
     *              the list, deleting also all its connections.\n 
     *              All the nodes that previously had index <code>j >= i</code>
     *              are decremented by one, but their list are left unchanged.
     * 
     * @throws cut::OutOfBoundError if <code>i >= NumNodes()</code>.
     *              
     * @param i The node to remove.
     */
    virtual void RemoveNode(int i);

    /**
     * @brief       Add the given adjancent to the given node.
     * 
     * @details     This method adds the value <code>j</code> as an adjacent
     *              of the node <code>i</code>.
     * 
     * @throws cut::OutOfBoundError if <code>i >= NumNodes()</code>.
     * @throws cut::AssertionError if <code>j</code> is already an adjacent of <code>i</code>.
     * 
     * @param i The index of a node.
     * @param j The new adjacent.
     */
    virtual void AddAdjacent(int i, int j);

    /**
     * @brief       Add the given adjancent to the given node.
     * 
     * @details     This method adds the value <code>j</code> as an adjacent
     *              of the node <code>i</code>, assigning it the index
     *              <code>idx</code> in the list of <code>i</code>'s
     *              connections, and shifting forward all the following
     *              connections.
     * 
     * @throws cut::OutOfBoundError if <code>i >= NumNodes()</code>.
     * @throws cut::AssertionError if <code>j</code> is already an adjacent of <code>i</code>.
     * @throws cut::OutOfBoundError if <code>idx >= NumAdjacents(i)</code>.
     * 
     * @param i The index of a node.
     * @param j The new adjacent.
     * @param idx The index of the connection.
     */
    virtual void InsertAdjacent(int i, int j, int idx);

    /**
     * @brief       Updates the adjancent to the given value.
     * 
     * @details     This method updates the connection with index <code>idx</code>
     *              from node <code>i</code> to point to the value <code>j</code>.
     * 
     * @throws cut::OutOfBoundError if <code>i >= NumNodes()</code>.
     * @throws cut::AssertionError if <code>j</code> is already an adjacent of <code>i</code>.
     * @throws cut::OutOfBoundError if <code>idx >= NumAdjacents(i)</code>.
     * 
     * @param i The index of a node.
     * @param j The new value of the adjacent.
     * @param idx The index of the connection.
     */
    virtual void UpdateAdjacent(int i, int j, int idx);

    /**
     * @brief       Replace the given adjacent with a new one.
     * 
     * @details     This method replaces the adjacent value <code>j</code> in
     *              the connection list of node <code>i</code> with the value
     *              <code>k</code>.
     * 
     * @throws cut::OutOfBoundError if <code>i >= NumNodes()</code>.
     * @throws cut::AssertionError if <code>j</code> is not an adjacent of <code>i</code>.
     * @throws cut::AssertionError if <code>k</code> is already an adjacent of <code>i</code>.
     * 
     * @param i The index of a node.
     * @param j The value of the adjacent to replace.
     * @param k The new value of the replaced adjacent.
     */
    virtual void ReplaceAdjacent(int i, int j, int k);

    /**
     * @brief       Removes the given adjacent to the given node.
     * 
     * @details     This method removes the adjacent in position <code>idx</code>
     *              from the connection list of node <code>i</code>.
     * 
     * @throws cut::OutOfBoundError if <code>i >= NumNodes()</code>.
     * @throws cut::OutOfBoundError if <code>idx >= NumAdjacents(i)</code>.
     * 
     * @param i The index of a node.
     * @param idx The index of a connection.
     */
    virtual void RemoveAdjacent(int i, int idx);
};



/**
 * @brief       An efficient read-only adjacency list.
 * 
 * @details     This class provides an efficient read-only implementation of
 *              an adjacency list.\n 
 *              The memory is compactly stored, enhancing memory locality
 *              and fast accesses.
 */
class CompatAdjacencyList : public cut::BaseAdjacencyList
{
protected:
    /**
     * @brief       The list of connections.
     * @details     The list of connections.
     */
    std::vector<int> m_Adj;

    /**
     * @brief       The starting index of each node.
     * @details     The starting index of each node.
     */
    std::vector<int> m_Idx;


public:
    /**
     * @brief       Construct a new CompatAdjacencyList from a list of connections.
     * 
     * @details     This constructor initializes an adjacency list from the
     *              given list of connections.\n 
     *              For each connection in the list, the first value identifies
     *              the node, while the second value identifies the adjacent.
     * 
     * @param Connections A list of connections.
     */
    CompatAdjacencyList(const std::vector<std::pair<int, int>>& Connections);

    /**
     * @brief       Copy constructor.
     * 
     * @details     This constructor initializes an adjacency list as a
     *              copy of the given one.
     * 
     * @param AL The list to copy.
     */
    CompatAdjacencyList(const cut::BaseAdjacencyList& AL);

    /**
     * @brief       Move constructor.
     * 
     * @details     This constructor initializes an adjacency list by moving
     *              the memory from the given adjacency list.\n 
     *              This constructor invalidates the input.
     * 
     * @param AL The adjacency list to move.
     */
    CompatAdjacencyList(cut::CompatAdjacencyList&& AL);

    virtual cut::BaseAdjacencyList& operator=(const cut::BaseAdjacencyList& AL) override;

    /**
     * @brief       Assignment-move operator.
     * 
     * @details     This operator updates this adjacency list by moving
     *              the memory from the given adjacency list.\n 
     *              This operator invalidates the input.
     * 
     * @param AL The adjacency list to move.
     */
    virtual cut::CompatAdjacencyList& operator=(cut::CompatAdjacencyList&& AL);
    virtual ~CompatAdjacencyList();

    virtual int NumNodes() const override;
    virtual int NumConnections() const override;
    virtual int NumAdjacents(int i) const override;
    virtual int GetAdjacent(int i, int idx) const override;
};

} // namespace cut
