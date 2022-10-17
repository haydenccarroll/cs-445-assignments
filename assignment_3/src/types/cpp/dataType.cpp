#include "../hpp/dataType.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

DataType::DataType(DataType* type, bool isArray) 
{
    if (type == nullptr)
    {
        throw std::runtime_error("type is null in dataType constructor");
    }
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

std::string DataType::toString(bool printOf, bool isStatic) const
{
    std::stringstream ss;
    int count = 0;
    const DataType* tmpPtr = this;
    DataTypeEnum enumType;
    while (tmpPtr->m_nextType != nullptr)
    {
        tmpPtr = tmpPtr->m_nextType;
        count++;
    }
    enumType = tmpPtr->m_enumType;

    if (count != 0)
    {
        ss << "is array ";
        count--;
    }
    for (int i=0; i < count; i++)
    {
        ss << "of array ";
    }

    if (printOf)
    {
        ss << "of ";
    }

    if (isStatic)
    {
        ss << "static ";
    }

    ss << "type ";
    switch (enumType)
    {
    case DataTypeEnum::Bool:
        ss << "bool";
        break;
    case DataTypeEnum::Char:
        ss << "char";
        break;
    case DataTypeEnum::Int:
        ss << "int";
        break;
    case DataTypeEnum::String:
        ss << "string";
        break;
    case DataTypeEnum::Void:
        ss << "void";
        break;
    }

    return ss.str();
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

bool DataType::operator==(const DataType &right) const
{
    return (this->toString() == right.toString());
};

bool DataType::operator!=(const DataType &right) const
{
    return !(this->operator==(right));
}
