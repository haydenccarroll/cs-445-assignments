#pragma once

#include <string>

class Options
{
public:
    Options(int argc, char** argv);
    ~Options();
    FILE* getFile() { return m_file; };
    std::string getFileName() { return m_fileName; }
    bool isdFlag() { return m_isdFlag; }
    bool ispFlag() { return m_ispFlag; }

private:
    bool m_isdFlag, m_ispFlag;
    FILE* m_file = nullptr;
    std::string m_fileName;
};
