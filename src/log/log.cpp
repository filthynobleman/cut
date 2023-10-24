/**
 * @file        log.cpp
 * 
 * @brief       Implements cut::Logger.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-10-24
 */
#include <cut/log.hpp>
#include <cut/time/timestamp.hpp>
#include <cut/excepts/excepts.hpp>



std::unordered_map<std::string, cut::Logger> cut::Logger::m_Logs;


cut::Logger::Logger(const std::string& LogFile,
                    cut::LogType Mask,
                    bool WithTimestamps)
    : m_Timestamp(WithTimestamps),
      m_Mask(Mask),
      m_Filename(LogFile)
{
    m_Stream.open(m_Filename, std::ios::out);
    CUTAssert(m_Stream.is_open());
}


cut::Logger::~Logger()
{
    m_Stream.close();
}


void cut::Logger::Log(cut::LogType Type,
                      const std::string& Msg)
{
    CUTAssert((Type == cut::LogType::MESSAGE) || (Type == cut::LogType::WARNING) || (Type == cut::LogType::ERROR));

    // Ignore disabled log types
    if ((((int)Type) & ((int)m_Mask)) == 0)
        return;

    if (HasTimestamps())
        m_Stream << cut::Timestamp().ToString() << ' ';
    
    switch (Type)
    {
    case cut::LogType::MESSAGE:
        m_Stream << "(MESSAGE): ";
        break;
        
    case cut::LogType::WARNING:
        m_Stream << "(WARNING): ";
        break;
        
    case cut::LogType::ERROR:
        m_Stream << "(ERROR): ";
        break;
    
    default:
        break;
    }

    m_Stream << Msg << std::endl;
}

void cut::Logger::Message(const std::string& Msg)   { Log(cut::LogType::MESSAGE, Msg); }
void cut::Logger::Warning(const std::string& Msg)   { Log(cut::LogType::WARNING, Msg); }
void cut::Logger::Error(const std::string& Msg)     { Log(cut::LogType::ERROR, Msg); }


cut::LogType cut::Logger::GetMask() const { return m_Mask; }
void cut::Logger::SetMask(cut::LogType Mask) { m_Mask = Mask; }

void cut::Logger::Enable(cut::LogType Types)
{
    m_Mask = (cut::LogType)(((int)m_Mask) | ((int)Types));
}
void cut::Logger::Disable(cut::LogType Types)
{
    m_Mask = (cut::LogType)(((int)m_Mask) & ~((int)Types));
}


void cut::Logger::EnableMessages()  { Enable(cut::LogType::MESSAGE); }
void cut::Logger::DisableMessages() { Disable(cut::LogType::MESSAGE); }
void cut::Logger::EnableWarnings()  { Enable(cut::LogType::WARNING); }
void cut::Logger::DisableWarnings() { Disable(cut::LogType::WARNING); }
void cut::Logger::EnableErrors()    { Enable(cut::LogType::ERROR); }
void cut::Logger::DisableErrors()   { Disable(cut::LogType::ERROR); }


bool cut::Logger::HasTimestamps() const { return m_Timestamp; }
void cut::Logger::UseTimestamps(bool WithTimestamps) { m_Timestamp = WithTimestamps; }
void cut::Logger::EnableTimestamps() { m_Timestamp = true; }
void cut::Logger::DisableTimestamps() { m_Timestamp = false; }






void cut::Logger::AttachLogger(const std::string& Name,
                               const std::string& LogFile,
                               cut::LogType Mask,
                               bool WithTimestamp)
{
    CUTAssert(m_Logs.find(Name) == m_Logs.end());

    m_Logs.emplace(std::piecewise_construct,
                   std::forward_as_tuple(Name),
                   std::forward_as_tuple(LogFile, Mask, WithTimestamp));
}

cut::Logger& cut::Logger::GetLogger(const std::string& Name)
{
    CUTAssert(m_Logs.find(Name) != m_Logs.end());
    return m_Logs.at(Name);
}

void cut::Logger::DeleteLogger(const std::string& Name)
{
    CUTAssert(m_Logs.find(Name) != m_Logs.end());
    m_Logs.erase(Name);
}