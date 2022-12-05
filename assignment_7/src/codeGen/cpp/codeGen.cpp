#include "../hpp/codeGen.hpp"
#include "../../error/include.hpp"

#include <filesystem>
FILE* code = nullptr;

CodeGen::CodeGen(ASTNode* tree, std::string fileName)
{
    m_tree = tree;
    m_fileName = fileName;

    auto file = fopen(m_fileName.c_str(), "w");
    if (file == nullptr)
    {
        Error::critical(0, "Could not open file for codegen.");
    }

    code = file; // for usage with heckendorns emitCode.cpp
}

CodeGen::~CodeGen()
{
    fclose(code);
}

void CodeGen::generate()
{
    std::filesystem::path oldFileName = m_fileName;
    oldFileName = oldFileName.replace_extension("c-");
    std::stringstream ss;
    ss << "File compiled:  " << oldFileName.filename().generic_string();

    emitComment("C- compiler version F22");
    emitComment(ss.str());
    generateIO();

    traverseGenerate(m_tree);



}

void CodeGen::generateIO()
{
    std::string comment = R"""(* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION input
  1:     ST  3,-1(1)	Store return address 
  2:     IN  2,2,2	Grab int input 
  3:     LD  3,-1(1)	Load return address 
  4:     LD  1,0(1)	Adjust fp 
  5:    JMP  7,0(3)	Return 
* END FUNCTION input
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION output
  6:     ST  3,-1(1)	Store return address 
  7:     LD  3,-2(1)	Load parameter 
  8:    OUT  3,3,3	Output integer 
  9:     LD  3,-1(1)	Load return address 
 10:     LD  1,0(1)	Adjust fp 
 11:    JMP  7,0(3)	Return 
* END FUNCTION output
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputb
 12:     ST  3,-1(1)	Store return address 
 13:    INB  2,2,2	Grab bool input 
 14:     LD  3,-1(1)	Load return address 
 15:     LD  1,0(1)	Adjust fp 
 16:    JMP  7,0(3)	Return 
* END FUNCTION inputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputb
 17:     ST  3,-1(1)	Store return address 
 18:     LD  3,-2(1)	Load parameter 
 19:   OUTB  3,3,3	Output bool 
 20:     LD  3,-1(1)	Load return address 
 21:     LD  1,0(1)	Adjust fp 
 22:    JMP  7,0(3)	Return 
* END FUNCTION outputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputc
 23:     ST  3,-1(1)	Store return address 
 24:    INC  2,2,2	Grab char input 
 25:     LD  3,-1(1)	Load return address 
 26:     LD  1,0(1)	Adjust fp 
 27:    JMP  7,0(3)	Return 
* END FUNCTION inputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputc
 28:     ST  3,-1(1)	Store return address 
 29:     LD  3,-2(1)	Load parameter 
 30:   OUTC  3,3,3	Output char 
 31:     LD  3,-1(1)	Load return address 
 32:     LD  1,0(1)	Adjust fp 
 33:    JMP  7,0(3)	Return 
* END FUNCTION outputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outnl
 34:     ST  3,-1(1)	Store return address 
 35:  OUTNL  3,3,3	Output a newline 
 36:     LD  3,-1(1)	Load return address 
 37:     LD  1,0(1)	Adjust fp 
 38:    JMP  7,0(3)	Return 
* END FUNCTION outnl
)""";
    // generate io stuff by using heckendorns code
    emitRawStr(comment);
}

void CodeGen::traverseGenerate(ASTNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    std::stringstream ss;

    switch(node->getNodeType())
    {
    case NodeType::FunDeclNode:
        genFunc(cast<FunDeclNode*>(node));
        break;
    default:
        break;
    }

    for (unsigned int i=0; i < node->getNumChildren(); i++)
    {
        traverseGenerate(node->getChild(i));
    }

    switch (node->getNodeType())
    {
    case NodeType::FunDeclNode:
        ss << "END FUNCTION " << cast<FunDeclNode*>(node)->getName();
        emitComment(ss.str());
        break;
    }

    traverseGenerate(node->getSibling(0));
}

void CodeGen::genFunc(FunDeclNode* node)
{
    if (node == nullptr)
    {
        return;
    }
    std::stringstream ss;
    emitComment("");
    emitComment("** ** ** ** ** ** ** ** ** ** ** **");
    ss << "FUNCTION " << node->getName();
    emitComment(ss.str());
    ss.clear();

}

void CodeGen::genVarDecl(VarDeclNode* node)
{
}

void CodeGen::genID(IdNode* node)
{

}

void CodeGen::genCompoundStmt(CompoundStmtNode* node)
{

}

void CodeGen::genFor(ForNode* node)
{

}

