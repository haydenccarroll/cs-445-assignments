#include "Const.h"
#include "../../helpers.h"
#include "../Node.h"
#include "Exp.h"

#include <string>
#include <variant>

namespace Tree::Exp {
Const::Const() : Exp::Exp() {}

Const::Const(unsigned lineNum) : Exp::Exp(lineNum, ExpType::Const) {
    m_typeInfo.isConst = true;
}

Const::Const(unsigned lineNum, SuperDataType typeInfo, std::string value)
    : Exp::Exp(lineNum, ExpType::Const) {
    m_typeInfo = typeInfo;
    m_typeInfo.isConst = true;
    switch (m_typeInfo.type.value()) {
    case DataType::Bool: {
        m_value = (value == "true");
        break;
    }
    case DataType::Char: {
        if (m_typeInfo.isArray) {
            m_value = helpers::remove_quotes(value);
            break;
        } else {
            m_value =
                helpers::make_char(helpers::remove_quotes(value), m_lineNum);
            break;
        }
    };
    case DataType::Int: {
        m_value = std::atoi(value.c_str());
        break;
    }
    };
}

std::string Const::toString(bool debugging) const {
    std::string str = "Const ";

    switch (m_typeInfo.type.value()) {
    case DataType::Int: {
        str += std::to_string(std::get<int>(m_value));
        break;
    }
    case DataType::Bool: {
        if (std::get<bool>(m_value)) {
            str += "true";
        } else {
            str += "false";
        }
        break;
    }
    case DataType::Char: {
        if (m_typeInfo.isArray) {
            str += "is array \"" + std::get<std::string>(m_value) + "\"";
            break;
        } else {
            str += "'" + std::string(1, std::get<char>(m_value)) + "'";
            break;
        }
    }
    default: {
        str += std::get<std::string>(m_value);
        break;
    }
    };

    if (debugging &&
        !(m_typeInfo.type.value() == DataType::Char && m_typeInfo.isArray)) {
        str += typeTag();
    }

    str += lineTag();
    return str;
}
} // namespace Tree::Exp