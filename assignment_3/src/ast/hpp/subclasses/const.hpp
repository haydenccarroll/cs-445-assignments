#pragma once

#include "exp.hpp"
#include "../../../types/types.hpp"

class ConstNode : public ExpNode
{
public:
    /**
     * @brief Construct a new Const Node object
     * 
     * @param lineNum 
     * @param value value of respective data type
     */
    ConstNode(unsigned int lineNum, int value);
    ConstNode(unsigned int lineNum, char value);
    ConstNode(unsigned int lineNum, std::string value);
    ConstNode(unsigned int lineNum, bool value);

    NodeType getNodeType() { return NodeType::ConstNode; }

    void printNode();
    virtual void printTypedNode();



private:
    const ConstType m_constType;

    const int m_intValue;
    const char m_charValue;
    const std::string m_stringValue;
    const bool m_boolValue;
};
