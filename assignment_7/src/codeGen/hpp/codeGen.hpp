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

    void setFinalGOffset(int gOffset) { m_finalGOffset = gOffset; }

    void genFuncStart(FunDeclNode* node);
    void genFuncEnd(FunDeclNode* node);

    void genCompoundStmtStart(CompoundStmtNode* node);
    void genCompoundStmtEnd(CompoundStmtNode* node);

    void genFor(ForNode* node);
    void genID(IdNode* node);
    void genReturn(ReturnNode* node);
    void genVarDecl(VarDeclNode* node);

    void genConst(ConstNode* node);
    void genCall(CallNode* node);
    void loadParam(ExpNode* node);

    void genBinary(BinaryOpNode* node);
    void genAss(BinaryOpNode* node);


    void genEndStuff();

    void toffPush(int toff, bool print=true);
    void toffPop(bool print=true);
    void toffDec(bool print=true);
    void toffInc(bool print=true);

    bool isNodeTopMostExp(ASTNode* node);

private:
    std::string m_fileName;
    ASTNode* m_tree;
    std::map<std::string,int> m_funcsToLocs;
    std::vector<int> m_toffs;
    int m_finalGOffset;
};
