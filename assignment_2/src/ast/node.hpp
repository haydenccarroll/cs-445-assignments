#pragma once

#include <vector>
#include <string>

#define AST_PRINT_INDENT_STR ".   "

class ASTNode {
public:
    ASTNode(unsigned int lineNum);
    void print(unsigned int indentLevel = 0);
    void printRoot();
    void addChild(ASTNode* child);
    void addSibling(ASTNode* sibling);

private:
    std::vector<ASTNode*> m_children;
    ASTNode* m_sibling;
    std::string m_name;
    unsigned int m_lineNum;
};