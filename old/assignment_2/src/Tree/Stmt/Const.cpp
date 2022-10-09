#include "Const.h"
#include "../Node.h"

#include <string>
#include <variant>

namespace Tree::Stmt
{
    Const::Const(unsigned lineNum, Type type, std::string value)
        : Stmt::Stmt(lineNum),
          _type(type)
    {
        switch (_type)
        {
        case DataType::String:
        {

            _value = value.substr(1, value.length() - 2);
            break;
        }
        case DataType::Bool:
        {
            _value = (value == "true");
            break;
        }
        case DataType::Char:
        {
            std::string tempStr = value.substr(1, value.length() - 2);
            _value = _toChar(tempStr);
            break;
        };
        case DataType::Int:
        {
            _value = std::atoi(value.c_str());
            break;
        }
        };
    }

    std::string Const::toString() const
    {
        std::string str = "Const ";

        switch (_type)
        {
        case DataType::Int:
        {
            str += std::to_string(std::get<int>(_value));
            break;
        }
        case DataType::Bool:
        {
            if (std::get<bool>(_value))
            {
                str += "true";
            }
            else
            {
                str += "false";
            }
            break;
        }
        case DataType::Char:
        {
            str += "'" + std::string(1, std::get<char>(_value)) + "'";
            break;
        }
        case DataType::String:
        {
            str += "\"" + std::get<std::string>(_value) + "\"";
            break;
        }
        default:
        {
            str += std::get<std::string>(_value);
            break;
        }
        };

        str += lineTag();
        return str;
    }

    char Const::_toChar(std::string str) const
    {
        for (int i=0; i < str.length(); i++) {
            if (str[i] == '\\' && i < str.length() - 1) {
                i++;
                switch (str[i]) {
                    case 'n':
                        return '\n';
                    case '0':
                        return '\0';
                    default:
                        return str[i];
                }
            }
            else {
                return str[i];
            }
        }
        return '\0';
    }
}