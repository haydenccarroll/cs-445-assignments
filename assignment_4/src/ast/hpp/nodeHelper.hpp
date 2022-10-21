#pragma once

#include "node.hpp"
#include "../hpp/subclasses/include.hpp"
#include "../../error/include.hpp"

template <typename T> T cast(ASTNode* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    T typedNode = dynamic_cast<T>(node);
    if (typedNode == nullptr)
    {
        Error::critical(node->getLineNum(), "Could not dynamic_cast<> node");
    }
    return typedNode;
}

template <typename T> T tryCast(ASTNode* node)
{
    return dynamic_cast<T>(node);
}

bool isIdInLval(ASTNode* node);

bool isArray(ASTNode* node);