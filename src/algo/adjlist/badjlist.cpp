/**
 * @file        badjlist.cpp
 * 
 * @brief       Implementation of the abstract class cut::BadjacencyList.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-11-15
 */
#include <cut/algo/adjlist.hpp>

cut::BaseAdjacencyList::BaseAdjacencyList() { }
cut::BaseAdjacencyList::BaseAdjacencyList(const cut::BaseAdjacencyList &AL) { }
cut::BaseAdjacencyList& cut::BaseAdjacencyList::operator=(const cut::BaseAdjacencyList& AL)
{
    return *this;
}
cut::BaseAdjacencyList::~BaseAdjacencyList() { }

int cut::BaseAdjacencyList::operator()(int i, int idx) const
{
    return GetAdjacent(i, idx);
}