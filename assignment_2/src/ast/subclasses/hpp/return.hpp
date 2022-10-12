#pragma once

#include "../../node.hpp"
#include "../../../types.hpp"

#include <iostream>

class ReturnNode : public ASTNode
{
public:
    ReturnNode(unsigned int lineNum);
    void printNode() { std::cout << "Return"; }

private:
};
