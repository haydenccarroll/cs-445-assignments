#pragma once

#include <vector>

#define AST_PRINT_INDENT_STR ".   "

/**
 * @brief abstract parent node for the abstract syntax tree
 * 
 */
class ASTNode {
public:
    /**
     * @brief Construct a new ASTNode object
     * 
     * @param lineNum line num node found on
     */
    ASTNode(unsigned int lineNum);

    /**
     * @brief prints node and its siblings + children recursively
     * 
     * @param indentLevel used for recursive printing
     * @param siblingLvl  used for recursive printing
     * @param childLvl    used for recursive printing
     */
    void print(unsigned int indentLevel=0, int siblingLvl=0, int childLvl=-1);

    /**
     * @brief adds a child to m_children
     * 
     * @param child child to add
     */
    void addChild(ASTNode* child);

    /**
     * @brief adds a sibling to m_sibling linked list
     * 
     * @param sibling sibling to add
     */
    void addSibling(ASTNode* sibling);

    /**
     * @brief gets the line num where node was first found.
     * 
     * @return unsigned int 
     */
    unsigned int getLineNum() { return m_lineNum; };

protected:
    /// @brief vector of child nodes
    std::vector<ASTNode*> m_children;
    /// @brief linked list of sibling nodes
    ASTNode* m_sibling;
    /// @brief line number node first appeared on
    unsigned int m_lineNum;

    /**
     * @brief used for print() purposes. prints stuff specific to this node.
     * 
     */
    virtual void printNode() = 0;
};
