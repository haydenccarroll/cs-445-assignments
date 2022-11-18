#pragma once

#include "../../types/include.hpp"

#include <vector>
#include <string>

#define AST_PRINT_INDENT_STR ".   "

class ASTNode {
public:
    ASTNode(int lineNum);
    ~ASTNode();

    // getters
    virtual NodeType getNodeType() = 0;
    ASTNode* getChild(unsigned int index);
    ASTNode* getSibling(unsigned int index);
    ASTNode* getParent() { return m_parent; }
    ASTNode* getAncestor(NodeType type);
    bool getHasBeenAnalyzed() { return m_hasBeenAnalyzed; }
    unsigned int getNumChildren() { return m_children.size(); }
    unsigned int getNumSiblings();
    int getLineNum() { return m_lineNum; };
    int getMemSize() { return m_memSize; }
    MemReferenceType getMemRefType() { return m_memRefType; }

//setters
    void addChild(ASTNode* child);
    void addSibling(ASTNode* sibling);
    void setHasBeenAnalyzed(bool isAnalyzed) { m_hasBeenAnalyzed = isAnalyzed; }
    void setMemSize(int memSize);
    void setMemLoc(int memLoc);
    void setMemRefType(MemReferenceType memRefType) { m_memRefType = memRefType; }
    std::string getLineTag();
    std::string getMemTag();

    /**
     * @brief prints node and its siblings + children recursively
     * 
     * @param indentLevel used for recursive printing
     * @param siblingLvl  used for recursive printing
     * @param childLvl    used for recursive printing
     */
    void print(unsigned int indentLevel=0, int siblingLvl=0, int childLvl=-1, bool printType=false, bool printMem=false);

    bool isAncestor(ASTNode* node);
    bool hasAncestor(NodeType type);



protected:
    std::vector<ASTNode*> m_children;
    /// @brief linked list of sibling nodes
    ASTNode* m_sibling;
    ASTNode* m_parent;

    bool m_hasBeenAnalyzed;
    int m_lineNum;
    int m_memSize;
    int m_memLoc;
    MemReferenceType m_memRefType = MemReferenceType::None;

    /**
     * @brief used for print() purposes. prints stuff specific to this node.
     * 
     */
    virtual std::string toString(bool printType=false) = 0;
    void setParent(ASTNode* parent);

};
