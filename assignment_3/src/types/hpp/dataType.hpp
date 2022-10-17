#pragma once

#include <string>

enum class DataTypeEnum
{
    Int,
    Bool,
    Char,
    String,
    Void
};

class DataType
{
public:
    DataType(DataType* type, bool isArray=false);
    DataType(DataTypeEnum type, bool isArray=false);
    void print(bool printOf=true, bool isStatic=false);
    std::string toString(bool printOf=true, bool isStatic=false) const;
    void setTypeSpec(DataTypeEnum typeSpec);
    bool isArray() { return (m_nextType != nullptr); }
    bool operator==(const DataType &right) const;
    bool operator!=(const DataType &right) const;

private:
    DataType* m_nextType;
    DataTypeEnum m_enumType;
};
