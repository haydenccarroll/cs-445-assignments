#include "Options.h"
#include "ourgetopt/ourgetopt.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

Options::Options(int argc, char **argv)
{
    bool errflag = false;
    bool hflag = false;

    char c;
    extern char *optarg;
    extern int optind;

    while (true)
    {
        while ((c = ourGetopt(argc, argv, (char *)"hpd")) != EOF)
        {
            switch (c)
            {
            case 'p':
                _print = true;
                break;
            case 'd':
                _debug = true;
                break;
            case 'h':
                hflag = true;
                break;
            default:
                errflag = true;
                break;
            }
        }

        if (hflag)
        {
            std::cout << "This is a parser for the C- programming language." << std::endl;
            std::cout << "You can pass in files to be parsed, or parse input from the command line.\n"
                      << std::endl;

            std::cout << "usage: " << argv[0] << " [-h] [-p] [-d] files..."
                      << std::endl;
            std::cout << "-h:\tDisplays this output" << std::endl;
            std::cout << "-p:\tPrint the AST after building it" << std::endl;
            std::cout << "-d:\tShow debugging information while building the AST\n"
                      << std::endl;
            exit(EXIT_SUCCESS);
        }
        else if (errflag)
        {
            std::cerr << "usage: " << argv[0] << " [-h] [-p] [-d] files..." << std::endl;
            exit(EXIT_SUCCESS);
        }
        else
        {
            if (optind < argc)
            {
                _files.push_back(argv[optind]);
                optind++;
            }
            else
            {
                break;
            }
        }
    }
}

bool Options::print() const
{
    return _print;
}

bool Options::debug() const
{
    return _debug;
}

const std::vector<std::string> &Options::files() const
{
    return _files;
}