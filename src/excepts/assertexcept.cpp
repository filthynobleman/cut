/**
 * @file        assertexcept.cpp
 * 
 * @brief       Implements cut::AssertError.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-10-09
 */
#include <cut/excepts/assertexcept.hpp>
#include <sstream>


cut::AssertionError::AssertionError(const std::string& Msg)
    : m_Msg(Msg), std::runtime_error("")
{ }

cut::AssertionError::AssertionError(const std::string& Code,
                                    const std::string& File,
                                    int Line)
    : std::runtime_error("")
{
    std::stringstream ss;
    ss << "Assertion failed at " << File << ':' << Line << ". ";
    ss << "( " << Code << " )";
    m_Msg = ss.str();
}


cut::AssertionError::~AssertionError() { }

char const* cut::AssertionError::what() const noexcept
{
    return m_Msg.c_str();
}