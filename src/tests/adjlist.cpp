/**
 * @file        adjlist.cpp
 * 
 * @brief       Application to test the adjacency lists.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-11-17
 */
#include <cut/algo/adjlist.hpp>
#include <iostream>

const int M = 5;
const int N = 2 * M;

int main(int argc, const char* const argv[])
{
    // Make a set of pairs joining each node to node N
    std::vector<std::pair<int, int>> Pairs;
    Pairs.reserve(N);
    for (int i = 0; i < N; ++i)
        Pairs.emplace_back(i, N);

    // Create a compacted adjacency list from the pairs
    cut::CompatAdjacencyList CAL(Pairs);

    // Make the list editable
    cut::AdjacencyList FAL(CAL);

    // Check the list is correct
    if (FAL.NumNodes() != N)
        return -1;
    for (int i = 0; i < N; ++i)
    {
        if (FAL.NumAdjacents(i) != 1)
            return -1;
        if (FAL.GetAdjacent(i, 0) != N)
            return -1;
    }

    // Fill the list so that node i has all adjacents >= i
    for (int i = 0; i < N; ++i)
    {
        for (int j = i; j < N - 1; ++j)
            FAL.AddAdjacent(i, j);
    }

    // Remove the odd nodes
    for (int i = N - 1; i >= 0; i -= 2)
        FAL.RemoveNode(i);
    // Check number of nodes
    if (FAL.NumNodes() != M)
        return -1;

    // Remove the odd adjacents
    for (int i = 0; i < FAL.NumNodes(); ++i)
    {
        int Idx = FAL.NumAdjacents(i) - 1;
        while (Idx >= 0)
        {
            if (FAL.GetAdjacent(i, Idx) % 2 != 0)
                FAL.RemoveAdjacent(i, Idx);
            Idx -= 1;
        }

        // Check adjacents are all even numbers
        for (int j = 0; j < FAL.NumAdjacents(i); ++j)
        {
            if (FAL.GetAdjacent(i, j) % 2 != 0)
                return -1;
        }
    }

    // Halve all the adjacents
    for (int i = 0; i < FAL.NumNodes(); ++i)
    {
        for (int j = 0; j < FAL.NumAdjacents(i); ++j)
        {
            FAL.UpdateAdjacent(i, FAL.GetAdjacent(i, j) / 2, j);
        }
    }

    // Convert to compact and check correctness
    CAL = cut::CompatAdjacencyList(FAL);
    cut::BaseAdjacencyList& BAL = CAL;
    // Number of nodes must be M
    if (BAL.NumNodes() != M)
        return -1;
    // Node i was previously node 2 * i, and had adjacents >= 2 * i
    // Then everything has been halved, so node i has adjacents >= i
    // Also, all the adjacents were <= N, so now they should all be <= M
    for (int i = 0; i < BAL.NumNodes(); ++i)
    {
        for (int j = 0; j < BAL.NumAdjacents(i); ++j)
        {
            if (i > BAL.GetAdjacent(i, j))
                return -1;
            if (M < BAL.GetAdjacent(i, j))
                return -1;
        }
    }


    return 0;
}