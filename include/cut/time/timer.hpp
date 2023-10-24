/**
 * @file        timer.hpp
 * 
 * @brief       A class implementing a timer.
 * 
 * @details     This file contains the declaration of the class cut::Timer, which
 *              implements a fine grained timer.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-10-13
 */
#pragma once

#include <chrono>
#include <ctime>
#include <unordered_map>
#include <string>

namespace cut
{


/**
 * @brief       Enumeration of timer precisions.
 * 
 * @details     This enumeration provides the available precisions for the time
 *              recorded by the class cut::Timer.
 */
enum TimerPrecision
{
    SECONDS,
    MILLISECONDS,
    MICROSECONDS,
    NANOSECONDS
};
    

/**
 * @brief       A class implementing a system timer.
 * 
 * @details     The class cut::Timer provides an easy interface to a system timer.\n 
 *              The timer records both the wall clock time and the CPU time, and allows
 *              for basic operations like pausing and resetting.\n 
 *              The class also exposes static access to global timers by means of unique
 *              names.
 */
class Timer
{
private:
    /**
     * @brief       Wall clock start.
     * @details     Wall clock start.
     */
    std::chrono::system_clock::time_point m_Start;

    /**
     * @brief       Total wall clock time accumulated.
     * @details     Total wall clock time accumulated.
     */
    std::chrono::system_clock::duration m_Tot;

    /**
     * @brief       CPU clock start.
     * @details     CPU clock start.
     */
    std::clock_t m_CPUStart;

    /**
     * @brief       Total CPU clock time accumulated.
     * @details     Total CPU clock time accumulated.
     */
    std::clock_t m_CPUTot;

    /**
     * @brief       Determine if in pause.
     * @details     Determine if in pause.
     */
    bool m_IsPause;


    /**
     * @brief       The map associating the static timers to their name.
     * @details     The map associating the static timers to their name.
     */
    static std::unordered_map<std::string, cut::Timer> m_Timers;


public:
    /**
     * @brief       Create a new object of type cut::Timer.
     * 
     * @details     This constructor initializes a new cut::Timer.\n 
     *              If the parameter StartNow is set to true (default), the timer will
     *              immediatly start after the object has been created.
     * 
     * @param StartNow Determine whether or not the timer should start after construction.
     */
    Timer(bool StartNow = true);

    /**
     * @brief       Default destructor.
     * 
     * @details     Default destructor.
     */
    ~Timer();


    /**
     * @brief       Start/resume the timer.
     * 
     * @details     This method starts the timer.\n 
     *              If the timer is paused, the method resumes the timer.\n 
     *              If the timer is running, the method does nothing.
     */
    void Start();

    /**
     * @brief       Pause the timer.
     * 
     * @details     This method set the timer on pause.\n 
     *              If the timer is paused or not yet started, the method does nothing.
     */
    void Pause();

    /**
     * @brief       Reset the timer.
     * 
     * @details     This method resets the timer, deleting the time spent in pause.\n 
     *              If the parameter Restart is set to true (default is false), the timer
     *              is started again after the reset.
     */
    void Reset(bool Restart = false);

    /**
     * @brief       Tell if timer is paused.
     * 
     * @details     This method tells whether or not the timer is in pause.
     * 
     * @return true If the timer is paused.
     * @return false If the timer is running.
     */
    bool IsPaused() const;

    /**
     * @brief       Return the wall clock time in seconds.
     * 
     * @details     This method returns the wall clock time passed since the timer started, 
     *              ignoring the time spent in pause.\n 
     *              The time is returned in seconds, using a floating point value up to 
     *              nanoseconds precision.
     * 
     * @return double The wall clock time in seconds.
     */
    double GetTime() const;

    /**
     * @brief       Returnt he wall clock time with the required precision.
     * 
     * @details     This method returns the wall clock time passed since the timer started,
     *              ignoring the time spent in pause.\n 
     *              The time is returns with the specified precision, using an integer value.
     * 
     * @param Precision The precision required by the timer.
     * @return std::size_t The wall clock time with the required precision.
     */
    std::size_t GetTime(cut::TimerPrecision Precision) const;

    /**
     * @brief       Return the CPU clock time in seconds.
     * 
     * @details     This method returns the CPU clock time passed since the timer started, 
     *              ignoring the time spent in pause.\n 
     *              The time is returned in seconds, using a floating point value.
     * 
     * @return double The CPU clock time in seconds.
     */
    double GetCPUTime() const;




    /**
     * @brief       Create a new static timer with the given name.
     * 
     * @details     This method creates a new global timer, associating it with the given name.\n 
     *              For the construction arguments, please refer to cut::Timer().\n 
     *              If a timer with this name does already exist, a cut::AssertError is thrown.
     * 
     * @param Name The name of the timer.
     * @param StartNow Determine whether or not the timer should start after construction.
     * 
     * @throws cut::AssertError if a timer with the same name already exists.
     */
    static void AttachTimer(const std::string& Name, bool StartNow = true);

    /**
     * @brief       Get the global timer with the given name.
     * 
     * @details     This method returns the global timer associated with the given name.\n 
     *              If a timer with this name does not exist, a cut::AssertError is thrown.
     * 
     * @param Name The name of the timer.
     * @return cut::Timer& The timer with the given name.
     * 
     * @throws cut::AssertError if a timer with the given name does not exist.
     */
    static cut::Timer& GetTimer(const std::string& Name);

    /**
     * @brief       Delete the global timer with the given name.
     * 
     * @details     This method deletes the global timer associated with the given name.\n 
     *              If a timer with this name does not exist, a cut::AssertError is thrown.
     * 
     * @param Name The name of the timer.
     * 
     * @throws cut::AssertError if a timer with the given name does not exist.
     */
    static void DeleteTimer(const std::string& Name);
    
};


} // namespace cut
