#ifndef OPTIONS_H
#define OPTIONS_H

#include "ourgetopt/ourgetopt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

class Options
{
public:
    Options(int argc, char **argv);
    bool print() const;
    bool debug() const;
    const std::vector<std::string> &files() const;

private:
    std::vector<std::string> _files;
    bool _print = false;
    bool _debug = false;
};

#endif