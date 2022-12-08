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

    void genBinary(BinaryOpNode* node);
    void genGenericBinOp(BinaryOpNode* node);
    void genAss(BinaryOpNode* node);
    void genAddAss(BinaryOpNode* node);
    void genSubAss(BinaryOpNode* node);
    void genDivAss(BinaryOpNode* node);
    void genMulAss(BinaryOpNode* node);
    void genOr(BinaryOpNode* node);
    void genAnd(BinaryOpNode* node);
    void genAdd(BinaryOpNode* node);
    void genSub(BinaryOpNode* node);
    void genMul(BinaryOpNode* node);
    void genDiv(BinaryOpNode* node);
    void genMod(BinaryOpNode* node);
    void genTEQ(BinaryOpNode* node);
    void genTGT(BinaryOpNode* node);
    void genTLT(BinaryOpNode* node);
    void genTNEQ(BinaryOpNode* node);

    void genUnary(UnaryOpNode* node);
    void genInc(UnaryOpNode* node);
    void genDec(UnaryOpNode* node);
    void genNot(UnaryOpNode* node);
    void genRand(UnaryOpNode* node);
    void genChsign(UnaryOpNode* node);



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
