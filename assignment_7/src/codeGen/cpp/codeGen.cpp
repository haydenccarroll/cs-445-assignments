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
    emitRM("LDA", 1, m_finalGOffset, 0, "set first frame at end of globals"); // should use goffset
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
    case NodeType::BinaryOpNode:
        genBinary(cast<BinaryOpNode*>(node));
        break;
    case NodeType::UnaryOpNode:
        genUnary(cast<UnaryOpNode*>(node));
        break;
    case NodeType::IdNode:
        genID(cast<IdNode*>(node));
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
}

void CodeGen::genCompoundStmtStart(CompoundStmtNode* node)
{
    if (node == nullptr)
    {
        return;
    }
    emitComment("COMPOUND");
    int oldToff = m_toffs.back();
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
        if (child->getDataType().isArray())
        {
            std::stringstream ss;
            ss << "load size of array " << child->getName();
            emitRM("LDC", 3, child->getMemSize()-1, 6, ss.str(), false);
            ss.str("");

            bool isLocal = child->getMemRefType() == MemReferenceType::Local;
            ss << "save size of array " << child->getName();
            emitRM("ST", 3, oldToff, isLocal, ss.str(), false);
            ss.str("");
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
        break;
    }
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
    auto idNode = tryCast<IdNode*>(node->getChild(0));
    if (idNode == nullptr)
    {
        return;
    }
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

    idNode->setHasBeenCodegenned(true);

    std::stringstream ss;
    ss << "load lhs variable " << idNode->getIdName();
    emitRM("LD", 3, secondParm, thirdParm, ss.str(), false);
    ss.str("");

    ss << "increment value of " << idNode->getIdName();
    emitRM("LDA", 3, 1, 3, ss.str(), false);
    ss.str("");

    ss << "Store variable " << idNode->getIdName();
    emitRM("ST", 3, secondParm, thirdParm, ss.str(), false);
    ss.str("");
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
    auto idNode = tryCast<IdNode*>(node->getChild(0));
    if (idNode == nullptr)
    {
        return;
    }
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

    idNode->setHasBeenCodegenned(true);

    std::stringstream ss;
    ss << "load lhs variable " << idNode->getIdName();
    emitRM("LD", 3, secondParm, thirdParm, ss.str(), false);
    ss.str("");

    ss << "decrement value of " << idNode->getIdName();
    emitRM("LDA", 3, -1, 3, ss.str(), false);
    ss.str("");

    ss << "Store variable " << idNode->getIdName();
    emitRM("ST", 3, secondParm, thirdParm, ss.str(), false);
    ss.str("");
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
    }
}

void CodeGen::genAss(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::Ass)
    {
        return;
    }

    traverseGenerate(node->getChild(1)); // calculate RHS first.

    auto idNode = tryCast<IdNode*>(node->getChild(0));
    if (idNode)
    {
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
        idNode->setHasBeenCodegenned(true); // dont process LHS any more
        ss << "Store variable " << idNode->getIdName();
        emitRM("ST", 3, idNode->getMemLoc(), thirdSTParam, ss.str(), false);
    }
}

void CodeGen::genAddAss(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::AddAss)
    {
        return;
    }

    traverseGenerate(node->getChild(1)); // calculate RHS first.

    auto idNode = tryCast<IdNode*>(node->getChild(0));
    if (idNode)
    {
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
        idNode->setHasBeenCodegenned(true); // dont process LHS any more

        ss << "load lhs variable " << idNode->getIdName();
        emitRM("LD", 4, idNode->getMemLoc(), thirdSTParam, ss.str(), false);
        ss.str("");

        emitRO("ADD", 3, 4, 3, "op +=");

        ss << "Store variable " << idNode->getIdName();
        emitRM("ST", 3, idNode->getMemLoc(), thirdSTParam, ss.str(), false);
    }
}

void CodeGen::genSubAss(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::SubAss)
    {
        return;
    }

    traverseGenerate(node->getChild(1)); // calculate RHS first.

    auto idNode = tryCast<IdNode*>(node->getChild(0));
    if (idNode)
    {
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
        idNode->setHasBeenCodegenned(true); // dont process LHS any more

        ss << "load lhs variable " << idNode->getIdName();
        emitRM("LD", 4, idNode->getMemLoc(), thirdSTParam, ss.str(), false);
        ss.str("");

        emitRO("SUB", 3, 4, 3, "op -=");

        ss << "Store variable " << idNode->getIdName();
        emitRM("ST", 3, idNode->getMemLoc(), thirdSTParam, ss.str(), false);
    }
}

void CodeGen::genMulAss(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::MulAss)
    {
        return;
    }

    traverseGenerate(node->getChild(1)); // calculate RHS first.

    auto idNode = tryCast<IdNode*>(node->getChild(0));
    if (idNode)
    {
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
        idNode->setHasBeenCodegenned(true); // dont process LHS any more

        ss << "load lhs variable " << idNode->getIdName();
        emitRM("LD", 4, idNode->getMemLoc(), thirdSTParam, ss.str(), false);
        ss.str("");

        emitRO("MUL", 3, 4, 3, "op *=");

        ss << "Store variable " << idNode->getIdName();
        emitRM("ST", 3, idNode->getMemLoc(), thirdSTParam, ss.str(), false);
    }
}

void CodeGen::genDivAss(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::DivAss)
    {
        return;
    }

    traverseGenerate(node->getChild(1)); // calculate RHS first.

    auto idNode = tryCast<IdNode*>(node->getChild(0));
    if (idNode)
    {
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
        idNode->setHasBeenCodegenned(true); // dont process LHS any more

        ss << "load lhs variable " << idNode->getIdName();
        emitRM("LD", 4, idNode->getMemLoc(), thirdSTParam, ss.str(), false);
        ss.str("");

        emitRO("DIV", 3, 4, 3, "op /=");

        ss << "Store variable " << idNode->getIdName();
        emitRM("ST", 3, idNode->getMemLoc(), thirdSTParam, ss.str(), false);
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
    emitRO("TEQ", 3, 4, 3, "Op ==");
}

void CodeGen::genTNEQ(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::NEQ)
    {
        return;
    }

    genGenericBinOp(node);
    emitRO("TNEQ", 3, 4, 3, "Op !=");
}

void CodeGen::genTGT(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::GT)
    {
        return;
    }

    genGenericBinOp(node);
    emitRO("TGT", 3, 4, 3, "Op >");
}

void CodeGen::genTLT(BinaryOpNode* node)
{
    if (node == nullptr || node->getOperatorType() != BinaryOpType::LT)
    {
        return;
    }

    genGenericBinOp(node);
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
