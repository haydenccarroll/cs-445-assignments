#include "node.hpp"

#include <iostream>


TreeNode::TreeNode(unsigned int lineNum)
{
    m_lineNum = lineNum;
    m_sibling = nullptr;
}

void TreeNode::printRoot()
{
    // not supposed to print itself, and it doesnt have a sibling.
    for (auto child : m_children)
    {
        child->print();
    }
}

void TreeNode::print(unsigned int indentLevel)
{
    std::string localIndentLevel = "";
    for (int i=0; i < indentLevel; i++)
    {
        localIndentLevel += AST_PRINT_INDENT_STR;
    }
    std::cout << localIndentLevel << "HERE WE HAVE A NODE\n";
    
    // print children
    for (auto child : m_children)
    {
        child->print(indentLevel + 1);
    }

    // print siblings
    if (m_sibling != nullptr)
    {
        m_sibling->print(indentLevel);
    }
}

void TreeNode::addChild(TreeNode* child)
{
    m_children.push_back(child);
}