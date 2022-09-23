#ifndef SCANTYPE_H
#define SCANTYPE_H

#include <string>

struct TokenData {
    std::string tokenStr;
    std::string stringConst;
    char charConst;
    int numConst;
    int boolConst;
    int tokenclass;
    int lineNum;
};

#endif