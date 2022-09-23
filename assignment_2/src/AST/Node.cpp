#include "Node.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace AST
{
    Node::Node()
        : m_sibling(nullptr)
    {
    }

    Node::Node(unsigned lineNum)
        : m_sibling(nullptr),
          m_lineNum(lineNum)
    {
    }

    Node::~Node()
    {
        if (m_sibling != nullptr)
        {
            delete m_sibling;
        }

        for (auto &child : m_children)
        {
            delete child;
        }
    }

    void Node::print() const
    {
        static int siblingCount = 0;
        static int numIndents = 0;

        std::cout << toString() << std::endl;
        numIndents++;

        for (int i = 0; i < m_children.size(); i++)
        {
            Node *child = m_children[i];
            if (child != nullptr)
            {
                for (int j = 0; j < numIndents; j++)
                {
                    std::cout << ".   ";
                }

                std::cout << "Child: " + std::to_string(i) << "  ";
                int backup = siblingCount;
                siblingCount = 0;
                child->print();
                siblingCount = backup;
            }
        }
        numIndents--;

        siblingCount++;
        if (m_sibling != nullptr)
        {
            for (int i = 0; i < numIndents; i++)
            {
                std::cout << ".   ";
            }

            std::cout << "Sibling: " + std::to_string(siblingCount) << "  ";
            m_sibling->print();
        }
        siblingCount--;
    }

    void Node::addChild(Node *node)
    {
        m_children.push_back(node);
    }

    void Node::addSibling(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }

        if (m_sibling == nullptr)
        {
            m_sibling = node;
        }
        else
        {
            m_sibling->addSibling(node);
        }
    }

    std::string Node::toString() const
    {
        return lineTag();
    }

    std::string Node::lineTag() const
    {
        return " [line: " + std::to_string(m_lineNum) + "]";
    }

    unsigned &Node::lineNumber()
    {
        return m_lineNum;
    }
}