#include "Options.h"
#include "ourgetopt/ourgetopt.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

// from ourgetopt
extern int optind;
extern char* optarg;

namespace Options {

Options::Options(int argc, char **argv) {
    char c;
    while (true) {
        while ((c = ourGetopt(argc, argv, (char *)"hpdPD")) != EOF) {
            switch (c) {
            case 'p':
                m_isPrintAST = true;
                break;
            case 'd':
                m_isYYdebug = true;
                break;
            case 'h':
                m_isHelp = true;
                break;
            case 'D':
                m_isSymbolTableDebug = true;
                break;
            case 'P':
                m_isPrintASTWithTypes = true;
                break;
            default:
                m_isError = true;
                break;
            }
        }

        if (m_isError || m_isHelp) {
            std::cout << "usage: c- [options] [sourcefile]\n"
            << "options:\n"
            << "-d - turn on parser debugging\n"
            << "-D - turn on symbol table debugging\n"
            << "-h - print this usage message\n"
            << "-p - print the abstract syntax tree\n"
            << "-P - print the abstract syntax tree plus type information"
            << std::endl;

            exit(!m_isError);
        } else {
            if (optind < argc) {
                m_file = argv[optind];
            }
            break;
        }
    }
}

bool Options::isYYdebug() const
{
    return m_isYYdebug;
}

bool Options::isSymbolTableDebug() const
{
    return m_isSymbolTableDebug;
}

bool Options::isPrintAST() const
{
    return m_isPrintAST;
}

bool Options::isPrintASTWithTypes() const
{
    return m_isPrintASTWithTypes;
}

const std::optional<std::string> Options::file() const 
{
    return m_file;
}

}