/**
 * @file        boundsexcept.hpp
 * 
 * @brief       This file contains the declaration of cut::OutOfBoundError, which
 *              realizes an expection specifically designed for signaling values out
 *              of desired bounds.
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
 * @brief       This class realizes an exception designed to signal out of bound errors.
 * 
 * @details     The class cut::OutOfBoundError realizes a specific instance of exception
 *              which is specifically designed for signaling the presence of values that
 *              exceed desired bounds.
 */
class OutOfBoundError : public std::runtime_error
{
private:
    /**
     * @brief       The error message.
     */
    std::string m_Msg;

public:
    /**
     * @brief       Construct a cut::OutOfBoundError from a given error message.
     * 
     * @details     Construct a cut::OutOfBoundError from a given error message.
     * 
     * @param Msg The error message to throw.
     */
    OutOfBoundError(const std::string& Msg);

    /**
     * @brief       Construct a cut::OutOfBoundError from specialized info.
     * 
     * @details     Construct a cut::OutOfBoundError constructing the error message from
     *              the code that generated the error, plus the information on which
     *              file and line of code contain that code.
     * 
     * @param Code The code raising the error.
     * @param File The file containing the code.
     * @param Line The line containing the code.
     */
    OutOfBoundError(const std::string& Code, const std::string& File, int Line);

    /**
     * @brief       Default destructor.
     * 
     * @details     Default destructor.
     */
    virtual ~OutOfBoundError();

    virtual char const* what() const noexcept override;
};






#define CUTCheckLess(x, ub) do {\
    if ((x) >= (ub))\
        throw cut::OutOfBoundError(__CUT_2_STR((x) < (ub)), __FILE__, __LINE__);\
} while(0)

#define CUTCheckLEQ(x, ub) do {\
    if ((x) > (ub))\
        throw cut::OutOfBoundError(__CUT_2_STR((x) <= (ub)), __FILE__, __LINE__);\
} while(0)

#define CUTCheckGreater(x, ub) do {\
    if ((x) <= (ub))\
        throw cut::OutOfBoundError(__CUT_2_STR((x) > (ub)), __FILE__, __LINE__);\
} while(0)

#define CUTCheckGEQ(x, ub) do {\
    if ((x) < (ub))\
        throw cut::OutOfBoundError(__CUT_2_STR((x) >= (ub)), __FILE__, __LINE__);\
} while(0)



} // namespace cut
