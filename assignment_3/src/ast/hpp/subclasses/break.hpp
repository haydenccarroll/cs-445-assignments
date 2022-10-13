#pragma once

#include "../node.hpp"

#include <iostream>

class BreakNode : public ASTNode
{
public:
    BreakNode(unsigned int lineNum);
    void printNode() { std::cout << "Break"; }

private:
};
