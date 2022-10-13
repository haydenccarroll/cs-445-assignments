#pragma once

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
    void setTypeSpec(DataTypeEnum typeSpec);
private:
    DataType* m_nextType;
    DataTypeEnum m_enumType;
};
