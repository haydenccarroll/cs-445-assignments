#pragma once

#include <vector>
#include <string>
#include <iostream>

#define AST_PRINT_INDENT_STR ".   "

class ASTNode {
public:
    ASTNode(unsigned int lineNum);
    void print(unsigned int indentLevel=0, int siblingLvl=0, int childLvl=-1);
    void addChild(ASTNode* child);
    void addSibling(ASTNode* sibling);
    virtual void printNode() { std::cout << "base node"; };
    unsigned int getLineNum() { return m_lineNum; };

protected:
    std::vector<ASTNode*> m_children;
    ASTNode* m_sibling;
    unsigned int m_lineNum;
};