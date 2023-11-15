/**
 * @file        adjmap.hpp
 * 
 * @brief       Classes implementing weighted adjacency lists.
 * 
 * @details     This file contains the declaration of classes that specializes
 *              the adjacency lists by adding weighted connections.\n 
 *              The file contains an abstract class cut::BaseWeightedMap, which
 *              extends cut::BaseAdjacencyList, and two derived classes,
 *              cut::WeightedMap and cut::CompatWeightedMap, respectively extending
 *              also cut::AdjacencyList and cut::CompatAdjacencyList.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-11-15
 */
#pragma once

#include <cut/algo/adjlist.hpp>


namespace cut
{
    
/**
 * @brief       Base class for weighted adjacency lists.
 * 
 * @details     The class cut::BaseWeightedMap extends cut::BaseAdjacencyList,
 *              and provides an abstract interface for weighted adjacency lists.\n 
 *              On top of an adjacency list, a weighted adjaceny list provides
 *              access to the weight of the connections.
 */
class BaseWeightedMap : public cut::BaseAdjacencyList
{
public:
    /**
     * @brief       Empty constructor.
     * 
     * @details     This constructor initializes an empty weighte adjacency list.
     */
    BaseWeightedMap();

    /**
     * @brief       Copy constructor.
     * 
     * @details     This constructor initializes a new weighted adjacency list
     *              as a copy of the given adjacency list.\n 
     *              If the given adjacency list is unweighted, all the weights
     *              are set to 1.
     * 
     * @param[in] AL The adjacency list to copy.
     */
    BaseWeightedMap(const cut::BaseAdjacencyList& AL);

    /**
     * @brief       Assignment-copy operator.
     * 
     * @details     This operator updates this weighted adjacency list to make
     *              it a copy of the given one.\n 
     *              If the given adjacency list is unweighted, all the weights
     *              are set to 1.
     * 
     * @param[in] AL The adjacency list to copy.
     * @return cut::BaseAdjacencyList& This weighted adjacency list after the assignment.
     */
    virtual cut::BaseAdjacencyList& operator=(const cut::BaseAdjacencyList& AL) = 0;

    /**
     * @brief       Default destructor.
     * 
     * @details     Default destructor.
     */
    virtual ~BaseWeightedMap();

    /**
     * @brief       Get the weighte of a connection.
     * 
     * @details     This method returns the weight of the connection with
     *              index <code>idx</code> in the connection list of node
     *              <code>i</code>.
     * 
     * @param[in] i The index of a node.
     * @param[in] idx The index of a connection.
     * @return double The weight of the connection.
     */
    virtual double GetWeight(int i, int idx) const = 0;

    /**
     * @brief       Syntactic sugar for <code>GetAdjacent()</code> and
     *              <code>GetWeight()</code>.
     * 
     * @details     Syntactic sugar for <code>GetAdjacent()</code> and
     *              <code>GetWeight()</code>.\n 
     *              The operator returns the value of the connection and
     *              assigns to the reference parameter <code>weight</code>
     *              the weight of the connection.
     * 
     * @param[in] i The index of a node.
     * @param[in] idx The indec of a connection.
     * @param[out] weight The weight of the connection.
     * @return int The value of the connection.
     */
    virtual int operator()(int i, int idx, double& weight) const;
};



class WeightedMap : public cut::BaseWeightedMap, public cut::AdjacencyList
{
protected:
    /**
     * @brief       The weights of the connections.
     * 
     * @details     The weights of the connections.
     */
    std::vector<std::vector<double>> m_Weights;


public:
    /**
     * @brief       Construct a new WeightedMap with N nodes.
     * 
     * @details     This constructor initializes an adjacency list with 
     *              N nodes.\n 
     *              The list has no connections.
     * 
     * @param N The number of nodes.
     */
    WeightedMap(int N);

    /**
     * @brief       Construct a new WeightedMap from a list of connections and weights.
     * 
     * @details     This constructor initializes an adjacency list from the
     *              given list of connections and weighs.\n 
     *              For each connection in the list, the first value identifies
     *              the node, while the second value identifies the adjacent.\n 
     *              The value <code>Weights[i]</code> is the weight of the
     *              connection <code>Connections[i]</code>.
     * 
     * @throws cut::AssertionError If the vector of connections and weights do not
     * have the same length.
     * 
     * @param Connections A list of connections.
     * @param Weights The list of connections' weights.
     */
    WeightedMap(const std::vector<std::pair<int, int>>& Connections,
                const std::vector<double>& Weights);

    /**
     * @brief       Copy constructor.
     * 
     * @details     This constructor initializes a weighted adjacency list as a
     *              copy of the given adjacency list.\n 
     *              If the list is unweighted, all the weights are initialized to 1.
     * 
     * @param AL The list to copy.
     */
    WeightedMap(const cut::BaseAdjacencyList& AL);

    /**
     * @brief       Move constructor.
     * 
     * @details     This constructor initializes a weighted adjacency list by 
     *              moving the memory from the given weighted adjacency list.\n 
     *              This constructor invalidates the input.
     * 
     * @param WM The list to copy.
     */
    WeightedMap(cut::WeightedMap&& WM);

    virtual cut::BaseAdjacencyList& operator=(const cut::BaseAdjacencyList& AL) override;

    /**
     * @brief       Assignment-move operator.
     * 
     * @details     This operator updates a weighted adjacency list by 
     *              moving the memory from the given weighted adjacency list.\n 
     *              This operator invalidates the input.
     * 
     * @param WM The list to move.
     * @return cut::WeightedMap& This list after the assignment.
     */
    virtual cut::WeightedMap& operator=(cut::WeightedMap&& WM);

    /**
     * @brief       Default destructor.
     * 
     * @details     Default destructor.
     */
    ~WeightedMap();

    virtual double GetWeight(int i, int idx) const;

    virtual void AddNode();
    virtual void InsertNode(int i);
    virtual void SwapNodes(int i, int j);
    virtual void RemoveNode(int i);

    virtual void AddAdjacent(int i, int j);
    virtual void InsertAdjacent(int i, int j, int idx);
    virtual void UpdateAdjacent(int i, int j, int idx);
    virtual void ReplaceAdjacent(int i, int j, int k);
    virtual void RemoveAdjacent(int i, int idx);

    /**
     * @brief       Add a new weighted adjacent.
     * 
     * @details     This method adds a new weighted adjacent to the
     *              connection list of <code>i</code>.\n 
     *              The value is the first element of the pair, while
     *              the weight is the second element.
     * 
     * @throws cut::OutOfBoundError if <code>i >= NumNodes()</code>.
     * @throws cut::AssertionError if <code>j</code> is already an adjacent of <code>i</code>.
     * 
     * @param i The index of a node.
     * @param j The connection to add.
     */
    virtual void AddAdjacent(int i, const std::pair<int, double>& j);

    /**
     * @brief       Add the given weighted adjancent to the given node.
     * 
     * @details     This method adds the value <code>j</code> as an adjacent
     *              of the node <code>i</code>, assigning it the index
     *              <code>idx</code> in the list of <code>i</code>'s
     *              connections, and shifting forward all the following
     *              connections.\n 
     *              The value is the first element of the pair, while
     *              the weight is the second element.
     * 
     * @throws cut::OutOfBoundError if <code>i >= NumNodes()</code>.
     * @throws cut::AssertionError if <code>j</code> is already an adjacent of <code>i</code>.
     * @throws cut::OutOfBoundError if <code>idx >= NumAdjacents(i)</code>.
     * 
     * @param i The index of a node.
     * @param j The new adjacent.
     * @param idx The index of the connection.
     */
    virtual void InsertAdjacent(int i, const std::pair<int, double>& j, int idx);

    /**
     * @brief       Updates the adjancent to the given value.
     * 
     * @details     This method updates the connection with index <code>idx</code>
     *              from node <code>i</code> to point to the value <code>j</code>.\n 
     *              The value is the first element of the pair, while
     *              the weight is the second element.
     * 
     * @throws cut::OutOfBoundError if <code>i >= NumNodes()</code>.
     * @throws cut::AssertionError if <code>j</code> is already an adjacent of <code>i</code>.
     * @throws cut::OutOfBoundError if <code>idx >= NumAdjacents(i)</code>.
     * 
     * @param i The index of a node.
     * @param j The new value of the adjacent.
     * @param idx The index of the connection.
     */
    virtual void UpdateAdjacent(int i, const std::pair<int, double>& j, int idx);

    /**
     * @brief       Replace the weight of the given adjacent with a new one.
     * 
     * @details     This method replaces the weight of the adjacent value 
     *              <code>j</code> in the connection list of node <code>i</code> 
     *              with the new weight <code>k</code>.
     * 
     * @throws cut::OutOfBoundError if <code>i >= NumNodes()</code>.
     * @throws cut::AssertionError if <code>j</code> is not an adjacent of <code>i</code>.
     * @throws cut::AssertionError if <code>k</code> is already an adjacent of <code>i</code>.
     * 
     * @param i The index of a node.
     * @param j The value of the adjacent to replace.
     * @param k The new weight of the replaced adjacent.
     */
    virtual void ReplaceAdjacent(int i, int j, double k);

    /**
     * @brief       Replace the given weighted adjacent with a new one.
     * 
     * @details     This method replaces the weighted adjacent value 
     *              <code>j</code> in the connection list of node <code>i</code> 
     *              with the a new weighted adjacent <code>k</code>.
     * 
     * @throws cut::OutOfBoundError if <code>i >= NumNodes()</code>.
     * @throws cut::AssertionError if <code>j</code> is not an adjacent of <code>i</code>.
     * @throws cut::AssertionError if <code>k</code> is already an adjacent of <code>i</code>.
     * 
     * @param i The index of a node.
     * @param j The value of the adjacent to replace.
     * @param k The new weighted adjacent of the replaced adjacent.
     */
    virtual void ReplaceAdjacent(int i, int j, const std::pair<int, double>& k);
};



class CompatWeightedMap : public cut::BaseWeightedMap, cut::CompatAdjacencyList
{
protected:
    /**
     * @brief       The list of weights.
     * 
     * @details     The list of weights.
     */
    std::vector<double> m_Weights;
    
public:
    /**
     * @brief       Construct a new CompatWeightedMap from a list of connections 
     *              and weights.
     * 
     * @details     This constructor initializes an adjacency list from the
     *              given list of connections and weighs.\n 
     *              For each connection in the list, the first value identifies
     *              the node, while the second value identifies the adjacent.\n 
     *              The value <code>Weights[i]</code> is the weight of the
     *              connection <code>Connections[i]</code>.
     * 
     * @throws cut::AssertionError If the vector of connections and weights do not
     * have the same length.
     * 
     * @param Connections A list of connections.
     * @param Weights The list of connections' weights.
     */
    CompatWeightedMap(const std::vector<std::pair<int, int>>& Connections,
                      const std::vector<double>& Weights);

    /**
     * @brief       Copy constructor.
     * 
     * @details     This constructor initializes a weighted adjacency list as a
     *              copy of the given adjacency list.\n 
     *              If the list is unweighted, all the weights are initialized to 1.
     * 
     * @param AL The list to copy.
     */
    CompatWeightedMap(const cut::BaseAdjacencyList& AL);

    /**
     * @brief       Move constructor.
     * 
     * @details     This constructor initializes a weighted adjacency list by 
     *              moving the memory from the given weighted adjacency list.\n 
     *              This constructor invalidates the input.
     * 
     * @param WM The list to copy.
     */
    CompatWeightedMap(cut::WeightedMap&& WM);

    virtual cut::BaseAdjacencyList& operator=(const cut::BaseAdjacencyList& AL) override;

    /**
     * @brief       Assignment-move operator.
     * 
     * @details     This operator updates a weighted adjacency list by 
     *              moving the memory from the given weighted adjacency list.\n 
     *              This operator invalidates the input.
     * 
     * @param WM The list to move.
     * @return cut::WeightedMap& This list after the assignment.
     */
    virtual cut::CompatWeightedMap& operator=(cut::CompatWeightedMap&& WM);

    /**
     * @brief       Default destructor.
     * 
     * @details     Default destructor.
     */
    ~CompatWeightedMap();

    virtual double GetWeight(int i, int idx) const;
};


} // namespace cut
