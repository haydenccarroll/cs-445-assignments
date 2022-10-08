#pragma once

#include "Tree/Tree.h"

#include <memory>
#include <string>
#include <vector>

struct TokenData {
    int tokenclass;   // token class
    unsigned lineNum; // what line did this token occur on?
    std::string tokenStr;
    int idIndex; // index for id
};