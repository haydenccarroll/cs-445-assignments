#include "../hpp/nodeHelper.hpp"
#include "../hpp/node.hpp"
#include "../hpp/subclasses/include.hpp"
#include "../../error/include.hpp"

bool isIdInLval(ASTNode* node)
{
    if (node == nullptr) { return false; }

    auto ancestor = cast<BinaryOpNode*>(node->getAncestor(NodeType::BinaryOpNode));
    while (ancestor != nullptr)
    {
        switch (ancestor->getOperatorType())
        {
        case BinaryOpType::Ass:
        case BinaryOpType::AddAss:
        case BinaryOpType::MulAss:
        case BinaryOpType::DivAss:
            if (node->isAncestor(ancestor->getChild(0)))
            {
                return true;
            }
        }
        ancestor = cast<BinaryOpNode*>(ancestor->getAncestor(NodeType::BinaryOpNode));
    }

    return false;
}

bool isArray(ASTNode* node)
{
    if (node == nullptr) { return false; }

    if (node->getNodeType() == NodeType::IdNode)
    {
        auto idNode = cast<IdNode*>(node);
        if (idNode->getExpType().isArray())
        {
            return true;
        }
    }

    return false;
}

bool doesContainID(ASTNode* node)
{
    if (node == nullptr) { return false;}
    if (node->getNodeType() == NodeType::IdNode) { return true;}

    for (int i=0; i < node->getNumChildren(); i++)
    {
        if (doesContainID(node->getChild(i)))
        {
            return true;
        }
    }

    if (doesContainID(node->getSibling(0)))
    {
        return true;
    }

    return false;
}

bool doesContainCall(ASTNode* node)
{
    if (node == nullptr) { return false;}
    if (node->getNodeType() == NodeType::CallNode) { return true;}

    for (int i=0; i < node->getNumChildren(); i++)
    {
        if (doesContainCall(node->getChild(i)))
        {
            return true;
        }
    }

    if (doesContainCall(node->getSibling(0)))
    {
        return true;
    }

    return false;
}

bool doesContainRand(ASTNode* node)
{
    if (node == nullptr) { return false;}
    if (node->getNodeType() == NodeType::UnaryOpNode)
    {
        auto unaryNode = cast<UnaryOpNode*>(node);
        if (unaryNode->getOperatorType() == UnaryOpType::Random)
        {
            return true;
        }
    }

    for (int i=0; i < node->getNumChildren(); i++)
    {
        if (doesContainRand(node->getChild(i)))
        {
            return true;
        }
    }

    if (doesContainRand(node->getSibling(0)))
    {
        return true;
    }

    return false;
}

bool isConstantExp(ASTNode* node)
{
    if (node == nullptr) { return false; }

    auto expNode = tryCast<ExpNode*>(node);
    if (expNode == nullptr)
    {
        return false;
    }

    if (doesContainID(node) || doesContainRand(node) || doesContainCall(node))
    {
        return false;
    }

    return true;
}
