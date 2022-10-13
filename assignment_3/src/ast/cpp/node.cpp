#include "../hpp/node.hpp"

#include <iostream>
#include <sstream>
#include <cstdarg>

ASTNode::ASTNode(unsigned int lineNum)
{
    m_lineNum = lineNum;
    m_sibling = nullptr;
}

void ASTNode::print(unsigned int indentLevel, int siblingLvl, int childLvl)
{
    for (int i=0; i < indentLevel; i++)
    {
        std::cout << AST_PRINT_INDENT_STR;
    }
        // if it is a sibling
    if (siblingLvl != 0)
    {
        std::cout << "Sibling: " << siblingLvl << "  ";
    } else if (childLvl != -1) // if it is a child
    {
        std::cout << "Child: " << childLvl << "  ";
    }
    printNode(); // print contents of this node
    std::cout << " [line: " << m_lineNum << "]\n";
    
    // print children
    for (unsigned int i=0; i < m_children.size(); i++)
    {
        if (m_children[i] != nullptr)
        {
            m_children[i]->print(indentLevel + 1, 0, i);
        }
    }

    // print siblings
    if (m_sibling != nullptr)
    {
        m_sibling->print(indentLevel, siblingLvl + 1);
    }
}

void ASTNode::addChild(ASTNode* child)
{
    m_children.push_back(child);
}

void ASTNode::addSibling(ASTNode* sibling)
{
    ASTNode* currNode = this;
    while (currNode->m_sibling != nullptr)
    {
        currNode = currNode->m_sibling;
    }

    currNode->m_sibling = sibling;
}
