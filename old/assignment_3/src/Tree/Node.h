#pragma once

#include "Types.h"

#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace Tree {

// string for indentations
static const std::string s_indentString = ".   ";

// base node class
class Node {
  public:
    Node();
    // param lineNum  - Line number the node appears on
    Node(unsigned lineNum);
    // param lineNum - Line number the node appears on
    // param nodeType - Type of node
    Node(unsigned lineNum, NodeType nodeType);
    // should release all dynamic memory associated with Node.
    virtual ~Node();

    // Adds child node
    void addChild(Node *node);
    // Sets the child at given index
    // If there is already a node at the index, it is deleted
    // param index - Child index
    // param node - node to replace put at index
    void setChild(int index, Node *node);
    // Adds a sibling node
    void addSibling(Node *node);
    // returns address of the sibling, nullptr if none
    Node *sibling() const;
    // returns address of the parent, nullptr if none
    Node *parent() const;
    // returns vector of children nodes
    const std::vector<Node *> &children() const;

    // Recursively prints the tree
    void print(bool debugging = false) const;
    // returns true if the node has a sibling
    bool hasSibling() const;
    // Gets current line number
    unsigned int lineNumber() const;
    // returns Type of node
    NodeType nodeType() const;

    // Get a string of node for printing purposes. (debugging=false by default)
    virtual std::string toString(bool debugging = false) const;

    // Functions to determine what "type" of node the node is.
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

    // param t - Node type (enum)
    // returns true if the node has a node of type t in its parent list
    // this is useful templated because there are many different type enums (such as StmtType, DeclType...)
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

    // Casts the address of the Node to some type
    // returns The casted address
    // this is useful for when dealing with different types of nodes.
    template <typename T> T cast() const { return (T)this; }

    // param t - Node type (enum)
    // returns the  of the closest ancestor in the parent list that is the type T
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

  private:
  protected:
    NodeType m_nodeType;
    std::vector<Node *> m_children;
    Node *m_sibling = nullptr;
    Node *m_parent = nullptr;
    unsigned m_lineNum;

    // returns The line tag at the end of a node's print, (just line number)
    std::string lineTag() const;
    // returns The type string to be printed if type debuggging is on.
    virtual std::string typeTag() const;
    // returns child at given index
    Node *getChild(int index) const;
};
}
