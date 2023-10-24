/**
 * @file        timer.cpp
 * 
 * @brief       Implements class cut::Timer.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-10-24
 */
#include <cut/time/timer.hpp>
#include <cut/excepts/excepts.hpp>



std::unordered_map<std::string, cut::Timer> cut::Timer::m_Timers;


cut::Timer::Timer(bool StartNow)
{
    Reset(StartNow);
}


cut::Timer::~Timer() { }



void cut::Timer::Start()
{
    if (!IsPaused())
        return;

    m_IsPause = false;
    m_Start = std::chrono::system_clock::now();
    m_CPUStart = clock();
}

void cut::Timer::Pause()
{
    if (IsPaused())
        return;

    clock_t CPUEnd = clock();
    std::chrono::system_clock::time_point End;
    End = std::chrono::system_clock::now();
    m_Tot += (End - m_Start);
    m_CPUTot += (CPUEnd - m_CPUStart);
    m_IsPause = true;
}

void cut::Timer::Reset(bool Restart)
{
    m_Tot = std::chrono::system_clock::duration(0);
    m_CPUTot = 0;
    m_IsPause = true;

    if (Restart)
        Start();
}



bool cut::Timer::IsPaused() const { return m_IsPause; }

double cut::Timer::GetTime() const
{
    std::chrono::system_clock::duration ET = m_Tot;
    if (!IsPaused())
    {
        std::chrono::system_clock::time_point End;
        End = std::chrono::system_clock::now();
        ET += End - m_Start;;
    }
    size_t ETns = std::chrono::duration_cast<std::chrono::nanoseconds>(ET).count();
    return 1.0e-9 * ETns;
}

size_t cut::Timer::GetTime(cut::TimerPrecision Precision) const
{
    CUTAssert((Precision == cut::TimerPrecision::SECONDS) || 
              (Precision == cut::TimerPrecision::MILLISECONDS) || 
              (Precision == cut::TimerPrecision::MICROSECONDS) || 
              (Precision == cut::TimerPrecision::NANOSECONDS));

    std::chrono::system_clock::duration ET = m_Tot;
    if (!IsPaused())
    {
        std::chrono::system_clock::time_point End;
        End = std::chrono::system_clock::now();
        ET += End - m_Start;;
    }
    size_t ETcast;
    switch (Precision)
    {
    case cut::TimerPrecision::SECONDS:
        ETcast = std::chrono::duration_cast<std::chrono::seconds>(ET).count();
        break;
    
    case cut::TimerPrecision::MILLISECONDS:
        ETcast = std::chrono::duration_cast<std::chrono::milliseconds>(ET).count();
        break;

    case cut::TimerPrecision::MICROSECONDS:
        ETcast = std::chrono::duration_cast<std::chrono::microseconds>(ET).count();
        break;
        
    case cut::TimerPrecision::NANOSECONDS:
        ETcast = std::chrono::duration_cast<std::chrono::nanoseconds>(ET).count();
        break;
    }
    return ETcast;
}

double cut::Timer::GetCPUTime() const
{
    clock_t ET = m_CPUTot;
    if (!IsPaused())
    {
        clock_t CPUEnd = clock();
        ET += CPUEnd - m_CPUStart;
    }
    return ET / ((double)CLOCKS_PER_SEC);
}




void cut::Timer::AttachTimer(const std::string& Name, bool StartNow)
{
    CUTAssert(m_Timers.find(Name) == m_Timers.end());

    m_Timers.emplace(Name, StartNow);
}

cut::Timer& cut::Timer::GetTimer(const std::string& Name)
{
    CUTAssert(m_Timers.find(Name) != m_Timers.end());
    return m_Timers[Name];
}

void cut::Timer::DeleteTimer(const std::string& Name)
{
    CUTAssert(m_Timers.find(Name) != m_Timers.end());
    m_Timers.erase(Name);
}