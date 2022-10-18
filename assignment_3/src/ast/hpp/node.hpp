#pragma once

#include "../../types/types.hpp"

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
     * @brief Destroy the ASTNode object
     * 
     */
    ~ASTNode();
    virtual NodeType getNodeType() = 0;

    /**
     * @brief prints node and its siblings + children recursively
     * 
     * @param indentLevel used for recursive printing
     * @param siblingLvl  used for recursive printing
     * @param childLvl    used for recursive printing
     */
    void print(unsigned int indentLevel=0, int siblingLvl=0, int childLvl=-1, bool printType=false);
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

    ASTNode* getParent() { return m_parent; }
    void setParent(ASTNode* parent) { m_parent = parent; }

    ASTNode* getAncestor(NodeType type);
    bool isAncestor(ASTNode* node);

    /**
     * @brief gets the ith sibling of the node. 0 is sibling to right
     * 
     * @param index 
     * @return ASTNode* child, nullptr if not found
     */
    ASTNode* getSibling(unsigned int index);

    bool getHasBeenAnalyzed() { return m_hasBeenAnalyzed; }
    void setHasBeenAnalyzed(bool isAnalyzed) { m_hasBeenAnalyzed = isAnalyzed; }

    /**
     * @brief gets a child from m_children at given index
     * 
     * @param index 
     * @return ASTNode* child node, nullptr if not found 
     */
    ASTNode* getChild(unsigned int index);

    /**
     * @brief gets the line num where node was first found.
     * 
     * @return unsigned int 
     */
    unsigned int getLineNum() { return m_lineNum; };

    unsigned int getNumChildren() { return m_children.size(); }

protected:
    /// @brief vector of child nodes
    std::vector<ASTNode*> m_children;
    /// @brief linked list of sibling nodes
    ASTNode* m_sibling;
    ASTNode* m_parent;

    bool m_hasBeenAnalyzed;
    /// @brief line number node first appeared on
    unsigned int m_lineNum;

    /**
     * @brief used for print() purposes. prints stuff specific to this node.
     * 
     */
    virtual void printNode() = 0;
    virtual void printTypedNode() { printNode(); };
};
