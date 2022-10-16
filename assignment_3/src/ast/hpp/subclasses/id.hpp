#pragma once

#include "../node.hpp"
#include "../../../types/types.hpp"

#include <iostream>

class IdNode : public ASTNode
{
public:
    /**
     * @brief Construct a new Id Node object
     * 
     * @param lineNum 
     * @param idName name of id
     * @param isArray true if id is an array
     */
    IdNode(unsigned int lineNum, std::string idName, bool isArray);
    /**
     * @brief Construct a new Id Node object
     * 
     * @param lineNum 
     * @param idName name of id
     * @param isArray true if id is an array
     * @param arraySize array size if it is an array
     */
    IdNode(unsigned int lineNum, std::string idName, bool isArray, int arraySize);
    void printNode() { std::cout << "Id: " << m_idName; }
    NodeType getNodeType() { return NodeType::IdNode; }
    std::string getIdName() { return m_idName; }

private:
    std::string m_idName;
    bool m_isArray;
    int m_arraySize;
};
