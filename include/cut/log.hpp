/**
 * @file        log.hpp
 * 
 * @brief       A class for logging operations.
 * 
 * @details     This file contains the declaration of a class that provides logging operations.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-10-09
 */
#pragma once

#include <string>
#include <fstream>
#include <unordered_map>



namespace cut
{


/**
 * @brief       Types of logging operations.
 * 
 * @details     An enumeration of logging operations.
 */
enum LogType
{
    MESSAGE     = 1,
    WARNING     = 2,
    ERROR       = 4,
    ALL         = 7,
    IMPORTANT   = 6,
    NONE        = 0
};
    

/**
 * @brief       A class for handling logging operations.
 * 
 * @details     The class cut::Logger provides a set of logging operations.\n 
 *              The interface exposes logging functions, as well as masking by message type.\n 
 *              The class also allows for static access to loggers associated to unique names.
 */
class Logger
{
private:
    /**
     * @brief       The path to the log file.
     * @details     The path to the log file.
     */
    std::string         m_Filename;

    /**
     * @brief       The logging stream.
     * @details     The logging stream.
     */
    std::ofstream       m_Stream;

    /**
     * @brief       The mask determining which type of messages must be logged.
     * @details     The mask determining which type of messages must be logged.
     */
    cut::LogType        m_Mask;

    /**
     * @brief       Determines whether or not timestamps must be attached to messages.
     * @details     Determines whether or not timestamps must be attached to messages.
     */
    bool                m_Timestamp;


    /**
     * @brief       The map associating static loggers to their names.
     * @details     The map associating static loggers to their names.
     */
    static std::unordered_map<std::string, cut::Logger> m_Logs;
    
public:
    /**
     * @brief       Create a new logger.
     * 
     * @details     This constructor initializes a new logger outputting to the
     *              file with the given name.\n 
     *              It is possible to determine during the initialization which types of
     *              messages must be logged and if a timestamp must be attached to them.
     * 
     * @param LogFile The log file.
     * @param Mask The mask determining the types of messages.
     * @param WithTimestamp Whether or not a timestamp must be used.
     */
    Logger(const std::string& LogFile,
           cut::LogType Mask = cut::LogType::ALL,
           bool WithTimestamp = true);

    /**
     * @brief       Destroy the logger and closes the stream.
     * 
     * @details     Destroy the logger and closes the stream.
     */
    ~Logger();




    /**
     * @brief       Logs a message of the given type.
     * 
     * @details     The loggers writes a message of the given type. If the type is
     *              masked out, nothing happens.
     * 
     * @param Type The type of message.
     * @param Msg The content of the message.
     */
    void Log(cut::LogType Type, 
             const std::string& Msg);

    /**
     * @brief       Logs a normal message.
     * 
     * @details     Logs a normal message.
     * 
     * @param Msg The content of the message.
     */
    void Message(const std::string& Msg);

    /**
     * @brief       Logs a warning.
     * 
     * @details     Logs a warning.
     * 
     * @param Msg The content of the message.
     */
    void Warning(const std::string& Msg);

    /**
     * @brief       Logs an error.
     * 
     * @details     Logs an error.
     * 
     * @param Msg The content of the message.
     */
    void Error(const std::string& Msg);




    cut::LogType GetMask() const;
    void SetMask(cut::LogType Mask);

    void EnableMessages();
    void EnableWarnings();
    void EnableErrors();
    void DisableMessages();
    void DisableWarnings();
    void DisableErrors();




    bool HasTimestamps() const;
    void UseTimestamps(bool Timestamps);
    void EnableTimestamps();
    void DisableTimestamps();





    /**
     * @brief       Creates a new named logger.
     * 
     * @details     This method creates a new global logger associated with the given name.\n 
     *              For the details about the logger creation, refer to cut::Logger::Logger().\n 
     *              If a logger with this name does already exist, a cut::AssertError is thrown.
     * 
     * @param Name The name of the global logger.
     * @param LogFile The log file.
     * @param Mask The mask determining the types of messages.
     * @param WithTimestamp Whether or not a timestamp must be used.
     * 
     * @throws cut::AssertError If a global logger with the given name already exists.
     */
    static void AttachLogger(const std::string& Name,
                             const std::string& LogFile,
                             cut::LogType Mask = cut::LogType::ALL,
                             bool WithTimestamp = true);

    /**
     * @brief       Get the logger with the given name.
     * 
     * @details     Get the logger with the given name.\n 
     *              If a logger with this name does not exist, a cut::AssertError is thrown.
     * 
     * @param Name The name of a global logger.
     * @return cut::Logger& The logger associated with that name.
     * 
     * @throws cut::AssertError If a global logger with the given name does not exist.
     */
    static cut::Logger& GetLogger(const std::string& Name);

    /**
     * @brief       Deletes the logger with the given name.
     * 
     * @details     Deletes the logger with the given name.\n 
     *              If a logger with this name does not exist, a cut::AssertError is thrown.
     * 
     * @param Name The name of a global logger.
     * 
     * @throws cut::AssertError If a global logger with the given name does not exist.
     */
    static void DeleteLogger(const std::string& Name);
};


} // namespace cut
