/**
 * @file        time.cpp
 * 
 * @brief       Test time functionalitites of the library.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-10-24
 */
#include <cut/time/time.hpp>
#include <iostream>
#include <random>
#include <algorithm>


void busy()
{
    std::mt19937 Eng(0);
    std::uniform_int_distribution<int> Dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    std::vector<int> V;
    V.resize(256 * 256 * 256);
    for (int i = 0; i < V.size(); ++i)
        V[i] = Dist(Eng);
    std::sort(V.begin(), V.end());
}

int main(int argc, const char* const argv[])
{
    cut::Timestamp Begin;
    std::cout << "Test started at " << Begin.ToString() << '.' << std::endl;
    std::cout << "Three time zones to the left is " << Begin.ToString(-3, "%F %T") << '.' << std::endl;
    std::cout << "Two time zones to the right is " << Begin.ToString(2, "%F %T") << '.' << std::endl;

    cut::Timer::AttachTimer("zero");

    cut::Timer::AttachTimer("first");
    busy();
    cut::Timer::GetTimer("first").Pause();
    std::cout << "After the first busy() call, time on timer \'first\' is " << cut::Timer::GetTimer("first").GetTime() << " seconds." << std::endl;
    std::cout << "CPU time of \'first\' is " << cut::Timer::GetTimer("first").GetCPUTime() << " seconds." << std::endl;

    std::cout << "Timer \'first\' is paused." << std::endl;

    std::cout << "Second busy() call with a different timer, not initialized... ";
    cut::Timer::AttachTimer("second", false);
    busy();
    std::cout << "Time on timer \'second\' is " << cut::Timer::GetTimer("second").GetTime() << std::endl;

    cut::Timer::GetTimer("first").Start();
    busy();
    std::cout << "After the third busy() call, time on timer \'first\' is " << cut::Timer::GetTimer("first").GetTime() << " seconds." << std::endl;
    std::cout << "CPU time of \'first\' is " << cut::Timer::GetTimer("first").GetCPUTime() << " seconds." << std::endl;

    
    cut::Timer::GetTimer("zero").Pause();
    std::cout << "Total time is:" << std::endl;
    std::cout << "  - seconds:      " << cut::Timer::GetTimer("zero").GetTime(cut::TimerPrecision::SECONDS) << std::endl;
    std::cout << "  - milliseconds: " << cut::Timer::GetTimer("zero").GetTime(cut::TimerPrecision::MILLISECONDS) << std::endl;
    std::cout << "  - microseconds: " << cut::Timer::GetTimer("zero").GetTime(cut::TimerPrecision::MICROSECONDS) << std::endl;
    std::cout << "  - nanoseconds:  " << cut::Timer::GetTimer("zero").GetTime(cut::TimerPrecision::NANOSECONDS) << std::endl;

    cut::Timestamp End;
    std::cout << "Program ended at " << End.ToString("%T %F") << std::endl;




    return 0;
}