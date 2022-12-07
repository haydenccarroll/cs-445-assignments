#pragma once

#include "../../ast/include.hpp"
#include "emitCode.hpp"

#include <string>
#include <map>

class CodeGen
{
public:
    CodeGen(ASTNode* tree, std::string fileName);
    ~CodeGen();
    void generate();
    void generateIO();
    void traverseGenerate(ASTNode* node);

    void genFuncStart(FunDeclNode* node);
    void genFuncEnd(FunDeclNode* node);

    void genVarDecl(VarDeclNode* node);

    void genCompoundStmtStart(CompoundStmtNode* node);
    void genCompoundStmtEnd(CompoundStmtNode* node);

    void genFor(ForNode* node);
    void genID(IdNode* node);
    void genReturn(ReturnNode* node);

    void genEndStuff();

private:
    std::string m_fileName;
    ASTNode* m_tree;
    std::map<std::string,int> m_funcsToLocs;
};
