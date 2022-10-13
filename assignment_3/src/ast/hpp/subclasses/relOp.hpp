#pragma once

#include "../node.hpp"
#include "../../../types/types.hpp"

#include <iostream>

class RelOpNode : public ASTNode
{
public:
    /**
     * @brief Construct a new Rel Op Node object
     * 
     * @param lineNum 
     * @param type type of relational operator used
     */
    RelOpNode(unsigned int lineNum, RelOpType type);
    void printNode() { std::cout << "Op: " << relOpTypeToStr(m_relOpType); }
    NodeType getNodeType() { return NodeType::RelOpNode; }


private:
    const RelOpType m_relOpType;
};
