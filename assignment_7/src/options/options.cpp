
#include "options.hpp"

#include "ourgetopt.hpp"
#include "../error/include.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <optional>


Options::Options(int argc, char **argv)
{
    extern char *optarg;
    extern int optind;

    m_isdFlag = false;
    m_ispFlag = false;
    m_isPFlag = false;
    m_isDFlag = false;
    m_ishFlag = false;
    m_isMFlag = false;

    // not used now, but could potentially be used in later assignments.
    bool errFlag = false;

    while (true) {
        // hunt for a string of options
        int c;
        while ((c = ourGetopt(argc, argv, (char *)"dpDPhM")) != EOF)
        {
            switch (c) {
            case 'd':
                m_isdFlag = true;
                break;
            case 'p':
                m_ispFlag = true;
                break;
            case 'h':
                m_ishFlag = true;
                break;
            case 'P':
                m_isPFlag = true;
                break;
            case 'D':
                m_isDFlag = true;
                break;
            case 'M':
                m_isMFlag = true;
            }
        }

        // report any errors or usage request
        if (errFlag) {
            std::cout << "error, invalid flags/arguments provided to program." << std::endl;
            exit(EXIT_FAILURE);
        }

        // pick off a nonoption
        if (optind < argc) {
            m_fileName = argv[optind];
            optind++;
        }
        else {
            break;
        }
    }
}

void Options::printHelpScreen()
{
    std::cout << "usage: -c [options] [sourcefile]\n"
              << "options:\n"
              << "-d - turn on parser debugging\n"
              << "-D - turn on symbol table debugging\n"
              << "-h - print this usage message\n"
              << "-p - print the abstract syntax tree\n"
              << "-P - print the abstract syntax tree plus type information\n";
}
