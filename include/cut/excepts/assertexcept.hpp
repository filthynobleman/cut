/**
 * @file        assertexcept.hpp
 * 
 * @brief       This file contains the declaration of cut::AssertionError, which
 *              realizes an expection specifically designed for signaling failed
 *              assertions.
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
 * @brief       This class realizes an exception designed to signal failed assertions.
 * 
 * @details     The class cut::AssertionError realizes a specific instance of exception
 *              which is specifically designed for signaling the failure of an assertion.
 */
class AssertionError : public std::runtime_error
{
private:
    /**
     * @brief       The error message.
     */
    std::string m_Msg;

public:
    /**
     * @brief       Construct a cut::AssertionError from a given error message.
     * 
     * @details     Construct a cut::AssertionError from a given error message.
     * 
     * @param Msg The error message to throw.
     */
    AssertionError(const std::string& Msg);

    /**
     * @brief       Construct a cut::AssertionError from specialized info.
     * 
     * @details     Construct a cut::AssertionError constructing the error message from
     *              the code that generated the error, plus the information on which
     *              file and line of code contain that code.
     * 
     * @param Code The code raising the error.
     * @param File The file containing the code.
     * @param Line The line containing the code.
     */
    AssertionError(const std::string& Code, const std::string& File, int Line);

    /**
     * @brief       Default destructor.
     * 
     * @details     Default destructor.
     */
    virtual ~AssertionError();

    virtual char const* what() const noexcept override;
};



/**
 * @brief       Check assertion and throws an error.
 * 
 * @details     This macro checks if the given expression evaluates to false. If so,
 *              it throws a cut::AssertionError.
 * 
 * @param expr The expression to evaluate.
 */
#define CUTAssert(expr) do {\
    if (!(expr))\
        throw cut::AssertionError(__CUT_2_STR(expr), __FILE__, __LINE__);\
} while(0)


} // namespace cut
