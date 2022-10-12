#pragma once

#include "../../node.hpp"
#include "../../../types.hpp"

#include <iostream>

class IdNode : public ASTNode
{
public:
    IdNode(unsigned int lineNum, std::string idName, bool isArray);
    IdNode(unsigned int lineNum, std::string idName, bool isArray, int arraySize);
    void printNode() { std::cout << "Id: " << m_idName; }

private:
    std::string m_idName;
    bool m_isArray;
    int m_arraySize;
};
