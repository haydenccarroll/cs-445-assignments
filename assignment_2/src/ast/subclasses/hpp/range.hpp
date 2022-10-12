#pragma once

#include "../../node.hpp"
#include "../../../types.hpp"

#include <iostream>

class RangeNode : public ASTNode
{
public:
    RangeNode(unsigned int lineNum);
    void printNode() { std::cout << "Range"; }

private:
};
