
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

    bool dFlag, pFlag, errFlag = false;
    std::optional<std::string> fileName;

    while (true) {
        // hunt for a string of options
        while ((c = ourGetopt(argc, argv, (char *)"dDpP")) != EOF)
            switch (c) {
            case 'd':
                dFlag = true;
                break;
            case 'p':
                pFlag = true;
                break;
            }

        // report any errors or usage request
        if (errFlag) {
            std::cout << "error, invalid flags/arguments provided to program." << std::endl;
            exit(EXIT_FAILURE);
        }

        // pick off a nonoption
        if (optind < argc) {
            fileName = argv[optind];
            optind++;
        }
        else {
            break;
        }
    }
}
