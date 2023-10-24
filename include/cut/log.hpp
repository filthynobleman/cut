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
    /**
     * @brief       Simple messages.
     * 
     * @details     Simple messages, useful to output statuses, updates, or generic informations.
     */
    MESSAGE     = 1,

    /**
     * @brief       Warning messages.
     * 
     * @details     Warning messages, useful to notify something is not working as expected, but
     *              it's not harmful.
     */
    WARNING     = 2,

    /**
     * @brief       Error messages.
     * 
     * @details     Error messages, useful to notify that there is something wrong and that the
     *              program should be terminated, or at least rolled back to a safe status.
     */
    ERROR       = 4,

    /**
     * @brief       Every type of message.
     * 
     * @details     Identifies all the types of messages.
     */
    ALL         = 7,

    /**
     * @brief       Only important messages.
     * 
     * @details     Identifies only the types of messages that are considered important,
     *              excluding simple messages. Useful to reduce the verbosity of a logger.
     */
    IMPORTANT   = 6,

    /**
     * @brief       No messages.
     * 
     * @details     Identifies no types of message. Useful to disable a logger temporarily.
     */
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




    /**
     * @brief       Return the mask for filtering the log types.
     * 
     * @details     Return the mask for filtering the log types.
     * 
     * @return cut::LogType The filter mask.
     */
    cut::LogType GetMask() const;

    /**
     * @brief       Set the mask for filtering the log types.
     * 
     * @details     Set the mask for filtering the log types.
     * 
     * @param Mask The filter mask.
     */
    void SetMask(cut::LogType Mask);

    /**
     * @brief       Enables the given types.
     * 
     * @details     This method updates the log mask to enable logging of the
     *              given types, without enabling or disabling other types.
     * 
     * @param Types The log types to enable.
     */
    void Enable(cut::LogType Types);

    /**
     * @brief       Disable the given types.
     * 
     * @details     This method updates the log mask to disable logging of the
     *              given types, without enabling or disabling other types.
     * 
     * @param Types The log types to disable.
     */
    void Disable(cut::LogType Types);

    /**
     * @brief       Enable logging of simple messages.
     * 
     * @details     Enable logging of simple messages.
     */
    void EnableMessages();
    /**
     * @brief       Enable logging of warnings.
     * 
     * @details     Enable logging of warnings.
     */
    void EnableWarnings();
    /**
     * @brief       Enable logging of errors.
     * 
     * @details     Enable logging of errors.
     */
    void EnableErrors();

    /**
     * @brief       Disable logging of simple messages.
     * 
     * @details     Disable logging of simple messages.
     */
    void DisableMessages();
    /**
     * @brief       Disable logging of warnings.
     * 
     * @details     Disable logging of warnings.
     */
    void DisableWarnings();
    /**
     * @brief       Disable logging of errors.
     * 
     * @details     Disable logging of errors.
     */
    void DisableErrors();



    /**
     * @brief       Determine whether or not timestamps are logged.
     * 
     * @details     This method tells if this logger also outputs timestamps attached
     *              to the messages.
     * 
     * @return true If timestamps are used.
     * @return false If timestamps are not used.
     */
    bool HasTimestamps() const;

    /**
     * @brief       Decide whether or not to use timestamps.
     * 
     * @details     This method sets this logger to also output timestamps attached
     *              to the messages.
     * 
     * @param Timestamps Whether or not to use timestamps.
     */
    void UseTimestamps(bool Timestamps);

    /**
     * @brief       Enable the use of timestamps.
     * 
     * @details     Enable the use of timestamps.
     */
    void EnableTimestamps();
    /**
     * @brief       Disable the use of timestamps.
     * 
     * @details     Disable the use of timestamps.
     */
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
