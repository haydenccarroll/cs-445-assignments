#include "Node.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace Tree
{
    Node::Node()
        : _sibling(nullptr)
    {
    }

    Node::Node(unsigned lineNum)
        : _sibling(nullptr),
          _lineNum(lineNum)
    {
    }

    Node::~Node()
    {
        if (_sibling != nullptr)
        {
            delete _sibling;
        }

        for (auto &child : _children)
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

        for (int i = 0; i < _children.size(); i++)
        {
            Node *child = _children[i];
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
        if (_sibling != nullptr)
        {
            for (int i = 0; i < numIndents; i++)
            {
                std::cout << ".   ";
            }

            std::cout << "Sibling: " + std::to_string(siblingCount) << "  ";
            _sibling->print();
        }
        siblingCount--;
    }

    void Node::addChild(Node *node)
    {
        _children.push_back(node);
    }

    void Node::addSibling(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }

        if (_sibling == nullptr)
        {
            _sibling = node;
        }
        else
        {
            _sibling->addSibling(node);
        }
    }

    std::string Node::toString() const
    {
        return lineTag();
    }

    std::string Node::lineTag() const
    {
        return " [line: " + std::to_string(_lineNum) + "]";
    }

    unsigned &Node::lineNumber()
    {
        return _lineNum;
    }
}