#include "node.hpp"

#include <iostream>


ASTNode::ASTNode(unsigned int lineNum)
{
    m_lineNum = lineNum;
    m_sibling = nullptr;
}

void ASTNode::printRoot()
{
    // not supposed to print itself, and it doesnt have a sibling.
    for (auto child : m_children)
    {
        child->print();
    }
}

void ASTNode::print(unsigned int indentLevel)
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

void ASTNode::addChild(ASTNode* child)
{
    m_children.push_back(child);
}

void ASTNode::addSibling(ASTNode* sibling)
{
    auto currNode = this;
    while (currNode->m_sibling != nullptr)
    {
        currNode = currNode->m_sibling;
    }

    currNode->m_sibling = sibling;

}