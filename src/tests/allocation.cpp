/**
 * @file        allocation.cpp
 * 
 * @brief       Test memory allocation routines.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-10-09
 */
#include <cut/memory/allocation.hpp>
#include <iostream>

#define _N 1024


int main(int argc, const char* const argv[])
{
    int* Array1;
    int* Array2;

    int N = _N;
    if (argc > 1)
        N = std::atoi(argv[1]);

    Array1 = cut::Calloc<int>(N);
    for (int i = 0; i < N; ++i)
        CUTAssert(Array1[i] == 0);
    std::cout << "Calloc behaving as expected." << std::endl;
    free(Array1);

    Array1 = cut::AllocInit<int>(N, 1);
    for (int i = 0; i < N; ++i)
    {
        CUTAssert(Array1[i] == 1);
        Array1[i] = i;
    }
    std::cout << "AllocInit (hence Malloc) behaving as expected." << std::endl;
    
    Array2 = cut::AllocCopy(Array1, N);
    for (int i = 0; i < N; ++i)
        CUTAssert(Array1[i] == Array2[i]);
    std::cout << "AllocCopy (hence Memcpy) behaving as expected." << std::endl;



    free(Array1);
    free(Array2);

    return 0;
}