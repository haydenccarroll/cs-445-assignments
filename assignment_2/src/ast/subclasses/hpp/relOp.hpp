#pragma once

#include "../../node.hpp"
#include "../../../types.hpp"

#include <iostream>

class RelOpNode : public ASTNode
{
public:
    RelOpNode(unsigned int lineNum, RelOpType type);
    void printNode() { std::cout << "Op: " << relOpTypeToStr(m_relOpType); }


private:
    const RelOpType m_relOpType;
};
