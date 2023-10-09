/**
 * @file        excepts.cpp
 * 
 * @brief       Application to test exceptions.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-10-09
 */
#include <cut/excepts/excepts.hpp>
#include <iostream>

int main(int argc, const char* const argv[])
{
    // Null pointer
    std::cout << "Testing cut::NullPtrError." << std::endl;
    try
    {
        CUTCheckNull(argv);
        std::cout << "  This line is expected to be printed." << std::endl;
        CUTCheckNull(nullptr);
    }
    catch(const std::exception& e)
    {
        std::cout << "  " << e.what() << std::endl;
    }
    std::cout << std::endl;

    // Assertion error
    std::cout << "Testing cut::AssertionError." << std::endl;
    try
    {
        CUTAssert(1 == 1);
        std::cout << "  This line is expected to be printed." << std::endl;
        CUTAssert(1 == 0);
    }
    catch(const std::exception& e)
    {
        std::cout << "  " << e.what() << std::endl;
    }
    std::cout << std::endl;

    // Bounds error
    std::cout << "Testing cut::AssertionError." << std::endl;
    try
    {
        CUTCheckGEQ(argc, 1);
        std::cout << "  This line is expected to be printed." << std::endl;
        CUTCheckLess(argc, 1);
    }
    catch(const std::exception& e)
    {
        std::cout << "  " << e.what() << std::endl;
    }
    



    return 0;
}