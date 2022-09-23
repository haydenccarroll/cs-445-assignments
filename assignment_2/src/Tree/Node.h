#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

namespace Tree
{
    /// Abstract Base Node class
    class Node
    {
    public:
        Node();
        // lineNum - Line number node is on
        Node(unsigned lineNum);
        virtual ~Node();
        // prints the tree
        void print() const;
        // returns the string version of the node for printing purposes
        virtual std::string toString() const;
        // Adds a child node
        void addChild(Node *);
        // Adds a sibling node
        void addSibling(Node *);
        // Gets line number reference
        unsigned &lineNumber();

    private:
    protected:
        std::vector<Node *> _children;
        Node *_sibling = nullptr;
        unsigned _lineNum;

        // returns the line number text. This is used in the toString() function. 
        std::string lineTag() const;
    };
}

#endif