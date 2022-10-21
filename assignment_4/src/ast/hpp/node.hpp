#pragma once

#include "../../types/include.hpp"

#include <vector>
#include <string>

#define AST_PRINT_INDENT_STR ".   "

class ASTNode {
public:
    ASTNode(unsigned int lineNum);
    ~ASTNode();

    // getters
    virtual NodeType getNodeType() = 0;
    ASTNode* getChild(unsigned int index);
    ASTNode* getSibling(unsigned int index);
    ASTNode* getParent() { return m_parent; }
    ASTNode* getAncestor(NodeType type);
    bool getHasBeenAnalyzed() { return m_hasBeenAnalyzed; }
    unsigned int getNumChildren() { return m_children.size(); }
    unsigned int getLineNum() { return m_lineNum; };

    //setters
    void addChild(ASTNode* child);
    void addSibling(ASTNode* sibling);
    void setParent(ASTNode* parent) { m_parent = parent; }
    void setHasBeenAnalyzed(bool isAnalyzed) { m_hasBeenAnalyzed = isAnalyzed; }

    /**
     * @brief prints node and its siblings + children recursively
     * 
     * @param indentLevel used for recursive printing
     * @param siblingLvl  used for recursive printing
     * @param childLvl    used for recursive printing
     */
    void print(unsigned int indentLevel=0, int siblingLvl=0, int childLvl=-1, bool printType=false);

    bool isAncestor(ASTNode* node);
    bool hasAncestor(NodeType type);



protected:
    std::vector<ASTNode*> m_children;
    /// @brief linked list of sibling nodes
    ASTNode* m_sibling;
    ASTNode* m_parent;

    bool m_hasBeenAnalyzed;
    unsigned int m_lineNum;

    /**
     * @brief used for print() purposes. prints stuff specific to this node.
     * 
     */
    virtual std::string toString(bool printType=false) = 0;
};
