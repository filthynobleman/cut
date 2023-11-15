/**
 * @file        cadjlist.cpp
 * 
 * @brief       Implementation of cut::CompatAdjacencyList.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-11-15
 */
#include <cut/algo/adjlist.hpp>
#include <cut/memory/memory.hpp>
#include <algorithm>
#include <typeinfo>


cut::CompatAdjacencyList::CompatAdjacencyList(const std::vector<std::pair<int,int>>& Connections)
    : cut::BaseAdjacencyList()
{
    // Sort the connections and get the number of nodes
    int NConns = Connections.size();
    std::pair<int, int>* Conns = cut::AllocCopy(Connections.data(), NConns);
    std::sort(Conns, Conns + NConns);
    int NNodes = Conns[NConns - 1].first + 1;

    // Initialize the data
    m_Adj.reserve(NConns);
    m_Idx.resize(NNodes + 1);
    int CurNode = 0;
    for (int i = 0; i < NConns; ++i)
    {
        int Node = Conns[i].first;
        while (Node > CurNode)
        {
            CurNode += 1;
            m_Idx[CurNode + 1] = m_Idx[CurNode];
        }
        m_Adj.emplace_back(Conns[i].second);
        m_Idx[CurNode + 1] += 1;
    }

    free(Conns);
}


cut::CompatAdjacencyList::CompatAdjacencyList(const cut::BaseAdjacencyList& AL)
    : cut::BaseAdjacencyList(AL)
{
    // If same class, it's easy
    try
    {
        const cut::CompatAdjacencyList& CAL = dynamic_cast<const cut::CompatAdjacencyList&>(AL);
        m_Adj = CAL.m_Adj;
        m_Idx = CAL.m_Idx;
    }
    catch(const std::bad_cast& e) { }
    catch(const std::exception& e)
    {
        throw e;
    }

    // Otherwise, use abstract interface
    int NNodes = AL.NumNodes();
    m_Adj.reserve(AL.NumConnections());
    m_Idx.resize(NNodes + 1);
    // Fill the data
    for (int i = 0; i < NNodes; ++i)
    {
        int NAdjs = AL.NumAdjacents(i);
        m_Idx[i + 1] = m_Idx[i] + NAdjs;
        for (int j = 0; j < NAdjs; ++j)
            m_Adj.emplace_back(AL.GetAdjacent(i, j));
    }
}

cut::CompatAdjacencyList::CompatAdjacencyList(cut::CompatAdjacencyList&& AL)
    : cut::BaseAdjacencyList()
{
    m_Adj = std::move(AL.m_Adj);
    m_Idx = std::move(AL.m_Idx);
}

cut::CompatAdjacencyList& cut::CompatAdjacencyList::operator=(const cut::BaseAdjacencyList& AL)
{
    cut::BaseAdjacencyList::operator=(AL);
    
    // If same class, it's easy
    try
    {
        const cut::CompatAdjacencyList& CAL = dynamic_cast<const cut::CompatAdjacencyList&>(AL);
        m_Adj = CAL.m_Adj;
        m_Idx = CAL.m_Idx;
    }
    catch(const std::bad_cast& e) { }
    catch(const std::exception& e)
    {
        throw e;
    }

    // Otherwise, use abstract interface
    int NNodes = AL.NumNodes();
    m_Adj.reserve(AL.NumConnections());
    m_Idx.resize(NNodes + 1);
    // Fill the data
    for (int i = 0; i < NNodes; ++i)
    {
        int NAdjs = AL.NumAdjacents(i);
        m_Idx[i + 1] = m_Idx[i] + NAdjs;
        for (int j = 0; j < NAdjs; ++j)
            m_Adj.emplace_back(AL.GetAdjacent(i, j));
    }

    return *this;
}

cut::CompatAdjacencyList& cut::CompatAdjacencyList::operator=(cut::CompatAdjacencyList&& AL)
{
    m_Adj = std::move(AL.m_Adj);
    m_Idx = std::move(AL.m_Idx);
    return *this;
}

cut::CompatAdjacencyList::~CompatAdjacencyList() { }


int cut::CompatAdjacencyList::NumNodes() const { return m_Idx.size() - 1; }
int cut::CompatAdjacencyList::NumConnections() const { return m_Adj.size(); }
int cut::CompatAdjacencyList::NumAdjacents(int i) const
{
    CUTCheckGEQ(i, 0);
    CUTCheckLess(i, NumNodes());

    return m_Idx[i + 1] - m_Idx[i];
}
int cut::CompatAdjacencyList::GetAdjacent(int i, int idx) const
{
    CUTCheckGEQ(i, 0);
    CUTCheckLess(i, NumNodes());
    CUTCheckGEQ(idx, 0);
    CUTCheckLess(idx, NumAdjacents(i));

    return m_Adj[m_Idx[i] + idx];
}