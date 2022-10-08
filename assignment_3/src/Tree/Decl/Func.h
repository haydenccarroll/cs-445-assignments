#pragma once

#include "../Node.h"
#include "../Stmt/Compound.h"
#include "Decl.h"
#include "Parm.h"

#include <map>
#include <string>

namespace Tree::Decl {
/// Function declaration node
class Func : public Decl {
  public:
    Func();
    /// @param lineNum Line number the node appears on
    Func(unsigned lineNum);
    /// Function type is set to void
    /// @param lineNum Line number the node appears on
    /// @param id Function identifier
    /// @param parms Function parameters
    /// @param compoundstmt Function body
    Func(unsigned lineNum, const std::string &id, Node *parms,
         Node *compoundstmt);
    /// @param lineNum Line number the node appears on
    /// @param type Function return type
    /// @param id Function identifier
    /// @param parms Function parameters
    /// @param compoundstmt Function body
    Func(unsigned lineNum, Type type, const std::string &id, Node *parms,
         Node *compoundstmt);

    bool hasParms() const;
    Parm *parms();
    
    virtual std::string toString(bool debugging = false) const override;

  protected:
    Parm *m_parms = nullptr;
    Stmt::Compound *m_compoundStmt = nullptr;
};
} // namespace Tree::Decl