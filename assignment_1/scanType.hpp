#pragma once

#include <string>

struct TokenData {
    int tokenclass;  // token class
    int linenum;     // what line did this token occur on?
    std::string tokenstr;
    int idIndex;     // index for id
    double numValue; // the value of the number as a DOUBLE!
    char charConst;
    std::string stringConst;
    int numConst;
    int boolConst;
};