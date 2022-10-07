#pragma once

#include "ourgetopt/ourgetopt.hpp"

#include <optional>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

class Options {
  public:
    Options(int argc, char **argv);
    bool print() const;
    bool debug() const;
    bool debugSymbolTable() const;
    bool printTypeInfo() const;
    const std::optional<std::string> &file() const;

  private:
    std::optional<std::string> m_file;
    bool m_print = false;
    bool m_debug = false;
    bool m_debugSymTbl = false;
    bool m_printTypeInfo = false;
};