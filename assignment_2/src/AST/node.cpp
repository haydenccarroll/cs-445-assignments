#include "node.h"

#include <iostream>
Node::Node()
{
    m_sibling = nullptr;
}

Node::Node(unsigned int lineNum)
{
    m_sibling = nullptr;
    m_lineNum = lineNum;
}

Node::~Node()
{
}

void Node::print() const
{
    _print(0, 0);

}

void Node::_print(unsigned int numIndent, unsigned int numSibling) const {
    std::cout << _getStrOfNode() << "\n";

    numIndent++;
    for (int i=0; i < m_children.size(); i++)
    {
        Node* child = m_children[i];
        if (child != nullptr) {
            for (int j=0; j < numIndent; j++)
            {
                std::cout << ".   ";
            }

            std::cout << "Child: " << i << "  ";
            child->_print(numIndent, numSibling);

        }
    }
    numIndent--;

    numSibling++;
    if (m_sibling != nullptr)
    {
        for (int i=0; i < numIndent; i++) {
            std::cout << ".   ";
        }
        std::cout << "Sibling: " + numSibling << "  ";
        m_sibling->_print(numIndent, numSibling);
    }


}

// should be overridden in subclass
std::string Node::_getStrOfNode() const {
    return "[line: " + std::to_string(m_lineNum) + "]";
}

void Node::addChild(Node* child)
{
    m_children.push_back(child);
}

void Node::addSibling(Node* sibling)
{
    if (m_sibling == nullptr)
    {
        m_sibling = sibling;
        return;
    }

    m_sibling->addSibling(sibling);
}
