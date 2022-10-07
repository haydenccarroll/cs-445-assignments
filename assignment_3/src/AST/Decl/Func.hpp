#pragma once

#include "../Node.hpp"
#include "../Stmt/Compound.hpp"
#include "Decl.hpp"
#include "Parm.hpp"

#include <map>
#include <string>

namespace AST::Decl {
/// Function declaration node
class Func : public Decl {
  public:
    Func();
    /// @param linenum Line number the node appears on
    Func(unsigned linenum);
    /// Function type is set to void
    /// @param linenum Line number the node appears on
    /// @param id Function identifier
    /// @param parms Function parameters
    /// @param compoundstmt Function body
    Func(unsigned linenum, const std::string &id, Node *parms,
         Node *compoundstmt);
    /// @param linenum Line number the node appears on
    /// @param type Function return type
    /// @param id Function identifier
    /// @param parms Function parameters
    /// @param compoundstmt Function body
    Func(unsigned linenum, Type type, const std::string &id, Node *parms,
         Node *compoundstmt);

    bool hasParms() const;
    Parm *parms();
    
    virtual std::string toString(bool debugging = false) const override;

  protected:
    Parm *m_parms = nullptr;
    Stmt::Compound *m_compoundStmt = nullptr;
};
} // namespace AST::Decl