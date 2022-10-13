#pragma once

#include <string>
#include <iostream>

inline void Error(unsigned int lineNum, std::string msg)
{
    std::cout << "ERROR(" << lineNum << "): " << msg << std::endl;
}

inline void Warning(unsigned int lineNum, std::string msg)
{
    std::cout << "WARNING(" << lineNum << "): " << msg << std::endl;
}
