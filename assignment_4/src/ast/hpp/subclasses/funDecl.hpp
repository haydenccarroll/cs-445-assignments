#pragma once

#include "decl.hpp"
#include "../../../types/types.hpp"

class FunDeclNode : public DeclNode
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
    virtual NodeType getNodeType() { return NodeType::FunDeclNode; }
    virtual void printTypedNode() { printNode(); }

private:
};
