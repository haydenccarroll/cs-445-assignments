#pragma once

#include "decl.hpp"
#include "../../../types/include.hpp"

#include <string>

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
    std::string toString(bool printType=false) override;
    NodeType getNodeType() override { return NodeType::FunDeclNode; }

private:
};
