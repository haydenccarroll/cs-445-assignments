#pragma once

#include <string>
#include <iostream>
#include <sstream>

class Error
{
public:
    Error(){};
    static void error(unsigned int lineNum, std::string msg)
    {
        std::cout << "ERROR(" << lineNum << "): " << msg << std::endl;
        s_errorCount++;
    }

    static void warning(unsigned int lineNum, std::string msg)
    {
        std::cout << "WARNING(" << lineNum << "): " << msg << std::endl;
        s_warningCount++;
    }

    static void critical(unsigned int lineNum, std::string msg)
    {
        std::stringstream ss;
        ss << "CRITICAL(" << lineNum << "): " << msg << std::endl;
        throw std::runtime_error(ss.str());

    }

    static void arglist(std::string msg)
    {
        std::cout << "ERROR(ARGLIST): " << msg << std::endl;
        s_errorCount++;
        
    }

    static void linker(std::string msg)
    {
        std::cout << "ERROR(LINKER): " << msg << std::endl;
        s_errorCount++;
    }

    static unsigned int getErrorCount() { return s_errorCount; }

    static unsigned int getWarningCount() { return s_warningCount; }

private:
    inline static unsigned int s_errorCount = 0;
    inline static unsigned int s_warningCount = 0;
};
