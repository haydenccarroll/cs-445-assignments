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

void CodeGen::genGlobalStatics()
{
    genGlobals(m_tree);
    genStatics(m_tree);
}

void CodeGen::genStatics(ASTNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    if (node->getNodeType() == NodeType::VarDeclNode &&
        node->getMemRefType() == MemReferenceType::Static)
    {
        auto decl = cast<VarDeclNode*>(node);
        if (decl->getDataType().isArray())
        {
            std::stringstream ss;
            ss << "load size of array " << decl->getName();
            emitRM("LDC", 3, decl->getMemSize()-1, 6, ss.str(), false);
            ss.str("");

            bool isLocal = decl->getMemRefType() == MemReferenceType::Local;
            ss << "save size of array " << decl->getName();
            emitRM("ST", 3, decl->getMemLoc()+1, 0, ss.str(), false);
            ss.str("");
            if (decl->getChild(0) != nullptr)
            {
                traverseGenerate(decl->getChild(0));
                genArrayCopy(decl, decl->getChild(0));
            }
        } else if (decl->getChild(0) != nullptr) // is initialization
        {
            std::stringstream ss;
            ss << "Store variable " << decl->getName();
            traverseGenerate(decl->getChild(0));
            emitRM("ST", 3, decl->getMemLoc(), 0, ss.str(), false);
        }

    }

    for (int i=0; i < node->getNumChildren(); i++)
    {
        genStatics(node->getChild(i));
    }
    genStatics(node->getSibling(0));
}

void CodeGen::genGlobals(ASTNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    if (node->getNodeType() == NodeType::VarDeclNode &&
        node->getMemRefType() == MemReferenceType::Global)
    {
        auto decl = cast<VarDeclNode*>(node);
        if (decl->getDataType().isArray())
        {
            std::stringstream ss;
            ss << "load size of array " << decl->getName();
            emitRM("LDC", 3, decl->getMemSize()-1, 6, ss.str(), false);
            ss.str("");

            bool isLocal = decl->getMemRefType() == MemReferenceType::Local;
            ss << "save size of array " << decl->getName();
            emitRM("ST", 3, decl->getMemLoc()+1, 0, ss.str(), false);
            ss.str("");

            if (decl->getChild(0) != nullptr)
            {
                traverseGenerate(decl->getChild(0));
                genArrayCopy(decl, decl->getChild(0));
            }
        } else if (decl->getChild(0) != nullptr) // is initialization
        {
            std::stringstream ss;
            ss << "Store variable " << decl->getName();
            traverseGenerate(decl->getChild(0));
            emitRM("ST", 3, decl->getMemLoc(), 0, ss.str(), false);
        }

    }
    genGlobals(node->getSibling(0));
}

void CodeGen::genArrayCopy(ASTNode* lhs, ASTNode* rhs)
{
    if (lhs == nullptr || rhs == nullptr)
    {
        return;
    }
    emitRM("LDA", 4, lhs->getMemLoc(), 1, "address of lhs");
    emitRM("LD", 5, 1, 3, "size of rhs");
    emitRM("LD", 6, 1, 4, "size of lhs");
    emitRO("SWP", 5, 6, 6, "pick smallest size");
    emitRO("MOV", 4, 3, 5, "array op =");
}


void CodeGen::genEndStuff()
{
    int currLoc = emitWhereAmI();
    emitNewLoc(0);
    emitRM("JMP", 7, currLoc - 1, 7, "Jump to init [backpatch]");
    emitNewLoc(currLoc);

    emitComment("INIT");
    emitRM("LDA", 1, m_finalGOffset, 0, "set first frame at end of globals"); // should use goffset
    emitRM("ST", 1, 0, 1, "store old fp (point to self)");
    emitComment("INIT GLOBALS AND STATICS");
    genGlobalStatics();
    emitComment("END INIT GLOBALS AND STATICS");
    emitRM("LDA", 3, 1, 7, "Return address in ac");

    int offsetFromMain = m_funcsToLocs.at("main") - emitWhereAmI() - 1;
    emitRM("JMP", 7, offsetFromMain, 7, "Jump to main");
    emitRO("HALT", 0, 0, 0, "DONE!");
    emitComment("END INIT");
}

void CodeGen::traverseGenerate(ASTNode* node, bool traverseSiblings)
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
    case NodeType::BinaryOpNode:
        genBinary(cast<BinaryOpNode*>(node));
        break;
    case NodeType::UnaryOpNode:
        genUnary(cast<UnaryOpNode*>(node));
        break;
    case NodeType::IdNode:
        genID(cast<IdNode*>(node));
        break;
    case NodeType::IfNode:
        genIf(cast<IfNode*>(node));
        break;
    case NodeType::WhileNode:
        genWhile(cast<WhileNode*>(node));
        break;
    case NodeType::BreakNode:
        genBreak(cast<BreakNode*>(node));
        break;
    case NodeType::ForNode:
        genFor(cast<ForNode*>(node));
        break;
    }

    if (node->getNodeType() != NodeType::VarDeclNode)
    {
        for (unsigned int i=0; i < node->getNumChildren(); i++)
        {
            traverseGenerate(node->getChild(i));
        }
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
    
    if (traverseSiblings)
    {
        traverseGenerate(node->getSibling(0));
    }
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
    toffPush(node->getMemSize());
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
}

void CodeGen::genID(IdNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    bool isLocal = true;
    switch (node->getMemRefType())
    {
    case MemReferenceType::Global:
    case MemReferenceType::Static:
        isLocal = false;
    }

    if (!node->getExpType().isArray())
    {
        std::stringstream ss;
        ss << "Load variable " << node->getIdName();
        emitRM("LD", 3, node->getMemLoc(), (int) isLocal, ss.str(), false);
        ss.str("");
    }
    else
    {
        std::stringstream ss;
        ss << "Load address of base of array " << node->getIdName();
        if (node->getMemRefType() == MemReferenceType::Parameter)
        {
            emitRM("LD", 3, node->getMemLoc(), isLocal, ss.str(), false);
        }
        else
        {
            emitRM("LDA", 3, node->getMemLoc(), isLocal, ss.str(), false);
        }
        ss.str("");
    }
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
        if (child->getMemRefType() != MemReferenceType::Static)
        {
            size += child->getMemSize();
        }

        child = tryCast<VarDeclNode*>(child->getSibling(0));
    }
    toffPush(m_toffs.back() - size);
    child = tryCast<VarDeclNode*>(node->getChild(0));
    while (child != nullptr)
    {
        int isLocal = 1;
        switch (child->getMemRefType())
        {
        case MemReferenceType::Global:
        case MemReferenceType::Static:
            isLocal = 0;
        }
        if (isLocal == 1)
        {
            child->setHasBeenCodegenned(true);
            if (child->getDataType().isArray())
            {
                std::stringstream ss;
                ss << "load size of array " << child->getName();
                emitRM("LDC", 3, child->getMemSize()-1, 6, ss.str(), false);
                ss.str("");

                bool isLocal = child->getMemRefType() == MemReferenceType::Local;
                ss << "save size of array " << child->getName();
                emitRM("ST", 3, child->getMemLoc() + 1, isLocal, ss.str(), false);
                ss.str("");
                if (child->getChild(0) != nullptr)
                {
                    traverseGenerate(child->getChild(0));
                    genArrayCopy(child, child->getChild(0));
                }
            } else if (child->getChild(0) != nullptr) // there is an initialization
            {

                std::stringstream ss;
                ss << "Store variable " << child->getName();
                traverseGenerate(child->getChild(0));
                emitRM("ST", 3, child->getMemLoc(), isLocal, ss.str(), false);
            }
        }

        child = tryCast<VarDeclNode*>(child->getSibling(0));
    }
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

    auto returnVal = node->getChild(0);
    if (returnVal != nullptr)
    {
        traverseGenerate(returnVal);
        emitRM("LDA", 2, 0, 3, "Copy result to return register");
    }

    emitRM("LD", 3, -1, 1, "Load return address");
    emitRM("LD", 1, 0, 1, "Adjust fp");
    emitRM("JMP", 7, 0, 3, "Return");
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


    auto param = node->getChild(0);
    int count = 1;
    while (param != nullptr)
    {
        ss << "Param " << count;
        emitComment(ss.str());
        ss.str("");

        traverseGenerate(param, false);

        emitRM("ST", 3, m_toffs.back(), 1, "Push parameter");
        toffDec();

        param = param->getSibling(0);
        count++;
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

void CodeGen::genUnary(UnaryOpNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    switch (node->getOperatorType())
    {
    case UnaryOpType::Chsign:
        genChsign(node);
        break;
    case UnaryOpType::Dec:
        genDec(node);
        break;
    case UnaryOpType::Inc:
        genInc(node);
        break;
    case UnaryOpType::Not:
        genNot(node);
        break;
    case UnaryOpType::Random:
        genRand(node);
        break;
    case UnaryOpType::SizeOf:
        genSizeOf(node);
        break;
    }
}

void CodeGen::genSizeOf(UnaryOpNode* node)
{
    if (node == nullptr || node->getNodeType() != NodeType::UnaryOpNode)
    {
        return;
    }

    traverseGenerate(node->getChild(0));
    emitRM("LD", 3, 1, 3, "Load array size");
}

void CodeGen::genInc(UnaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != UnaryOpType::Inc)
    {
        return;
    }

    bool isGlobal = false;
    bool isArray = false;
    int thirdParm;
    int secondParm = 0;
    node->getChild(0)->setHasBeenCodegenned(true);
    auto idNode = tryCast<IdNode*>(node->getChild(0));
    if (idNode != nullptr)
    {
        switch (idNode->getMemRefType())
        {
        case MemReferenceType::Global:
        case MemReferenceType::Static:
            isGlobal = true;
        }
        if (isGlobal)
        {
            thirdParm= 0;
        }
        else if (idNode->getExpType().isArray())
        {
            thirdParm = 5;
        }
        else
        {
            thirdParm = 1;
            secondParm = -2;
        }

        std::stringstream ss;
        ss << "load lhs variable " << idNode->getIdName();
        emitRM("LD", 3, idNode->getMemLoc(), thirdParm, ss.str(), false);
        ss.str("");

        ss << "increment value of " << idNode->getIdName();
        emitRM("LDA", 3, 1, 3, ss.str(), false);
        ss.str("");

        ss << "Store variable " << idNode->getIdName();
        emitRM("ST", 3, idNode->getMemLoc(), thirdParm, ss.str(), false);
        ss.str("");
    }
    else // must be array index
    {
        genLHSIndex(cast<BinaryOpNode*>(node->getChild(0)), nullptr, 3);
        std::stringstream ss;

        auto idNode = cast<IdNode*>(node->getChild(0)->getChild(0));
        ss << "load lhs variable " << idNode->getIdName();
        emitRM("LD", 3, 0, 5, ss.str(), false);
        ss.str("");
        ss << "increment value of " << idNode->getIdName();
        emitRM("LDA", 3, 1, 3, ss.str(), false);
        ss.str("");
        ss << "Store variable " << idNode->getIdName();
        emitRM("ST", 3, 0, 5, ss.str(), false);
    }
}

void CodeGen::genDec(UnaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != UnaryOpType::Dec)
    {
        return;
    }

    bool isGlobal = false;
    bool isArray = false;
    int thirdParm;
    int secondParm = 0;
    node->getChild(0)->setHasBeenCodegenned(true);
    auto idNode = tryCast<IdNode*>(node->getChild(0));
    if (idNode != nullptr)
    {
        switch (idNode->getMemRefType())
        {
        case MemReferenceType::Global:
        case MemReferenceType::Static:
            isGlobal = true;
        }
        if (isGlobal)
        {
            thirdParm= 0;
        }
        else if (idNode->getExpType().isArray())
        {
            thirdParm = 5;
        }
        else
        {
            thirdParm = 1;
            secondParm = -2;
        }

        std::stringstream ss;
        ss << "load lhs variable " << idNode->getIdName();
        emitRM("LD", 3, idNode->getMemLoc(), thirdParm, ss.str(), false);
        ss.str("");

        ss << "decrement value of " << idNode->getIdName();
        emitRM("LDA", 3, -1, 3, ss.str(), false);
        ss.str("");

        ss << "Store variable " << idNode->getIdName();
        emitRM("ST", 3, idNode->getMemLoc(), thirdParm, ss.str(), false);
        ss.str("");
    }
    else // must be array index
    {
        genLHSIndex(cast<BinaryOpNode*>(node->getChild(0)), nullptr, 3);
        std::stringstream ss;

        auto idNode = cast<IdNode*>(node->getChild(0)->getChild(0));
        ss << "load lhs variable " << idNode->getIdName();
        emitRM("LD", 3, 0, 5, ss.str(), false);
        ss.str("");
        ss << "decrement value of " << idNode->getIdName();
        emitRM("LDA", 3, -1, 3, ss.str(), false);
        ss.str("");
        ss << "Store variable " << idNode->getIdName();
        emitRM("ST", 3, 0, 5, ss.str(), false);
    }
}

void CodeGen::genNot(UnaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != UnaryOpType::Not)
    {
        return;
    }

    traverseGenerate(node->getChild(0)); // generate RHS

    emitRM("LDC", 4, 1, 6, "Load 1");
    emitRO("XOR", 3, 3, 4, "Op XOR to get logical not");
}

void CodeGen::genRand(UnaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != UnaryOpType::Random)
    {
        return;
    }

    traverseGenerate(node->getChild(0)); // generate RHS

    emitRO("RND", 3, 3, 6, "Op ?");
}

void CodeGen::genChsign(UnaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != UnaryOpType::Chsign)
    {
        return;
    }

    traverseGenerate(node->getChild(0)); // generate RHS

    emitRO("NEG", 3, 3, 3, "Op unary -");
}

void CodeGen::genBinary(BinaryOpNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    switch (node->getOperatorType())
    {
    case BinaryOpType::Ass:
        genAss(node);
        break;
    case BinaryOpType::AddAss:
        genAddAss(node);
        break;
    case BinaryOpType::DivAss:
        genDivAss(node);
        break;
    case BinaryOpType::MulAss:
        genMulAss(node);
        break;
    case BinaryOpType::SubAss:
        genSubAss(node);
        break;
    case BinaryOpType::Or:
        genOr(node);
        break;
    case BinaryOpType::And:
        genAnd(node);
        break;
    case BinaryOpType::Add:
        genAdd(node);
        break;
    case BinaryOpType::Sub:
        genSub(node);
        break;
    case BinaryOpType::Mul:
        genMul(node);
        break;
    case BinaryOpType::Div:
        genDiv(node);
        break;
    case BinaryOpType::Mod:
        genMod(node);
        break;
    case BinaryOpType::EQ:
        genTEQ(node);
        break;
    case BinaryOpType::GT:
        genTGT(node);
        break;
    case BinaryOpType::LT:
        genTLT(node);
        break;
    case BinaryOpType::NEQ:
        genTNEQ(node);
        break;
    case BinaryOpType::LEQ:
        genTLE(node);
        break;
    case BinaryOpType::GEQ:
        genTGE(node);
        break;
    case BinaryOpType::Index:
        genIndex(node);
        break;
    }
}

void CodeGen::genAss(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::Ass)
    {
        return;
    }

    node->getChild(0)->setHasBeenCodegenned(true);

    auto idNode = tryCast<IdNode*>(node->getChild(0));
    if (idNode)
    {
        traverseGenerate(node->getChild(1)); // calculate RHS first.

        if (idNode->getExpType().isArray())
        {
            genArrayCopy(idNode, node->getChild(1));
            return;
        }

        // 0 if global/static
        // 1 if lcocal
        bool isLocal = 1;
        bool isArray = false;
        switch (idNode->getMemRefType())
        {
        case MemReferenceType::Global:
        case MemReferenceType::Static:
            isLocal = 0;
        }

        std::stringstream ss;
        ss << "Store variable " << idNode->getIdName();
        emitRM("ST", 3, idNode->getMemLoc(), isLocal, ss.str(), false);
    }
    else // it must be array index
    {
        auto indexNode = cast<BinaryOpNode*>(node->getChild(0));
        genLHSIndex(indexNode, node->getChild(1));

        std::stringstream ss;
        auto idNode = cast<IdNode*>(indexNode->getChild(0));
        ss << "Store variable " << idNode->getIdName();
        emitRM("ST", 3, 0, 5, ss.str(), false);
    }
}

void CodeGen::genAddAss(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::AddAss)
    {
        return;
    }

    node->getChild(0)->setHasBeenCodegenned(true);

    auto idNode = tryCast<IdNode*>(node->getChild(0));
    if (idNode)
    {
        traverseGenerate(node->getChild(1)); // calculate RHS first.

        // 0 if global/static
        // 1 if lcocal
        // 5 if array?
        bool isGlobal = false;
        bool isArray = false;
        switch (idNode->getMemRefType())
        {
        case MemReferenceType::Global:
        case MemReferenceType::Static:
            isGlobal = true;
        }

        int thirdSTParam;
        if (isGlobal)
        {
            thirdSTParam = 0;
        }
        else if (idNode->getExpType().isArray())
        {
            thirdSTParam = 5;
        }
        else
        {
            thirdSTParam = 1;
        }

        std::stringstream ss;
        ss << "load lhs variable " << idNode->getIdName();
        emitRM("LD", 4, idNode->getMemLoc(), thirdSTParam, ss.str(), false);
        ss.str("");

        emitRO("ADD", 3, 4, 3, "op +=");

        ss << "Store variable " << idNode->getIdName();
        emitRM("ST", 3, idNode->getMemLoc(), thirdSTParam, ss.str(), false);
    }
    else
    {
        auto indexNode = cast<BinaryOpNode*>(node->getChild(0));
        genLHSIndex(indexNode, node->getChild(1));

        std::stringstream ss;
        auto idNode = cast<IdNode*>(indexNode->getChild(0));
        ss << "load lhs variable " << idNode->getIdName();
        emitRM("LD", 4, 0, 5, ss.str(), false);
        ss.str("");
        emitRO("ADD", 3, 4, 3, "op +=");
        ss << "Store variable " << idNode->getIdName();
        emitRM("ST", 3, 0, 5, ss.str(), false);
    }
}

void CodeGen::genSubAss(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::SubAss)
    {
        return;
    }

    node->getChild(0)->setHasBeenCodegenned(true);

    auto idNode = tryCast<IdNode*>(node->getChild(0));
    if (idNode)
    {
        traverseGenerate(node->getChild(1)); // calculate RHS first.

        // 0 if global/static
        // 1 if lcocal
        // 5 if array?
        bool isGlobal = false;
        bool isArray = false;
        switch (idNode->getMemRefType())
        {
        case MemReferenceType::Global:
        case MemReferenceType::Static:
            isGlobal = true;
        }

        int thirdSTParam;
        if (isGlobal)
        {
            thirdSTParam = 0;
        }
        else if (idNode->getExpType().isArray())
        {
            thirdSTParam = 5;
        }
        else
        {
            thirdSTParam = 1;
        }

        std::stringstream ss;
        ss << "load lhs variable " << idNode->getIdName();
        emitRM("LD", 4, idNode->getMemLoc(), thirdSTParam, ss.str(), false);
        ss.str("");

        emitRO("SUB", 3, 4, 3, "op -=");

        ss << "Store variable " << idNode->getIdName();
        emitRM("ST", 3, idNode->getMemLoc(), thirdSTParam, ss.str(), false);
    }
    else
    {
        auto indexNode = cast<BinaryOpNode*>(node->getChild(0));
        genLHSIndex(indexNode, node->getChild(1));

        std::stringstream ss;
        auto idNode = cast<IdNode*>(indexNode->getChild(0));
        ss << "load lhs variable " << idNode->getIdName();
        emitRM("LD", 4, 0, 5, ss.str(), false);
        ss.str("");
        emitRO("SUB", 3, 4, 3, "op -=");
        ss << "Store variable " << idNode->getIdName();
        emitRM("ST", 3, 0, 5, ss.str(), false);
    }
}

void CodeGen::genMulAss(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::MulAss)
    {
        return;
    }

    node->getChild(0)->setHasBeenCodegenned(true);

    auto idNode = tryCast<IdNode*>(node->getChild(0));
    if (idNode)
    {
        traverseGenerate(node->getChild(1)); // calculate RHS first.

        // 0 if global/static
        // 1 if lcocal
        // 5 if array?
        bool isGlobal = false;
        bool isArray = false;
        switch (idNode->getMemRefType())
        {
        case MemReferenceType::Global:
        case MemReferenceType::Static:
            isGlobal = true;
        }

        int thirdSTParam;
        if (isGlobal)
        {
            thirdSTParam = 0;
        }
        else if (idNode->getExpType().isArray())
        {
            thirdSTParam = 5;
        }
        else
        {
            thirdSTParam = 1;
        }

        std::stringstream ss;
        ss << "load lhs variable " << idNode->getIdName();
        emitRM("LD", 4, idNode->getMemLoc(), thirdSTParam, ss.str(), false);
        ss.str("");

        emitRO("MUL", 3, 4, 3, "op *=");

        ss << "Store variable " << idNode->getIdName();
        emitRM("ST", 3, idNode->getMemLoc(), thirdSTParam, ss.str(), false);
    }
    else
    {
        auto indexNode = cast<BinaryOpNode*>(node->getChild(0));
        genLHSIndex(indexNode, node->getChild(1));

        std::stringstream ss;
        auto idNode = cast<IdNode*>(indexNode->getChild(0));
        ss << "load lhs variable " << idNode->getIdName();
        emitRM("LD", 4, 0, 5, ss.str(), false);
        ss.str("");
        emitRO("MUL", 3, 4, 3, "op *=");
        ss << "Store variable " << idNode->getIdName();
        emitRM("ST", 3, 0, 5, ss.str(), false);
    }
}

void CodeGen::genDivAss(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::DivAss)
    {
        return;
    }

    node->getChild(0)->setHasBeenCodegenned(true);

    auto idNode = tryCast<IdNode*>(node->getChild(0));
    if (idNode)
    {
        traverseGenerate(node->getChild(1)); // calculate RHS first.

        // 0 if global/static
        // 1 if lcocal
        // 5 if array?
        bool isGlobal = false;
        bool isArray = false;
        switch (idNode->getMemRefType())
        {
        case MemReferenceType::Global:
        case MemReferenceType::Static:
            isGlobal = true;
        }

        int thirdSTParam;
        if (isGlobal)
        {
            thirdSTParam = 0;
        }
        else if (idNode->getExpType().isArray())
        {
            thirdSTParam = 5;
        }
        else
        {
            thirdSTParam = 1;
        }

        std::stringstream ss;
        ss << "load lhs variable " << idNode->getIdName();
        emitRM("LD", 4, idNode->getMemLoc(), thirdSTParam, ss.str(), false);
        ss.str("");

        emitRO("DIV", 3, 4, 3, "op /=");

        ss << "Store variable " << idNode->getIdName();
        emitRM("ST", 3, idNode->getMemLoc(), thirdSTParam, ss.str(), false);
    }
    else
    {
        auto indexNode = cast<BinaryOpNode*>(node->getChild(0));
        genLHSIndex(indexNode, node->getChild(1));

        std::stringstream ss;
        auto idNode = cast<IdNode*>(indexNode->getChild(0));
        ss << "load lhs variable " << idNode->getIdName();
        emitRM("LD", 4, 0, 5, ss.str(), false);
        ss.str("");
        emitRO("DIV", 3, 4, 3, "op /=");
        ss << "Store variable " << idNode->getIdName();
        emitRM("ST", 3, 0, 5, ss.str(), false);
    }
}

void CodeGen::genGenericBinOp(BinaryOpNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    // generic BinOp stuff
    traverseGenerate(node->getChild(0)); // traverse LHS
    emitRM("ST", 3, m_toffs.back(), 1, "Push left side");
    toffDec();
    traverseGenerate(node->getChild(1)); // traverse RHS
    toffInc();
    emitRM("LD", 4, m_toffs.back(), 1, "Pop left into ac1");
}

void CodeGen::genOr(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::Or)
    {
        return;
    }

    genGenericBinOp(node);
    emitRO("OR", 3, 4, 3, "Op OR");
}

void CodeGen::genAnd(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::And)
    {
        return;
    }

    genGenericBinOp(node);
    emitRO("AND", 3, 4, 3, "Op AND");
}

void CodeGen::genTEQ(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::EQ)
    {
        return;
    }

    genGenericBinOp(node);
    if (cast<ExpNode*>(node->getChild(0))->getExpType().isArray())
    {
        emitRM("LD", 5, 1, 3, "AC2 <- |RHS|");
        emitRM("LD", 6, 1, 4, "AC3 <- |LHS|");
        emitRM("LDA", 2, 0, 5, "R2 <- |RHS|");
        emitRO("SWP", 5, 6, 6, "pick smallest size");
        emitRM("LD", 6, 1, 4, "AC3 <- |LHS|");
        emitRO("CO", 4, 3, 5, "setup array compare  LHS vs RHS");
        emitRO("TNE", 5, 4, 3, "if not equal then test (AC1, AC)");
        emitRO("JNZ", 5, 2, 7, "jump not equal");
        emitRM("LDA", 3, 0, 2, "AC1 <- |RHS|");
        emitRM("LDA", 4, 0, 6, "AC <- |LHS|");
    }
    emitRO("TEQ", 3, 4, 3, "Op ==");
}



void CodeGen::genTNEQ(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::NEQ)
    {
        return;
    }

    genGenericBinOp(node);
    if (cast<ExpNode*>(node->getChild(0))->getExpType().isArray())
    {
        emitRM("LD", 5, 1, 3, "AC2 <- |RHS|");
        emitRM("LD", 6, 1, 4, "AC3 <- |LHS|");
        emitRM("LDA", 2, 0, 5, "R2 <- |RHS|");
        emitRO("SWP", 5, 6, 6, "pick smallest size");
        emitRM("LD", 6, 1, 4, "AC3 <- |LHS|");
        emitRO("CO", 4, 3, 5, "setup array compare  LHS vs RHS");
        emitRO("TNE", 5, 4, 3, "if not equal then test (AC1, AC)");
        emitRO("JNZ", 5, 2, 7, "jump not equal");
        emitRM("LDA", 3, 0, 2, "AC1 <- |RHS|");
        emitRM("LDA", 4, 0, 6, "AC <- |LHS|");
    }
    emitRO("TNE", 3, 4, 3, "Op !=");
}

void CodeGen::genTGE(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::GEQ)
    {
        return;
    }

    genGenericBinOp(node);
    if (cast<ExpNode*>(node->getChild(0))->getExpType().isArray())
    {
        emitRM("LD", 5, 1, 3, "AC2 <- |RHS|");
        emitRM("LD", 6, 1, 4, "AC3 <- |LHS|");
        emitRM("LDA", 2, 0, 5, "R2 <- |RHS|");
        emitRO("SWP", 5, 6, 6, "pick smallest size");
        emitRM("LD", 6, 1, 4, "AC3 <- |LHS|");
        emitRO("CO", 4, 3, 5, "setup array compare  LHS vs RHS");
        emitRO("TNE", 5, 4, 3, "if not equal then test (AC1, AC)");
        emitRO("JNZ", 5, 2, 7, "jump not equal");
        emitRM("LDA", 3, 0, 2, "AC1 <- |RHS|");
        emitRM("LDA", 4, 0, 6, "AC <- |LHS|");
    }
    emitRO("TGE", 3, 4, 3, "Op >=");
}

void CodeGen::genTLE(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::LEQ)
    {
        return;
    }

    genGenericBinOp(node);
    if (cast<ExpNode*>(node->getChild(0))->getExpType().isArray())
    {
        emitRM("LD", 5, 1, 3, "AC2 <- |RHS|");
        emitRM("LD", 6, 1, 4, "AC3 <- |LHS|");
        emitRM("LDA", 2, 0, 5, "R2 <- |RHS|");
        emitRO("SWP", 5, 6, 6, "pick smallest size");
        emitRM("LD", 6, 1, 4, "AC3 <- |LHS|");
        emitRO("CO", 4, 3, 5, "setup array compare  LHS vs RHS");
        emitRO("TNE", 5, 4, 3, "if not equal then test (AC1, AC)");
        emitRO("JNZ", 5, 2, 7, "jump not equal");
        emitRM("LDA", 3, 0, 2, "AC1 <- |RHS|");
        emitRM("LDA", 4, 0, 6, "AC <- |LHS|");
    }
    emitRO("TLE", 3, 4, 3, "Op <=");
}

void CodeGen::genTGT(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::GT)
    {
        return;
    }

    genGenericBinOp(node);
    if (cast<ExpNode*>(node->getChild(0))->getExpType().isArray())
    {
        emitRM("LD", 5, 1, 3, "AC2 <- |RHS|");
        emitRM("LD", 6, 1, 4, "AC3 <- |LHS|");
        emitRM("LDA", 2, 0, 5, "R2 <- |RHS|");
        emitRO("SWP", 5, 6, 6, "pick smallest size");
        emitRM("LD", 6, 1, 4, "AC3 <- |LHS|");
        emitRO("CO", 4, 3, 5, "setup array compare  LHS vs RHS");
        emitRO("TNE", 5, 4, 3, "if not equal then test (AC1, AC)");
        emitRO("JNZ", 5, 2, 7, "jump not equal");
        emitRM("LDA", 3, 0, 2, "AC1 <- |RHS|");
        emitRM("LDA", 4, 0, 6, "AC <- |LHS|");
    }
    emitRO("TGT", 3, 4, 3, "Op >");
}

void CodeGen::genTLT(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::LT)
    {
        return;
    }

    genGenericBinOp(node);
    if (cast<ExpNode*>(node->getChild(0))->getExpType().isArray())
    {
        emitRM("LD", 5, 1, 3, "AC2 <- |RHS|");
        emitRM("LD", 6, 1, 4, "AC3 <- |LHS|");
        emitRM("LDA", 2, 0, 5, "R2 <- |RHS|");
        emitRO("SWP", 5, 6, 6, "pick smallest size");
        emitRM("LD", 6, 1, 4, "AC3 <- |LHS|");
        emitRO("CO", 4, 3, 5, "setup array compare  LHS vs RHS");
        emitRO("TNE", 5, 4, 3, "if not equal then test (AC1, AC)");
        emitRO("JNZ", 5, 2, 7, "jump not equal");
        emitRM("LDA", 3, 0, 2, "AC1 <- |RHS|");
        emitRM("LDA", 4, 0, 6, "AC <- |LHS|");
    }
    emitRO("TLT", 3, 4, 3, "Op <");
}

void CodeGen::genMod(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::Mod)
    {
        return;
    }

    genGenericBinOp(node);
    emitRO("MOD", 3, 4, 3, "Op %");
}

void CodeGen::genMul(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::Mul)
    {
        return;
    }

    genGenericBinOp(node);
    emitRO("MUL", 3, 4, 3, "Op *");
}

void CodeGen::genDiv(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::Div)
    {
        return;
    }

    genGenericBinOp(node);
    emitRO("DIV", 3, 4, 3, "Op /");
}

void CodeGen::genAdd(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::Add)
    {
        return;
    }

    genGenericBinOp(node);
    emitRO("ADD", 3, 4, 3, "Op +");
}

void CodeGen::genSub(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::Sub)
    {
        return;
    }

    genGenericBinOp(node);
    emitRO("SUB", 3, 4, 3, "Op -");
}

void CodeGen::genLHSIndex(BinaryOpNode* node, ASTNode* rhs, int subThirdParam)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::Index)
    {
        return;
    }

    auto idNode = cast<IdNode*>(node->getChild(0));
    int isLocal = 1;
    switch (idNode->getMemRefType())
    {
    case MemReferenceType::Global:
    case MemReferenceType::Static:
        isLocal = 0;
    }
    traverseGenerate(node->getChild(1)); // generate array index here
    if (rhs != nullptr)
    {
        emitRM("ST", 3, m_toffs.back(), 1, "Push index");
        toffDec();
        traverseGenerate(rhs);
        toffInc();
        emitRM("LD", 4, m_toffs.back(), 1, "Pop index");
    }
    std::stringstream ss;
    ss << "Load address of base of array " << idNode->getIdName();
    if (idNode->getMemRefType() == MemReferenceType::Parameter)
    {
        emitRM("LD", 5, idNode->getMemLoc(), isLocal, ss.str(), false);
    }
    else
    {
        emitRM("LDA", 5, idNode->getMemLoc(), isLocal, ss.str(), false);
    }
    emitRO("SUB", 5, 5, subThirdParam, "Compute offset of value");
}

void CodeGen::genIndex(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::Index)
    {
        return;
    }

    std::stringstream ss;
    auto idNode = cast<IdNode*>(node->getChild(0));
    idNode->setHasBeenCodegenned(true);
    ss << "Load address of base of array " << idNode->getIdName();

    // first param is 3, unless its on LHS
    int isLocal = 1;
    switch (idNode->getMemRefType())
    {
    case MemReferenceType::Global:
    case MemReferenceType::Static:
        isLocal = 0;
    }
    if (idNode->getMemRefType() == MemReferenceType::Parameter)
    {
        emitRM("LD", 3, idNode->getMemLoc(), isLocal, ss.str(), false);
    }
    else
    {
        emitRM("LDA", 3, idNode->getMemLoc(), isLocal, ss.str(), false);
    }
    emitRM("ST", 3, m_toffs.back(), 1, "Push left side");
    toffDec();
    traverseGenerate(node->getChild(1)); // calculate array index here
    toffInc();
    emitRM("LD", 4, m_toffs.back(), 1, "Pop left into ac1");
    emitRO("SUB", 3, 4, 3, "compute location from index");
    emitRM("LD", 3, 0, 3, "Load array element");
}

void CodeGen::genConst(ConstNode* node)
{
    if (node->getExpType().isArray())
    {
        emitStrLit(m_litOff, (char*) node->getStringVal().c_str());
        m_litOff += node->getStringVal().length() + 1;
        emitRM("LDA", 3, node->getMemLoc(), 0, "Load address of char array");
        return;
    }
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

void CodeGen::genIf(IfNode* node)
{
    if (node == nullptr || node->getNodeType() != NodeType::IfNode)
    {
        return;
    }

    emitComment("IF");

    traverseGenerate(node->getChild(0));

    // leave space for the jump at the end.
    int oldInstruct = emitWhereAmI();
    emitNewLoc(oldInstruct+1);

    emitComment("THEN");
    traverseGenerate(node->getChild(1));

    int newInstruct = emitWhereAmI();
    emitNewLoc(oldInstruct);
    if (node->getChild(2) != nullptr) // if there is else 
    {
        emitRM("JZR", 3, newInstruct - oldInstruct, 7, "Jump around the THEN if false [backpatch]");
    }
    else
    {
        emitRM("JZR", 3, newInstruct - oldInstruct - 1, 7, "Jump around the THEN if false [backpatch]");
    }
    emitNewLoc(newInstruct);

    if (node->getChild(2) != nullptr) // if there is else
    {
        oldInstruct = emitWhereAmI();
        emitNewLoc(oldInstruct+1);

        emitComment("ELSE");
        traverseGenerate(node->getChild(2));

        int newInstruct = emitWhereAmI();
        emitNewLoc(oldInstruct);
        emitRM("JMP", 7, newInstruct - oldInstruct - 1, 7, "Jump around the ELSE [backpatch]");
        emitNewLoc(newInstruct);
    }



    emitComment("END IF");
}

void CodeGen::genWhile(WhileNode* node)
{
    if (node == nullptr || node->getNodeType() != NodeType::WhileNode)
    {
        return;
    }

    emitComment("WHILE");
    int whileStartLoc = emitWhereAmI(); // useful for jumping back to loop

    // generate while condition stuff
    traverseGenerate(node->getChild(0));
    emitRM("JNZ", 3, 1, 7, "Jump to while part");

    int doStartLoc = emitWhereAmI(); // useful for skipping loop entirely
    m_loopLocs.push_back(doStartLoc);
    
    emitNewLoc(doStartLoc + 1);

    // give space for 1 instruction
    emitComment("DO");

    // generate do condition
    traverseGenerate(node->getChild(1));
    emitRM("JMP", 7, whileStartLoc - emitWhereAmI() - 1, 7, "go to beginning of loop");
    int endWhileLoc = emitWhereAmI();
    
    emitNewLoc(doStartLoc);
    emitRM("JMP", 7, endWhileLoc - doStartLoc - 1, 7, "Jump past loop [backpatch]");
    emitNewLoc(endWhileLoc);

    // insert go to beginning of loop instruction
    // insert end loop instruction
    m_loopLocs.pop_back();
    emitComment("END WHILE");
}

void CodeGen::genBreak(BreakNode* node)
{
    if (node == nullptr || node->getNodeType() != NodeType::BreakNode ||
        m_loopLocs.size() == 0)
    {
        return;
    }
    emitComment("BREAK");
    emitRM("JMP", 7, m_loopLocs.back() - emitWhereAmI() - 1, 7, "break");
}

void CodeGen::genFor(ForNode* node)
{
    auto iterDecl = cast<VarDeclNode*>(node->getChild(0));
    auto range = cast<RangeNode*>(node->getChild(1));
    int iterLoc = m_toffs.back();
    int stopLoc = iterLoc - 1;
    int stepLoc = iterLoc - 2;
    toffPush(m_toffs.back() - 3); // 3 is probably typical, but if it has the BY maybe 4
    emitComment("FOR");
    traverseGenerate(range->getChild(0)); // generate lower bound
    emitRM("ST", 3, iterLoc, 1, "save starting value in index variable");
    traverseGenerate(range->getChild(1)); // generate upper bound
    emitRM("ST", 3, stopLoc, 1, "save stop value"); // 2nd param isnt right
    if (range->getChild(2)) // has the by part of range
    {
        traverseGenerate(range->getChild(2));
    }
    else
    {
        emitRM("LDC", 3, 1, 6, "default increment by 1");
    }
    emitRM("ST", 3, stepLoc, 1, "save step value"); // 2nd param isnt right
    int saveStepLoc = emitWhereAmI(); // used for jumping to top of loop
    emitRM("LD", 4, iterLoc, 1, "loop index"); // 2nd param isnt right
    emitRM("LD", 5, stopLoc, 1, "stop value"); // 2nd param isnt right
    emitRM("LD", 3, stepLoc, 1, "step value"); // 2nd param isnt right
    emitRO("SLT", 3, 4, 5, "Op <");
    emitRM("JNZ", 3, 1, 7, "Jump to loop body");


    int startPos = emitWhereAmI();
    emitNewLoc(startPos+1); // save room for backpatch

    traverseGenerate(node->getChild(2)); // gen loop body

    emitComment("Bottom of loop increment and jump");
    emitRM("LD", 3, iterLoc, 1, "Load index"); // 2nd param isnt right
    emitRM("LD", 5, stepLoc, 1, "Load step"); // 2nd param isnt right
    emitRO("ADD", 3, 3, 5, "increment");
    emitRM("ST", 3, iterLoc, 1, "store back to index"); // 2nd param isnt right
    emitRM("JMP", 7, saveStepLoc - emitWhereAmI() - 1, 7, "go to beginning of loop"); // 2nd param isnt right
    
    int endPos = emitWhereAmI();
    emitNewLoc(startPos);
    emitRM("JMP", 7, endPos - startPos - 1, 7, "Jump past loop [backpatch]"); // 2nd param isnt right
    emitNewLoc(endPos);

    toffPop(false);
    emitComment("END LOOP");
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

    if (node->getParent()->getNodeType() == NodeType::CompoundStmtNode)
    {
        return true;
    }
    return false;
}

