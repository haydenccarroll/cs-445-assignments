#pragma once

#include "../node.hpp"
#include "../../../types/types.hpp"

class AssignOpNode : public ASTNode
{
public:
    /**
     * @brief Construct a new Assign Op Node object
     * 
     * @param lineNum 
     * @param type The type of assignment operator used
     */
    AssignOpNode(unsigned int lineNum, AssignOpType type);
    void printNode();

private:
    const AssignOpType m_assignOpType;
};
