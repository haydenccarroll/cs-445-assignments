#pragma once

#include "ourgetopt/ourgetopt.hpp"

#include <optional>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

namespace Options {

class Options {
  public:
    Options(int argc, char **argv);
    bool isYYdebug() const;
    bool isSymbolTableDebug() const;
    bool isPrintAST() const;
    bool isPrintASTWithTypes() const;
    const std::optional<std::string> file() const;

  private:
    std::optional<std::string> m_file;
    bool m_isYYdebug = false;
    bool m_isSymbolTableDebug = false;
    bool m_isPrintAST = false;
    bool m_isPrintASTWithTypes = false;

    bool m_isHelp = false;
    bool m_isError = false;
};

}