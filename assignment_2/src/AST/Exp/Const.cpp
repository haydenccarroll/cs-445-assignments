#include "Const.h"
#include "../Node.h"

#include <string>
#include <variant>

namespace AST::Exp
{
    Const::Const()
        : Node::Node()
    {
    }

    Const::Const(unsigned linenum)
        : Node::Node(linenum)
    {
    }

    Const::Const(unsigned linenum, Type type, std::string value)
        : Node::Node(linenum),
          m_type(type)
    {
        switch (m_type)
        {
        case Type::String:
        {

            m_value = value.substr(1, value.length() - 2);
            break;
        }
        case Type::Bool:
        {
            m_value = (value == "true");
            break;
        }
        case Type::Char:
        {
            std::string tempStr = value.substr(1, value.length() - 2);
            m_value = _toChar(tempStr);
            break;
        };
        case Type::Int:
        {
            m_value = std::atoi(value.c_str());
            break;
        }
        };
    }

    std::string Const::toString() const
    {
        std::string str = "Const ";

        switch (m_type)
        {
        case Type::Int:
        {
            str += std::to_string(std::get<int>(m_value));
            break;
        }
        case Type::Bool:
        {
            if (std::get<bool>(m_value))
            {
                str += "true";
            }
            else
            {
                str += "false";
            }
            break;
        }
        case Type::Char:
        {
            str += "'" + std::string(1, std::get<char>(m_value)) + "'";
            break;
        }
        case Type::String:
        {
            str += "\"" + std::get<std::string>(m_value) + "\"";
            break;
        }
        default:
        {
            str += std::get<std::string>(m_value);
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