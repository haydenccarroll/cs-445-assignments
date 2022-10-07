#pragma once

#include "AST/AST.hpp"

#include <memory>
#include <string>
#include <vector>

struct TokenData {
    int tokenclass;   // token class
    unsigned linenum; // what line did this token occur on?
    std::string tokenstr;
    int idIndex; // index for id
};