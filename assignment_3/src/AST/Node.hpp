#pragma once

#include "Types.hpp"

#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace AST {

/// String to print for indentations
static const std::string s_indentString = ".   ";

/// Base AST Node class
class Node {
  public:
#pragma region Constructors / Destructors
    /// Default constructor
    Node();
    /// @param linenum Line number the node appears on
    Node(unsigned linenum);
    /// @param linenum Line number the node appears on
    /// @param nodeType Type of node
    Node(unsigned linenum, NodeType nodeType);
    /// Virtual destructor, release all dynamically allocated memory
    virtual ~Node();
#pragma endregion

#pragma region Tree traversal and construction
    /// Adds a child node
    void addChild(Node *node);
    /// Sets the child at the index to the node
    /// If there is already a node at the index, it is freed
    /// @param index Child index
    /// @param node Node to set the child at the index
    void setChild(int index, Node *node);
    /// Adds a sibling node
    void addSibling(Node *node);
    /// @returns The address of the sibling, nullptr if none
    Node *sibling() const;
    /// @returns The address of the parent, nullptr if none
    Node *parent() const;
    /// @returns The vector of children nodes
    const std::vector<Node *> &children() const;
#pragma endregion

#pragma region Info
    /// Recursively prints the tree
    void print(bool debugging = false) const;
    /// @returns True if the node has a sibling
    bool hasSibling() const;
    /// Gets reference to the line number member
    unsigned &lineNumber();
    /// @returns Type of node
    const NodeType &nodeType() const;
#pragma endregion

#pragma region Virtual functions
    /// Get a string representation of the node
    virtual std::string toString(bool debugging = false) const;

    /// Functions to determine node type from base Node pointer
    virtual bool is(NodeType) const;
    virtual bool is(StmtType) const;
    virtual bool is(DeclType) const;
    virtual bool is(ExpType) const;
    virtual bool is(OpType) const;
    virtual bool is(BoolOpType) const;
    virtual bool is(UnaryOpType) const;
    virtual bool is(UnaryAsgnType) const;
    virtual bool is(BinaryOpType) const;
    virtual bool is(AsgnType) const;
#pragma endregion

#pragma region Templated functions

    /// @param t Node type (enum)
    /// @returns True if the node has an ancestor of type t
    template <typename T> bool hasAncestor(T t) const {
        Node *walker = parent();
        while (walker != nullptr) {
            if (walker->is(t)) {
                return true;
            }

            walker = walker->parent();
        }
        return false;
    }

    /// Casts the address of the Node to some type
    /// @returns The casted address
    template <typename T> T cast() const { return (T)this; }

    /// @param t Node type (enum)
    /// @returns Address of the closest ancestor that is the provided type
    template <typename T> Node *getClosestAncestor(T t) const {
        Node *walker = parent();
        while (walker != nullptr) {
            if (walker->is(t)) {
                return walker;
            }
            walker = walker->parent();
        }

        return nullptr;
    }
#pragma endregion

  private:
  protected:
    NodeType m_nodeType;
    std::vector<Node *> m_children;
    Node *m_sibling = nullptr;
    Node *m_parent = nullptr;
    unsigned m_linenum;

    /// @returns The line tag at the end of every node's print statement
    std::string lineTag() const;
    /// @returns The type tag to print for type debugging
    virtual std::string typeTag() const;
    /// @param index Returns the child at the specified index, nullptr if none
    /// exists
    Node *getChild(int index) const;
};
} // namespace AST