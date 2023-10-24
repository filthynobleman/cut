/**
 * @file        timestamp.cpp
 * 
 * @brief       Implements cut::Timestamp.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-10-24
 */
#include <cut/time/timestamp.hpp>
#include <sstream>
#include <ctime>
#include <iomanip>

cut::Timestamp::Timestamp()
{
    m_TS = std::chrono::system_clock::now();
}

cut::Timestamp::~Timestamp() { }


std::string cut::Timestamp::ToString(int UTC, const std::string& Format) const
{
    std::chrono::system_clock::time_point TS = m_TS;
    std::chrono::system_clock::duration UTCShift;
    UTCShift = std::chrono::hours(UTC);
    TS += UTCShift;

    std::stringstream ss;
    const std::time_t TS_t = std::chrono::system_clock::to_time_t(TS);
    ss << std::put_time(std::localtime(&TS_t), Format.c_str());

    return ss.str();
}

std::string cut::Timestamp::ToString(const std::string& Format) const
{
    std::stringstream ss;
    const std::time_t TS_t = std::chrono::system_clock::to_time_t(m_TS);
    ss << std::put_time(std::localtime(&TS_t), Format.c_str());

    return ss.str();
}

std::string cut::Timestamp::ToString() const
{
    return ToString("%F %T");
}