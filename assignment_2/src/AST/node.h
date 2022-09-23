#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

// abstract base node class
class Node
{
public:
    Node();
    Node(unsigned int lineNum);
    virtual ~Node() = 0;

    void print() const;
    void addChild(Node* childNode);
    void addSibling(Node* siblingNode);
    void print() const;



protected:
    std::vector<Node*> m_children;
    Node* m_sibling = nullptr;
    unsigned int m_lineNum;


private:
    void _print(unsigned int numIndent, unsigned int numSibling) const;
    std::string Node::_getStrOfNode() const;


};

#endif
