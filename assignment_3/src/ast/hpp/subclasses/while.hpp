#pragma once

#include "../node.hpp"

#include <iostream>

class WhileNode : public ASTNode
{
public:
    WhileNode(unsigned int lineNum);
    void printNode() { std::cout << "While"; }

private:
};
