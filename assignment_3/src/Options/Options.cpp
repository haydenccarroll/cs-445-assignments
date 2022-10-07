#include "Options.hpp"
#include "ourgetopt/ourgetopt.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

Options::Options(int argc, char **argv) {
    bool errflag = false;
    bool hflag = false;

    char c;
    extern char *optarg;
    extern int optind;

    while (true) {
        while ((c = ourGetopt(argc, argv, (char *)"hpdPD")) != EOF) {
            switch (c) {
            case 'p':
                m_print = true;
                break;
            case 'd':
                m_debug = true;
                break;
            case 'h':
                hflag = true;
                break;
            case 'D':
                m_debugSymTbl = true;
                break;
            case 'P':
                m_printTypeInfo = true;
                break;
            default:
                errflag = true;
                break;
            }
        }

        if (hflag || errflag) {
            std::cout << "usage: c- [options] [sourcefile]" << std::endl;
            std::cout << "options:" << std::endl;
            std::cout << "-d - turn on parser debugging" << std::endl;
            std::cout << "-D - turn on symbol table debugging" << std::endl;
            std::cout << "-h - print this usage message" << std::endl;
            std::cout << "-p - print the abstract syntax tree" << std::endl;
            std::cout
                << "-P - print the abstract syntax tree plus type information"
                << std::endl;

            exit(!errflag);
        } else {
            if (optind < argc) {
                m_file = argv[optind];
            }
            break;
        }
    }
}

bool Options::print() const { return m_print; }

bool Options::debug() const { return m_debug; }

bool Options::debugSymbolTable() const { return m_debugSymTbl; }

bool Options::printTypeInfo() const { return m_printTypeInfo; }

const std::optional<std::string> &Options::file() const { return m_file; }