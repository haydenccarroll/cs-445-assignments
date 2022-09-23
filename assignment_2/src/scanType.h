#ifndef SCANTYPE_H
#define SCANTYPE_H

#include "Tree/Tree.h"

#include <string>
#include <vector>
#include <memory>

struct TokenData {
    int tokenclass;
    unsigned lineNum;
    std::string tokenStr;
};

#endif