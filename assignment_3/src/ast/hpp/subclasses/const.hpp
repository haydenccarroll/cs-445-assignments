#pragma once

#include "../node.hpp"
#include "../../../types/types.hpp"

class ConstNode : public ASTNode
{
public:
    /**
     * @brief Construct a new Const Node object
     * 
     * @param lineNum 
     * @param type type of const
     * @param value value of respective data type
     */
    ConstNode(unsigned int lineNum, ConstType type, int value);
    ConstNode(unsigned int lineNum, ConstType type, char value);
    ConstNode(unsigned int lineNum, ConstType type, std::string value);
    ConstNode(unsigned int lineNum, ConstType type, bool value);

    NodeType getNodeType() { return NodeType::ConstNode; }

    void printNode();



private:
    const ConstType m_constType;

    const int m_intValue;
    const char m_charValue;
    const std::string m_stringValue;
    const bool m_boolValue;
};
