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
    for (int i = 0; i < m_children.size(); i++)
    {
        std::cout << "siez:" << m_children.size() << std::endl;
        if (m_children[i] != nullptr)
        {
            m_children[i]->print();
        }
    }
}

void ASTNode::print(unsigned int indentLevel)
{
    std::string localIndentLevel = "";
    for (int i=0; i < indentLevel; i++)
    {
        // localIndentLevel += AST_PRINT_INDENT_STR;
    }
    std::cout << localIndentLevel << "HERE WE HAVE A NODE at line:" << m_lineNum << std::endl;
    
    // print children
    for (unsigned int i=0; i < m_children.size(); i++)
    {
        if (m_children[i] != nullptr)
        {
            m_children[i]->print(indentLevel + 1);
        }
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