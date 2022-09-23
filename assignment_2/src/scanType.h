#pragma once

#include "AST/AST.h"

#include <string>
#include <vector>
#include <memory>

struct TokenData {
    int tokenclass;  // token class
    unsigned linenum;     // what line did this token occur on?
    std::string tokenstr;
    int idIndex;     // index for id
};