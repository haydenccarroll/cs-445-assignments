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

    genEndStuff();



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
    emitNewLoc(39);

    m_funcsToLocs["input"] = 1;
    m_funcsToLocs["output"] = 6;
    m_funcsToLocs["inputb"] = 12;
    m_funcsToLocs["outputb"] = 17;
    m_funcsToLocs["inputc"] = 23;
    m_funcsToLocs["outputc"] = 28;
    m_funcsToLocs["outnl"] = 34;
}

void CodeGen::genEndStuff()
{
    emitComment("INIT");
    emitRM("LDA", 1, 0, 0, "set first frame at end of globals"); // should use goffset
    emitRM("ST", 1, 0, 1, "store old fp (point to self)");
    emitComment("INIT GLOBALS AND STATICS");
    // init globals and statics here
    emitComment("END INIT GLOBALS AND STATICS");
    emitRM("LDA", 3, 1, 7, "Return address in ac");

    int offsetFromMain = m_funcsToLocs.at("main") - emitWhereAmI() - 1;
    emitRM("JMP", 7, offsetFromMain, 7, "Jump to main");
    emitRO("HALT", 0, 0, 0, "DONE!");
    emitComment("END INIT");
}

void CodeGen::traverseGenerate(ASTNode* node)
{
    if (node == nullptr || node->getHasBeenCodeGenned())
    {
        return;
    }
    
    node->setHasBeenCodegenned(true);
    if (isNodeTopMostExp(node))
    {
        emitComment("EXPRESSION");
    }
    std::stringstream ss;

    switch(node->getNodeType())
    {
    case NodeType::FunDeclNode:
        genFuncStart(cast<FunDeclNode*>(node));
        break;
    case NodeType::CompoundStmtNode:
        genCompoundStmtStart(cast<CompoundStmtNode*>(node));
        break;
    case NodeType::ReturnNode:
        genReturn(cast<ReturnNode*>(node));
        break;
    case NodeType::CallNode:
        genCall(cast<CallNode*>(node));
        break;
    case NodeType::ConstNode:
        genConst(cast<ConstNode*>(node));
        break;
    }

    for (unsigned int i=0; i < node->getNumChildren(); i++)
    {
        traverseGenerate(node->getChild(i));
    }

    switch (node->getNodeType())
    {
    case NodeType::FunDeclNode:
        genFuncEnd(cast<FunDeclNode*>(node));
        break;
    case NodeType::CompoundStmtNode:
        genCompoundStmtEnd(cast<CompoundStmtNode*>(node));
        break;
    }

    traverseGenerate(node->getSibling(0));
}

void CodeGen::genFuncStart(FunDeclNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    m_funcsToLocs[node->getName()] = emitWhereAmI();

    // boilerplate for every function beginning
    std::stringstream ss;
    emitComment("");
    emitComment("** ** ** ** ** ** ** ** ** ** ** **");
    ss << "FUNCTION " << node->getName();
    emitComment(ss.str());
    ss.str("");
    toffPush(-2);
    emitRM("ST", 3, -1, 1, "Store return address");
}

void CodeGen::genFuncEnd(FunDeclNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    // boilerplate for every function end
    emitComment("Add standard closing in case there is no return statement");
    emitRM("LDC", 2, 0, 6, "Set return value to 0");
    emitRM("LD", 3, -1, 1, "Load return address");
    emitRM("LD", 1, 0, 1, "Adjust fp");
    emitRM("JMP", 7, 0, 3, "Return");
    std::stringstream ss;
    ss << "END FUNCTION " << node->getName();
    emitComment(ss.str());

    if (node->getName() == "main")
    {
        int currLoc = emitWhereAmI();
        emitNewLoc(0);
        emitRM("JMP", 7, currLoc - 1, 7, "Jump to init [backpatch]");
        emitNewLoc(currLoc);
    }
}

void CodeGen::genID(IdNode* node)
{

}

void CodeGen::genCompoundStmtStart(CompoundStmtNode* node)
{
    if (node == nullptr)
    {
        return;
    }
    emitComment("COMPOUND");
    
    auto child = tryCast<VarDeclNode*>(node->getChild(0));
    int size = 0;
    while (child != nullptr)
    {
        size += child->getMemSize();
        child = tryCast<VarDeclNode*>(child->getSibling(0));
    }
    toffPush(m_toffs.back() - size);
    emitComment("Compound Body");
}

void CodeGen::genCompoundStmtEnd(CompoundStmtNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    toffPop();
    emitComment("END COMPOUND");
}

void CodeGen::genReturn(ReturnNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    emitComment("RETURN");
    emitRM("LD", 3, -1, 1, "Load return address");
    emitRM("LD", 1, 0, 1, "Adjust fp");
    emitRM("JMP", 7, 0, 3, "Return"); // -9 isnt always constant. idk what it is.
}

void CodeGen::genCall(CallNode* node)
{
    if (node == nullptr)
    {
        return;
    }
    std::stringstream ss;
    int oldToff = m_toffs.back(); // needed because print order is messed up
    toffPush(m_toffs.back(), false);
    ss << "CALL " << node->getFunName();
    emitComment(ss.str());
    ss.str("");

    ss << "Store fp in ghost frame for " << node->getFunName();
    emitRM("ST", 1, m_toffs.back(), 1, ss.str(), false);
    ss.str("");

    toffDec();
    toffDec();


    for (int i=0; i < node->getNumChildren(); i++)
    {
        if (node->getChild(i) == nullptr) // skip null childs
        {
            continue;
        }
        ss << "Param " << i+1;
        emitComment(ss.str());
        ss.str("");

        traverseGenerate(node->getChild(i));

        emitRM("ST", 3, m_toffs.back(), 1, "Push parameter");
        toffDec();
    }

    ss << "Param end " << node->getFunName();
    emitComment(ss.str());
    ss.str("");

    emitRM("LDA", 1, oldToff, 1, "Ghost frame becomes new active frame");
    emitRM("LDA", 3, 1, 7, "Return address in ac");

    ss << "CALL " << node->getFunName();
    int offsetFromFunc = m_funcsToLocs.at(node->getFunName()) - emitWhereAmI() - 1;
    emitRM("JMP", 7, offsetFromFunc, 7, ss.str(), false);
    ss.str("");

    emitRM("LDA", 3, 0, 2, "Save the result in ac");

    ss << "Call end " << node->getFunName();
    emitComment(ss.str());
    ss.str("");

    toffPop();
}

void CodeGen::genVarDecl(VarDeclNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    // dont do anything, let other functions handle this.
}

// void CodeGen::loadParam(ExpNode* node)
// {
//     if (node == nullptr)
//     {
//         return;
//     }

//     bool isVar = (node->getNodeType() == NodeType::IdNode);
//     bool isArr = false;
//     IdNode* idNode = tryCast<IdNode*>(node);
//     if (node->getNodeType() == NodeType::BinaryOpNode)
//     {
//         auto binNode = cast<BinaryOpNode*>(node);
//         switch (binNode->getOperatorType())
//         {
//         case BinaryOpType::MulAss:
//         case BinaryOpType::DivAss:
//         case BinaryOpType::SubAss:
//         case BinaryOpType::AddAss:
//         case BinaryOpType::Ass:
//             isVar = true;
//             idNode = cast<IdNode*>(binNode->getChild(0));
//             break;
//         case BinaryOpType::Index:
//             isArr = true;
//             break;
//         }
//     }

//     if (isVar)
//     {

//         bool isLocal = true;

//         switch (idNode->getMemRefType())
//         {
//         case MemReferenceType::Global:
//         case MemReferenceType::Static:
//             isLocal = false;
//             break;
//         }

//         std::stringstream ss;
//         ss << "Load variable " << idNode->getIdName();
//         emitRM("LD", 3, idNode->getMemLoc(), isLocal, ss.str());
//         ss.str("");
//     }
//     else if (isArr)
//     {
//         // do stuff if its an array
//     }
//     else
//     {
//         int value = 0;
//         switch (node->getExpType().getEnumType())
//         {
//         case DataTypeEnum::Bool:
//             emitRM("LD", 3, value, 6, "Load Boolean constant");
//             break;
//         case DataTypeEnum::Char:
//             emitRM("LD", 3, value, 6, "Load char constant");
//             break;
//         case DataTypeEnum::Int:
//             emitRM("LD", 3, value, 6, "Load integer constant");
//             break;
//         }
//     }
// }

void CodeGen::genConst(ConstNode* node)
{
    switch (node->getExpType().getEnumType())
    {
    case DataTypeEnum::Bool:
        emitRM("LDC", 3, int(node->getBoolVal()), 6, "Load Boolean constant");
        break;
    case DataTypeEnum::Char:
        emitRM("LDC", 3, int(node->getCharVal()), 6, "Load char constant");
        break;
    case DataTypeEnum::Int:
        emitRM("LDC", 3, int(node->getIntVal()), 6, "Load integer constant");
        break;
    }
}

void CodeGen::genFor(ForNode* node)
{

}

void CodeGen::toffPush(int toff, bool print)
{
    m_toffs.push_back(toff);
    if (print)
    {
        std::stringstream ss;
        ss << "TOFF set: " << toff;
        emitComment(ss.str());
    }
}

void CodeGen::toffPop(bool print)
{
    m_toffs.pop_back();
    if (print)
    {
        std::stringstream ss;
        ss << "TOFF set: " << m_toffs.back();
        emitComment(ss.str());
    }
}

void CodeGen::toffDec(bool print)
{
    m_toffs.back()--;
    if (print)
    {
        std::stringstream ss;
        ss << "TOFF dec: " << m_toffs.back();
        emitComment(ss.str());
    }
}

void CodeGen::toffInc(bool print)
{
    m_toffs.back()++;
    if (print)
    {
        std::stringstream ss;
        ss << "TOFF inc: " << m_toffs.back();
        emitComment(ss.str());
    }
}

bool CodeGen::isNodeTopMostExp(ASTNode* node)
{
    auto expNode = tryCast<ExpNode*>(node);
    if (expNode == nullptr)
    {
        return false;
    }

    while (node->getParent() != nullptr)
    {
        if (tryCast<ExpNode*>(node->getParent()) != nullptr)
        {
            return false;
        }
        node = node->getParent();
    }
    return true;
}
