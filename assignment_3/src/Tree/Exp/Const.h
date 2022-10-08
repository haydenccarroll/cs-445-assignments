#pragma once

#include "../Node.h"
#include "Exp.h"

#include <variant>

namespace Tree::Exp {
// Node for constants
class Const : public Exp {
  public:
    Const();
    // param lineNum - Line number the node appears on
    Const(unsigned lineNum);
    // param lineNum - Line number the node appears on
    // param Type - Type of the constant
    // param data - String value of the data
    Const(unsigned lineNum, SuperDataType typeInfo, std::string data);
    
    virtual std::string toString(bool debugging = false) const override;

  protected:
    std::variant<int, bool, char, std::string> m_value;
};
} // namespace Tree::Exp