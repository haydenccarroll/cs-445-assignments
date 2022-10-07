#pragma once

#include "../Node.hpp"
#include "Decl.hpp"

#include <map>
#include <string>

namespace AST::Decl {
/// Parameter declaration node
class Parm : public Decl {
  public:
    Parm();
    /// @param lineNum Line number the node appears on
    Parm(unsigned lineNum);
    /// @param lineNum Line number the node appears on
    /// @param id Parameter name
    /// @param isArray Whether or not the parameter is an array
    Parm(unsigned lineNum, const std::string &id, bool isArray);
    
    virtual std::string toString(bool debugging = false) const override;
};
} // namespace AST::Decl