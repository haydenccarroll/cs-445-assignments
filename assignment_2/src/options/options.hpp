#pragma once

#include <string>

class Options
{
public:
    Options(int argc, char** argv);
private:
    bool m_isdFlag, m_ispFlag;
    std::string m_fileName;
};

