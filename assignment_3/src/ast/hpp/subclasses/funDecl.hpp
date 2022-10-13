#pragma once

#include "../node.hpp"
#include "../../../types/types.hpp"

class FunDeclNode : public ASTNode
{
public:
    /**
     * @brief Construct a new Fun Decl Node object
     * 
     * @param lineNum 
     * @param funcName name of function declared
     * @param returnType return type of function
     */
    FunDeclNode(unsigned int lineNum, std::string funcName, DataType returnType);
    void printNode();
    NodeType getNodeType() { return NodeType::FunDeclNode; }
private:
    std::string m_funcName;
    DataType m_returnType;
};
