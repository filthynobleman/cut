/**
 * @file        timestamp.hpp
 * 
 * @brief       A class representing a timestamp.
 * 
 * @details     This file contains the declaration of the class cut::Timestamp,
 *              which is used to represent timestamps.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-10-24
 */
#pragma once

#include <chrono>
#include <string>


namespace cut
{

/**
 * @brief       A class representing timestamps.
 * 
 * @details     The class cut::Timestamp is used to represent timestamps and time points.\n 
 *              It is basically a wrapper for the C/C++ structure std::time_t, and its main
 *              goal is to provide an easy interface for obtaining the current time as string.
 */
class Timestamp
{
private:
    /**
     * @brief       Time time registered by the timestamp.
     * @details     Time time registered by the timestamp.
     */
    std::chrono::system_clock::time_point m_TS;


public:
    /**
     * @brief       Create a timestamp at the current time.
     * 
     * @details     This constructor creates a new timestamp, initializing it to the
     *              time when the object has been created.\n 
     *              Time timestamp is initialized using the system time zone.
     */
    Timestamp();

    /**
     * @brief       Default destructor.
     * 
     * @details     Default destructor.
     */
    ~Timestamp();


    /**
     * @brief       Return the timestamp as formatted string, after conversion to desired UTC.
     * 
     * @details     This method returns the string that, acoording to the given formatting,
     *              represents this timestamp. For additional details about the formatting
     *              options, please refer to the documentation for std::put_time()
     *              ( https://en.cppreference.com/w/cpp/io/manip/put_time )\n 
     *              Before formatting, the timestamp is converted to the given UTC.\n 
     * 
     * @warning     With the current implementation, the class cut::Timestamp is not aware
     *              of the local time zone, and assumes the system clock being located at UTC+0.\n 
     *              This could change in the future.
     * 
     * @param UTC The target time zone.
     * @param Format The format for this timestamp.
     * @return std::string The formatted timestamp.
     */
    std::string ToString(int UTC, const std::string& Format) const;

    /**
     * @brief       Return the timestamp as formatted string.
     * 
     * @details     This method returns the string that, acoording to the given formatting,
     *              represents this timestamp. For additional details about the formatting
     *              options, please refer to the documentation for std::put_time()
     *              ( https://en.cppreference.com/w/cpp/io/manip/put_time )\n 
     *              The timestamp is formatted using the local time zone.
     * 
     * @warning     With the current implementation, the class cut::Timestamp is not aware
     *              of the local time zone, and assumes the system clock being located at UTC+0.\n 
     *              This could change in the future.
     * 
     * @param Format The format for this timestamp.
     * @return std::string The formatted timestamp.
     */
    std::string ToString(const std::string& Format) const;

    /**
     * @brief       Return the timestamp as formatted string.
     * 
     * @details     This method returns the string that represents this timestamp.\n 
     *              Time timestamp is formatted as yyyy-mm-dd HH:MM:SS.\n 
     *              The timestamp is formatted using the local time zone.
     * 
     * @warning     With the current implementation, the class cut::Timestamp is not aware
     *              of the local time zone, and assumes the system clock being located at UTC+0.\n 
     *              This could change in the future.
     * 
     * @return std::string The formatted timestamp.
     */
    std::string ToString() const;
};

} // namespace cut
