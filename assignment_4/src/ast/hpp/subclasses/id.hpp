#pragma once

#include "exp.hpp"
#include "../../../types/include.hpp"

#include <string>

class IdNode : public ExpNode
{
public:
    /**
     * @brief Construct a new Id Node object
     * 
     * @param lineNum 
     */
    IdNode(int lineNum, std::string idName);
    std::string toString(bool printType=false) override;
    NodeType getNodeType() override { return NodeType::IdNode; }
    std::string getIdName() { return m_idName; }

private:
    std::string m_idName;
};
