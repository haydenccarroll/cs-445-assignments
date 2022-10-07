#include "Node.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <variant>
#include <vector>
#include <stdexcept>


namespace AST {
#pragma region Constructors / Destructors

Node::Node() : m_sibling(nullptr) {}

Node::Node(unsigned linenum) : m_sibling(nullptr), m_linenum(linenum) {}

Node::Node(unsigned linenum, NodeType nodeType)
    : m_linenum(linenum), m_nodeType(nodeType) {}

Node::~Node() {
    if (m_sibling != nullptr) {
        delete m_sibling;
    }

    for (auto &child : m_children) {
        if (child != nullptr) {
            delete child;
        }
    }
}

#pragma endregion

#pragma region Tree traversal and construction

void Node::addChild(Node *node) {
    m_children.push_back(node);
    if (node != nullptr) {
        node->m_parent = this;

        Node *sibling = node->sibling();
        while (sibling != nullptr) {
            sibling->m_parent = this;
            sibling = sibling->sibling();
        }
    }
}

void Node::setChild(int index, Node *node) {
    if (m_children.size() <= index) {
        throw std::runtime_error("Cannot set child, index out of bounds.");
    } else {
        if (m_children[index] != nullptr &&
            !(m_children[index] == this || m_children[index] == node)) {
            delete m_children[index];
        }

        m_children[index] = node;
        node->m_parent = this;
        Node *sibling = node->sibling();
        while (sibling != nullptr) {
            sibling->m_parent = this;
            sibling = sibling->sibling();
        }
    }
}

void Node::addSibling(Node *node) {
    if (node == nullptr) {
        return;
    }

    if (m_sibling == nullptr) {
        m_sibling = node;
        m_sibling->m_parent = m_parent;
    } else {
        m_sibling->addSibling(node);
    }
}

Node *Node::sibling() const { return m_sibling; }

Node *Node::parent() const { return m_parent; }

const std::vector<Node *> &Node::children() const { return m_children; }

#pragma endregion

#pragma region Info

void Node::print(bool debugging) const {
    static int siblingCount = 0;
    static int numIndents = 0;

    std::cout << toString(debugging) << std::endl;
    numIndents++;

    for (int i = 0; i < m_children.size(); i++) {
        Node *child = m_children[i];
        if (child != nullptr) {
            for (int j = 0; j < numIndents; j++) {
                std::cout << s_indentString;
            }

            std::cout << "Child: " + std::to_string(i) << "  ";
            int backup = siblingCount;
            siblingCount = 0;
            child->print(debugging);
            siblingCount = backup;
        }
    }
    numIndents--;

    siblingCount++;
    if (m_sibling != nullptr) {
        for (int i = 0; i < numIndents; i++) {
            std::cout << s_indentString;
        }

        std::cout << "Sibling: " + std::to_string(siblingCount) << "  ";
        m_sibling->print(debugging);
    }
    siblingCount--;
}

bool Node::hasSibling() const { return m_sibling != nullptr; }

unsigned &Node::lineNumber() { return m_linenum; }

const NodeType &Node::nodeType() const { return m_nodeType; }

#pragma endregion

#pragma region Virtual functions

std::string Node::toString(bool debugging) const { return lineTag(); }

bool Node::is(NodeType t) const { return this != nullptr && nodeType() == t; }
bool Node::is(StmtType t) const { return false; }
bool Node::is(DeclType t) const { return false; }
bool Node::is(ExpType t) const { return false; }
bool Node::is(OpType t) const { return false; }
bool Node::is(BoolOpType t) const { return false; }
bool Node::is(UnaryOpType t) const { return false; }
bool Node::is(UnaryAsgnType t) const { return false; }
bool Node::is(BinaryOpType t) const { return false; }
bool Node::is(AsgnType t) const { return false; }

#pragma endregion

#pragma region Private functions

std::string Node::lineTag() const {
    return " [line: " + std::to_string(m_linenum) + "]";
}

std::string Node::typeTag() const { return ""; }

Node *Node::getChild(int index) const {
    if (m_children.size() <= index) {
        return nullptr;
    } else {
        return m_children[index];
    }
}

#pragma endregion
} // namespace AST