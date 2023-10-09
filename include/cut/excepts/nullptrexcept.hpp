/**
 * @file        nullptrexcept.hpp
 * 
 * @brief       This file contains the declaration of cut::NullPtrError, which
 *              realizes an expection specifically designed for signaling unwanted
 *              null pointers.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-10-09
 */
#pragma once

#include <string>
#include <stdexcept>
#include <cut/common/common.hpp>

namespace cut
{
    
/**
 * @brief       This class realizes an exception designed to signal null pointers.
 * 
 * @details     The class cut::NullPtrError realizes a specific instance of exception
 *              which is specifically designed for signaling the presence of an unwanted
 *              null pointer.
 */
class NullPtrError : public std::runtime_error
{
private:
    /**
     * @brief       The error message.
     */
    std::string m_Msg;

public:
    /**
     * @brief       Construct a cut::NullPtrError from a given error message.
     * 
     * @details     Construct a cut::NullPtrError from a given error message.
     * 
     * @param Msg The error message to throw.
     */
    NullPtrError(const std::string& Msg);

    /**
     * @brief       Construct a cut::NullPtrError from specialized info.
     * 
     * @details     Construct a cut::NullPtrError constructing the error message from
     *              the code that generated the error, plus the information on which
     *              file and line of code contain that code.
     * 
     * @param Code The code raising the error.
     * @param File The file containing the code.
     * @param Line The line containing the code.
     */
    NullPtrError(const std::string& Code, const std::string& File, int Line);

    /**
     * @brief       Default destructor.
     * 
     * @details     Default destructor.
     */
    virtual ~NullPtrError();

    virtual char const* what() const noexcept override;
};





/**
 * @brief       Check if null and throws an exception.
 * 
 * @details     This macro checks if the given pointer evalautes to null. If so, 
 *              a cut::NullPtrError is thrown.
 * 
 * @param ptr An expression that evaluates to a pointer.
 */
#define CUTCheckNull(ptr) do {\
if ((ptr) == nullptr)\
    throw cut::NullPtrError(__CUT_2_STR(ptr), __FILE__, __LINE__);\
} while(0)



} // namespace cut
