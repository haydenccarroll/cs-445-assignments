
#include "options.hpp"

#include "ourgetopt.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <optional>


Options::Options(int argc, char **argv)
{
    int c;
    extern char *optarg;
    extern int optind;

    m_isdFlag = false;
    m_ispFlag = false; 
    bool errFlag = false;

    while (true) {
        // hunt for a string of options
        while ((c = ourGetopt(argc, argv, (char *)"dpDP:")) != EOF)
        {
            std::cout << "getopt c: " << c << std::endl;
            switch (c) {
            case 'd':
                m_isdFlag = true;
                break;
            case 'p':
                m_ispFlag = true;
                break;
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

    m_file = fopen(m_fileName.c_str(), "r");
}
