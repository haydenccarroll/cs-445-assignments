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