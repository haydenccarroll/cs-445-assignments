#pragma once

#include "../node.hpp"

#include <iostream>

class ForNode : public ASTNode
{
public:
    ForNode(unsigned int lineNum);
    void printNode() { std::cout << "For"; }

private:
};