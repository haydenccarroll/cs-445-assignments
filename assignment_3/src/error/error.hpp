#pragma once

#include <string>
#include <iostream>

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

    static unsigned int getErrorCount() { return s_errorCount; }

    static unsigned int getWarningCount() { return s_warningCount; }

private:
    inline static unsigned int s_errorCount = 0;
    inline static unsigned int s_warningCount = 0;
};
