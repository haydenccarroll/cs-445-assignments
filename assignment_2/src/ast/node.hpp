#pragma once

#include <vector>
#include <string>

#define AST_PRINT_INDENT_STR ".   "

class ASTNode {
public:
    ASTNode(unsigned int lineNum);
    void print(unsigned int indentLevel=0, int siblingLvl=0, int childLvl=-1);
    void addChild(ASTNode* child);
    void addSibling(ASTNode* sibling);
    void printNode();
    unsigned int getLineNum() { return m_lineNum; };

private:
    std::vector<ASTNode*> m_children;
    ASTNode* m_sibling;
    std::string m_name;
    unsigned int m_lineNum;
};