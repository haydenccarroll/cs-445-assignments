#pragma once

#include "../../node.hpp"
#include "../../../types.hpp"

#include <iostream>

class IfNode : public ASTNode
{
public:
    IfNode(unsigned int lineNum);
    void printNode() { std::cout << "If"; }

private:
};
