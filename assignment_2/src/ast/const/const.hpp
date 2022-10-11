#pragma once

#include "../node.hpp"
#include "../../types.hpp"

class ConstNode : public ASTNode
{
public:
    ConstNode(unsigned int lineNum, ConstType type, int value);
    ConstNode(unsigned int lineNum, ConstType type, char value);
    ConstNode(unsigned int lineNum, ConstType type, std::string value);
    ConstNode(unsigned int lineNum, ConstType type, bool value);



private:
    const ConstType m_constType;

    const int m_intValue;
    const char m_charValue;
    const std::string m_stringValue;
    const bool m_boolValue;
};
