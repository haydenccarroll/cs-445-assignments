#pragma once

#include <vector>
#include <string>

#define AST_PRINT_INDENT_STR ".   "

class TreeNode {
public:
    TreeNode(unsigned int lineNum);
    void print(unsigned int indentLevel = 0);
    void printRoot();
    void addChild(TreeNode* child);

private:
    std::vector<TreeNode*> m_children;
    TreeNode* m_sibling;
    std::string m_name;
    unsigned int m_lineNum;
};