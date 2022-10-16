#pragma once

#include "decl.hpp"
#include "../../../types/types.hpp"

class ParamNode : public DeclNode
{
public:
    /**
     * @brief Construct a new Param Node object
     * 
     * @param lineNum 
     * @param paramName name of parameter
     * @param dataType datatype of parameter (concrete type such as int, bool... may)
     *                 not be known yet. can be set later with setTypeSpec()
     */
    ParamNode(unsigned int lineNum, std::string paramName, DataType dataType);
    void printNode();
    NodeType getNodeType() { return NodeType::ParamNode; }

    /**
     * @brief sets the concrete type (int bool char string) of a parameter
     * 
     * @param type type to set
     */
    void setTypeSpec(DataTypeEnum type);
};
