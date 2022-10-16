#include "../hpp/dataType.hpp"

#include <iostream>

DataType::DataType(DataType* type, bool isArray) 
{
    m_nextType = nullptr;
    if (!isArray)
    {
        m_enumType = type->m_enumType;
    }
    m_nextType = type;
    m_enumType = DataTypeEnum::Void;
}

DataType::DataType(DataTypeEnum type, bool isArray)
{
    m_nextType = nullptr;
    if (isArray)
    {
        m_nextType = new DataType(type);
    } else 
    {
        m_enumType = type;
    }
}

void DataType::print(bool printOf, bool isStatic)
{
    int count = 0;
    DataType* tmpPtr = this;
    DataTypeEnum enumType;
    while (tmpPtr->m_nextType != nullptr)
    {
        tmpPtr = tmpPtr->m_nextType;
        count++;
    }
    enumType = tmpPtr->m_enumType;

    if (count != 0)
    {
        std::cout << "is array ";
        count--;
    }
    for (int i=0; i < count; i++)
    {
        std::cout << "of array ";
    }

    if (printOf)
    {
        std::cout << "of ";
    }

    if (isStatic)
    {
        std::cout << "static ";
    }

    std::cout << "type ";
    switch (enumType)
    {
    case DataTypeEnum::Bool:
        std::cout << "bool";
        break;
    case DataTypeEnum::Char:
        std::cout << "char";
        break;
    case DataTypeEnum::Int:
        std::cout << "int";
        break;
    case DataTypeEnum::String:
        std::cout << "string";
        break;
    case DataTypeEnum::Void:
        std::cout << "void";
        break;
    }
}

void DataType::setTypeSpec(DataTypeEnum typeSpec)
{
    if (m_nextType != nullptr)
    {
        m_nextType->setTypeSpec(typeSpec);
    } else
    {
        m_enumType = typeSpec;
    }
}
