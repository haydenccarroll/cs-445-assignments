#pragma once

#include "../../node.hpp"
#include "../../../types/types.hpp"

#include <iostream>

class UnaryOpNode : public ASTNode
{
public:
    UnaryOpNode(unsigned int lineNum, UnaryOpType type);
    void printNode() { std::cout << "Op: " << unaryOpTypeToStr(m_unaryOpType); }



private:
    const UnaryOpType m_unaryOpType;
};
