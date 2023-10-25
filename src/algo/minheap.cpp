/**
 * @file        minheap.cpp
 * 
 * @brief       Implements cut::MinHeap.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-10-25
 */
#include <cut/algo/minheap.hpp>
#include <cut/excepts/excepts.hpp>

std::pair<double, size_t> cut::MinHeap::FindMin() const
{
    CUTCheckGreater(Size(), 0);

    return { m_Sign * m_Nodes[0].first, m_Nodes[0].second };
}

size_t cut::MinHeap::Size() const { return m_Nodes.size(); }


void cut::MinHeap::MoveUp(size_t Element)
{
    size_t v = m_Perm[Element];
    while (v != 0)
    {
        size_t p = v >> 1;  // parent is floor(v / 2)
        // if parent is already smaller, it's done
        if (m_Nodes[p].first < m_Nodes[v].first)
            break;

        // exchange node with parent
        std::swap(m_Nodes[p], m_Nodes[v]);

        // remember to swap the permutation to preserve the pointers
        std::swap(m_Perm[m_Nodes[p].second], m_Perm[m_Nodes[v].second]);

        // Next iteration
        v = p;
    }
}

void cut::MinHeap::MoveDown(size_t Element)
{
    size_t v = m_Perm[Element];
    while (true)
    {
        size_t u = 2 * v;
        // If no children, break
        if (u >= Size())
            break;
        // If two children, pick minimum key
        if (u + 1 < Size())
        {
            if (m_Nodes[u].first > m_Nodes[u + 1].first)
                u = u + 1;
        }

        // If children has a larger key, break
        if (m_Nodes[u].first > m_Nodes[v].first)
            break;
        
        // Swap node and children
        std::swap(m_Nodes[v], m_Nodes[u]);

        // remember to swap the permutation to preserve the pointers
        std::swap(m_Perm[m_Nodes[v].second], m_Perm[m_Nodes[u].second]);

        // Next iteration
        v = u;
    }
}

double cut::MinHeap::GetKey(size_t Element) const
{
    CUTCheckLess(Element, Size());

    return m_Sign * m_Nodes[m_Perm[Element]].first;
}

void cut::MinHeap::DecreaseKey(size_t Element, double Decrement)
{
    CUTCheckLess(Element, Size());

    size_t v = m_Perm[Element];
    m_Nodes[v].first -= m_Sign * Decrement;

    // If min-heap, keys are stored positive, decrement reduces the key
    // value and stuff must move up
    if (m_Sign > 0)
        MoveUp(Element);
    // If max-heap, keys are stored negative (but shown positive), decrement
    // increases the key value, and stuff moves down
    else
        MoveDown(Element);
}

void cut::MinHeap::IncreaseKey(size_t Element, double Increment)
{
    CUTCheckLess(Element, Size());

    size_t v = m_Perm[Element];
    m_Nodes[v].first += m_Sign * Increment;

    // If min-heap, keys are stored positive, increment increases the
    // key value, and stuf moves down
    if (m_Sign > 0)
        MoveDown(Element);
    // If max-heap, keys are stored negative (but shown positive), increment
    // decreases the key value, and stuff moves up
    else
        MoveUp(Element);
}


void cut::MinHeap::Insert(double Key)
{
    m_Perm.push_back(m_Nodes.size());
    m_Nodes.emplace_back(m_Sign * Key, m_Nodes.size());
    MoveUp(m_Nodes.size() - 1);
}


cut::MinHeap::MinHeap(const std::vector<double>& Keys,
                      bool IsMaxHeap)
{
    // Min-heap store keys with the right sign.
    // Max-heap store keys with negated sign.
    m_Sign = 1;
    if (IsMaxHeap)
        m_Sign = -1;
    
    // Add one by one and update the heap
    for (double k : Keys)
        Insert(k);
}

cut::MinHeap::~MinHeap() { }