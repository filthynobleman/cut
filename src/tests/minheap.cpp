/**
 * @file        algo.cpp
 * 
 * @brief       Application to test the algorithms & data structures package.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-10-25
 */
#include <cut/algo/minheap.hpp>
#include <vector>
#include <random>
#include <iostream>

std::mt19937 Eng(0);

void Shuffle(std::vector<double>& Vector)
{
    std::uniform_int_distribution<int> Dist(0, Vector.size() - 1);

    for (int i = 0; i < Vector.size(); ++i)
        std::swap(Vector[i], Vector[Dist(Eng)]);
}

void Fill(std::vector<double>& Vector, size_t NElems)
{
    Vector.resize(NElems);
    for (int i = 0; i < NElems; ++i)
        Vector[i] = i;
}


int main(int argc, const char* const argv[])
{
    std::vector<double> V;
    Fill(V, 1000);
    
    std::cout << "Creating min-heap from sorted vector... ";
    cut::MinHeap H1(V);
    std::cout << "Done." << std::endl;
    std::cout << "Min key:     " << H1.FindMin().first << std::endl;
    std::cout << "Min element: " << H1.FindMin().second << std::endl;
    std::cout << "Decreasing element 655 to make it the minimum... ";
    H1.DecreaseKey(655, 656);
    std::cout << "Done." << std::endl;
    std::cout << "Min key:     " << H1.FindMin().first << std::endl;
    std::cout << "Min element: " << H1.FindMin().second << std::endl;
    std::cout << "Increasing elements from 0 to 700 to make 701 the minimum... ";
    for (int i = 0; i < 701; ++i)
        H1.IncreaseKey(i, 1024);
    std::cout << "Done." << std::endl;
    std::cout << "Min key:     " << H1.FindMin().first << std::endl;
    std::cout << "Min element: " << H1.FindMin().second << std::endl;

    std::cout << std::endl;

    std::cout << "Shuffling and creating min-heap from unsorted vector... ";
    Shuffle(V);
    cut::MinHeap H2(V);
    std::cout << "Done." << std::endl;
    std::cout << "Min key:     " << H2.FindMin().first << std::endl;
    std::cout << "Min element: " << H2.FindMin().second << std::endl;
    std::cout << "Decreasing element 655 to make it the minimum... ";
    H2.DecreaseKey(655, 1001);
    std::cout << "Done." << std::endl;
    std::cout << "Min key:     " << H2.FindMin().first << std::endl;
    std::cout << "Min element: " << H2.FindMin().second << std::endl;
    std::cout << "Increasing all elements but 701 to make it the minimum... ";
    for (int i = 0; i < V.size(); ++i)
        H2.IncreaseKey(i, i == 701 ? 0 : 1024);
    std::cout << "Done." << std::endl;
    std::cout << "Min key:     " << H2.FindMin().first << std::endl;
    std::cout << "Min element: " << H2.FindMin().second << std::endl;

    std::cout << std::endl;

    std::cout << "Creating max-heap from unsorted vector... ";
    cut::MinHeap H3(V, true);
    std::cout << "Done." << std::endl;
    std::cout << "Max key:     " << H3.FindMin().first << std::endl;
    std::cout << "Max element: " << H3.FindMin().second << std::endl;
    std::cout << "Increasing element 123 to make it the maximum... ";
    H3.IncreaseKey(123, 1024);
    std::cout << "Done." << std::endl;
    std::cout << "Max key:     " << H3.FindMin().first << std::endl;
    std::cout << "Max element: " << H3.FindMin().second << std::endl;
    std::cout << "Decreasing all elements but 250 to make it the maximum... ";
    for (int i = 0; i < V.size(); ++i)
        H3.DecreaseKey(i, i == 250 ? 0 : 2048);
    std::cout << "Done." << std::endl;
    std::cout << "Max key:     " << H3.FindMin().first << std::endl;
    std::cout << "Max element: " << H3.FindMin().second << std::endl;
}