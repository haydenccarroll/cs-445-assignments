#pragma once

#include "exp.hpp"
#include "../../../types/types.hpp"

#include <iostream>

class IdNode : public ExpNode
{
public:
    /**
     * @brief Construct a new Id Node object
     * 
     * @param lineNum 
     */
    IdNode(unsigned int lineNum, std::string idName);
    void printNode() { std::cout << "Id: " << m_idName; }
    NodeType getNodeType() { return NodeType::IdNode; }
    std::string getIdName() { return m_idName; }

private:
    std::string m_idName;
};
