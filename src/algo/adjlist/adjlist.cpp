/**
 * @file        adjlist.cpp
 * 
 * @brief       Implementation of cut::AdjacencyList.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-11-15
 */
#include <cut/algo/adjlist.hpp>
#include <cut/excepts/excepts.hpp>
#include <typeinfo>
#include <algorithm>


cut::AdjacencyList::AdjacencyList(int N)
    : cut::BaseAdjacencyList()
{
    m_Adj.resize(N);
    m_NConnections = 0;
}

cut::AdjacencyList::AdjacencyList(const std::vector<std::pair<int,int>>& Connections)
    : cut::BaseAdjacencyList()
{
    m_NConnections = Connections.size();
    // Get the number of nodes
    int NNodes = 0;
    for (const std::pair<int, int>& c : Connections)
        NNodes = std::max(NNodes, c.first + 1);
    if (NNodes == 0)
    {
        m_Adj.resize(0);
        return;
    }
    // Get the number of connections per node
    std::vector<int> NConns;
    NConns.resize(NNodes, 0);
    for (const std::pair<int, int>& c : Connections)
        NConns[c.first]++;
    // Resize the adjacency list properly
    m_Adj.resize(NNodes);
    for (int i = 0; i < NNodes; ++i)
        m_Adj[i].reserve(NConns[i]);
    for (const std::pair<int, int>& c : Connections)
    {
        try
        {
            AddAdjacent(c.first, c.second);
        }
        catch(const std::exception& e) { }
        
    }
}

cut::AdjacencyList::AdjacencyList(const cut::BaseAdjacencyList& AL)
    : cut::BaseAdjacencyList(AL)
{
    // If same class, it's easy
    try
    {
        const cut::AdjacencyList& FAL = dynamic_cast<const cut::AdjacencyList&>(AL);
        m_Adj = FAL.m_Adj;
        m_NConnections = FAL.m_NConnections;
    }
    catch(const std::bad_cast& e) { }
    catch(const std::exception& e)
    {
        throw e;
    }
    
    // Otherwise, use abstract interface
    m_NConnections = AL.NumConnections();
    // Get the number of nodes
    int NNodes = AL.NumNodes();
    m_Adj.resize(NNodes);
    if (NNodes == 0)
        return;
    // Fill adjacency list
    for (int i = 0; i < NNodes; ++i)
    {
        int NAdjs = AL.NumAdjacents(i);
        m_Adj[i].reserve(NAdjs);
        for (int j = 0; j < NAdjs; ++j)
            m_Adj[i].push_back(AL.GetAdjacent(i, j));
    }
}

cut::AdjacencyList::AdjacencyList(cut::BaseAdjacencyList&& AL)
    : cut::BaseAdjacencyList()
{
    try
    {
        cut::AdjacencyList&& FAL = dynamic_cast<cut::AdjacencyList&&>(AL);
        m_Adj = std::move(FAL.m_Adj);
        m_NConnections = FAL.m_NConnections;
    }
    catch(const std::exception& e)
    {
        throw e;
    }   
}

cut::BaseAdjacencyList& cut::AdjacencyList::operator=(const cut::BaseAdjacencyList& AL)
{
    cut::BaseAdjacencyList::operator=(AL);
    // If same class, it's easy
    try
    {
        const cut::AdjacencyList& FAL = dynamic_cast<const cut::AdjacencyList&>(AL);
        m_Adj = FAL.m_Adj;
        m_NConnections = FAL.m_NConnections;
    }
    catch(const std::bad_cast& e) { }
    catch(const std::exception& e)
    {
        throw e;
    }
    
    // Otherwise, use abstract interface
    m_NConnections = AL.NumConnections();
    // Get the number of nodes
    int NNodes = AL.NumNodes();
    m_Adj.resize(NNodes);
    if (NNodes == 0)
        return *this;
    // Fill adjacency list
    for (int i = 0; i < NNodes; ++i)
    {
        int NAdjs = AL.NumAdjacents(i);
        m_Adj[i].reserve(NAdjs);
        for (int j = 0; j < NAdjs; ++j)
            m_Adj[i].push_back(AL.GetAdjacent(i, j));
    }

    return *this;
}

cut::AdjacencyList& cut::AdjacencyList::operator=(cut::BaseAdjacencyList&& AL)
{
    try
    {
        cut::AdjacencyList&& FAL = dynamic_cast<cut::AdjacencyList&&>(AL);
        m_Adj = std::move(FAL.m_Adj);
        m_NConnections = FAL.m_NConnections;
    }
    catch(const std::exception& e)
    {
        throw e;
    }
    return *this;
}

cut::AdjacencyList::~AdjacencyList() { }

int cut::AdjacencyList::NumNodes() const { return m_Adj.size(); }
int cut::AdjacencyList::NumConnections() const { return m_NConnections; }
int cut::AdjacencyList::NumAdjacents(int i) const
{
    CUTCheckGEQ(i, 0);
    CUTCheckLess(i, NumNodes());

    return m_Adj[i].size();
}
int cut::AdjacencyList::GetAdjacent(int i, int idx) const
{
    CUTCheckGEQ(i, 0);
    CUTCheckLess(i, NumNodes());
    CUTCheckGEQ(idx, 0);
    CUTCheckLess(idx, NumAdjacents(i));

    return m_Adj[i][idx];
}


void cut::AdjacencyList::AddNode()
{
    m_Adj.emplace_back();
}

void cut::AdjacencyList::InsertNode(int i)
{
    CUTCheckGEQ(i, 0);
    CUTCheckLess(i, NumNodes());

    m_Adj.emplace(m_Adj.begin() + i);
}

void cut::AdjacencyList::SwapNodes(int i, int j)
{
    CUTCheckGEQ(i, 0);
    CUTCheckLess(i, NumNodes());
    CUTCheckGEQ(j, 0);
    CUTCheckLess(j, NumNodes());

    std::swap(m_Adj[i], m_Adj[j]);
}

void cut::AdjacencyList::RemoveNode(int i)
{
    CUTCheckGEQ(i, 0);
    CUTCheckLess(i, NumNodes());

    m_Adj.erase(m_Adj.begin() + i);
}


void cut::AdjacencyList::AddAdjacent(int i, int j)
{
    CUTCheckGEQ(i, 0);
    CUTCheckLess(i, NumNodes());
    CUTAssert(std::find(m_Adj[i].begin(), m_Adj[i].end(), j) == m_Adj[i].end());

    m_Adj[i].emplace_back(j);
}

void cut::AdjacencyList::InsertAdjacent(int i, int j, int idx)
{
    CUTCheckGEQ(i, 0);
    CUTCheckLess(i, NumNodes());
    CUTCheckGEQ(idx, 0);
    CUTCheckLess(idx, NumAdjacents(i));
    CUTAssert(std::find(m_Adj[i].begin(), m_Adj[i].end(), j) == m_Adj[i].end());

    m_Adj[i].emplace(m_Adj[i].begin() + idx, j);
}

void cut::AdjacencyList::UpdateAdjacent(int i, int j, int idx)
{
    CUTCheckGEQ(i, 0);
    CUTCheckLess(i, NumNodes());
    CUTCheckGEQ(idx, 0);
    CUTCheckLess(idx, NumAdjacents(i));

    // Ignore if the update does not change the value
    if (m_Adj[i][idx] == j)
        return;

    CUTAssert(std::find(m_Adj[i].begin(), m_Adj[i].end(), j) == m_Adj[i].end());
    m_Adj[i][idx] = j;
}

void cut::AdjacencyList::ReplaceAdjacent(int i, int j, int k)
{
    CUTCheckGEQ(i, 0);
    CUTCheckLess(i, NumNodes());
    CUTAssert(std::find(m_Adj[i].begin(), m_Adj[i].end(), k) == m_Adj[i].end());

    auto j_pos = std::find(m_Adj[i].begin(), m_Adj[i].end(), j);
    CUTAssert(j_pos != m_Adj[i].end());
    *j_pos = k;
}

void cut::AdjacencyList::RemoveAdjacent(int i, int idx)
{
    CUTCheckGEQ(i, 0);
    CUTCheckLess(i, NumNodes());
    CUTCheckGEQ(idx, 0);
    CUTCheckLess(idx, NumAdjacents(i));

    m_Adj[i].erase(m_Adj[i].begin() + idx);
}