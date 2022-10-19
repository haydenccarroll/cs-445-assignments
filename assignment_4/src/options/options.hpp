#pragma once

#include <string>

class Options
{
public:
    Options(int argc, char** argv);
    std::string getFileName() { return m_fileName; }
    void printHelpScreen();
    bool isdFlag() { return m_isdFlag; }
    bool ispFlag() { return m_ispFlag; }
    bool isDFlag() { return m_isDFlag; }
    bool isPFlag() { return m_isPFlag; }
    bool ishFlag() { return m_ishFlag; }

private:
    bool m_isdFlag, m_ispFlag, m_isPFlag, m_isDFlag, m_ishFlag;
    std::string m_fileName;
};
