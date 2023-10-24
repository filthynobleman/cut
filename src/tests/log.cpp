/**
 * @file        log.cpp
 * 
 * @brief       Application for testing the class cut::Logger.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-10-24
 */
#include <cut/log.hpp>


int main(int argc, const char* const argv[])
{
    cut::Logger::AttachLogger("first", "first.log");
    cut::Logger::GetLogger("first").Message("This is a message.");
    cut::Logger::GetLogger("first").Warning("This is a warning.");
    cut::Logger::GetLogger("first").Error("This is an error.");
    
    cut::Logger::GetLogger("first").Disable(cut::LogType::IMPORTANT);
    cut::Logger::GetLogger("first").Message("This is a message.");
    cut::Logger::GetLogger("first").Warning("This is a warning.");
    cut::Logger::GetLogger("first").Error("This is an error.");
    
    cut::Logger::GetLogger("first").Enable(cut::LogType::ALL);
    cut::Logger::GetLogger("first").Message("This is a message.");
    cut::Logger::GetLogger("first").Warning("This is a warning.");
    cut::Logger::GetLogger("first").Error("This is an error.");

    cut::Logger::AttachLogger("second", "second.log", cut::LogType::IMPORTANT, false);
    cut::Logger::GetLogger("second").Message("This is a message.");
    cut::Logger::GetLogger("second").Warning("This is a warning.");
    cut::Logger::GetLogger("second").Error("This is an error.");

    cut::Logger::DeleteLogger("first");
    
    
    cut::Logger::GetLogger("second").EnableTimestamps();
    cut::Logger::GetLogger("second").Enable(cut::LogType::NONE);
    cut::Logger::GetLogger("second").Message("This is a message.");
    cut::Logger::GetLogger("second").Warning("This is a warning.");
    cut::Logger::GetLogger("second").Error("This is an error.");
    



    return 0;
}