#include "../hpp/node.hpp"

#include <iostream>
#include <sstream>

#include "../../error/include.hpp"

ASTNode::ASTNode(int lineNum)
{
    m_lineNum = lineNum;
    m_sibling = nullptr;
    m_hasBeenAnalyzed = false;
    m_memSize = 0;
}

ASTNode::~ASTNode()
{
    for (int i=0; i < m_children.size(); i++)
    {
        delete m_children[i];
        m_children[i] = nullptr;
    }
    delete m_sibling;
    m_sibling = nullptr;
}

unsigned int ASTNode::getNumSiblings()
{
    if (m_sibling == nullptr)
    {
        return 0;
    }

    return 1 + m_sibling->getNumSiblings();
}


void ASTNode::print(unsigned int indentLevel, int siblingLvl, int childLvl, bool printType, bool printMem)
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
    std::cout << this->toString(printType);
    if (printMem && m_memSize != 0)
    {
        std::cout << " " << getMemTag();
    }
    std::cout << " " << getLineTag() << "\n";

    // print children
    for (unsigned int i=0; i < m_children.size(); i++)
    {
        if (m_children[i] != nullptr)
        {
            m_children[i]->print(indentLevel + 1, 0, i, printType, printMem);
        }
    }

    // print siblings
    if (m_sibling != nullptr)
    {
        m_sibling->print(indentLevel, siblingLvl + 1, -1, printType, printMem);
    }
}

void ASTNode::setMemSize(int memSize)
{
    m_memSize = memSize;
}

void ASTNode::setMemLoc(int memLoc)
{
    m_memLoc = memLoc;
}

std::string ASTNode::getLineTag()
{
    std::stringstream ss;
    ss << "[line: " << m_lineNum << "]";
    return ss.str();
}

std::string ASTNode::getMemTag()
{
    if (m_memSize == 0)
    {
        return "";
    }

    std::stringstream ss;
    ss << "[mem: ";
    switch (m_memRefType)
    {
    case MemReferenceType::Global:
        ss << "Global";
        break;
    case MemReferenceType::Local:
        ss << "Local";
        break;
    case MemReferenceType::Parameter:
        ss << "Parameter";
        break;
    case MemReferenceType::Static:
        ss << "LocalStatic";
        break;
    case MemReferenceType::None:
        ss << "None";
        break;
    }

    ss << " loc: " << m_memLoc << " size: " << m_memSize << "]";

    return ss.str();
}

ASTNode* ASTNode::getAncestor(NodeType type)
{
    if (m_parent == nullptr) { return nullptr; }

    if (m_parent->getNodeType() == type) { return m_parent; }

    return m_parent->getAncestor(type);
}

bool ASTNode::hasAncestor(NodeType type)
{
    return (getAncestor(type) != nullptr);
}


bool ASTNode::isAncestor(ASTNode* node)
{
    if (this == node) { return true; }

    if (m_parent == nullptr) { return false; }

    return m_parent->isAncestor(node);
}

void ASTNode::addChild(ASTNode* child)
{
    if (child != nullptr)
    {
        child->m_parent = this;
        child->setParent(this);
    }
    m_children.push_back(child);
}

void ASTNode::addSibling(ASTNode* sibling)
{
    if (sibling == nullptr) { return; }

    sibling->setParent(this);
    ASTNode* currNode = this;
    while (currNode->m_sibling != nullptr)
    {
        currNode = currNode->m_sibling;

    }

    currNode->m_sibling = sibling;
}

void ASTNode::setParent(ASTNode* parent)
{
    if (parent == nullptr)
    {
        return;
    }

    m_parent = parent;
    if (m_sibling != nullptr)
    {
        m_sibling->setParent(parent);
    }
}

ASTNode* ASTNode::getChild(unsigned int index)
{
    if (index >= m_children.size()) { return nullptr; }

    return m_children[index];
}

ASTNode* ASTNode::getSibling(unsigned int index)
{
    if (m_sibling == nullptr) { return nullptr; }

    if (index == 0) {
        return m_sibling;
    }

    return getSibling(index - 1);
}
