/**
 * @file        nullptrexcept.cpp
 * 
 * @brief       Implements cut::NullPtrError.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-10-09
 */
#include <cut/excepts/nullptrexcept.hpp>
#include <sstream>


cut::NullPtrError::NullPtrError(const std::string& Msg)
    : m_Msg(Msg), std::runtime_error("")
{ }

cut::NullPtrError::NullPtrError(const std::string& Code,
                                const std::string& File,
                                int Line)
    : std::runtime_error("")
{
    std::stringstream ss;
    ss << "Null pointer detected at " << File << ':' << Line << ". ";
    ss << "( " << Code << " )";
    m_Msg = ss.str();
}


cut::NullPtrError::~NullPtrError() { }

char const* cut::NullPtrError::what() const noexcept
{
    return m_Msg.c_str();
}