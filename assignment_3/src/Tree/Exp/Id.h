#pragma once

#include "../Node.h"
#include "Exp.h"

#include <string>

namespace Tree::Exp {
// Identifier node
class Id : public Exp {
  public:
    Id();
    // param lineNum - Line number the node appears on
    Id(unsigned lineNum);
    // param lineNum - Line number the node appears on
    // param id - String identifier
    Id(unsigned lineNum, const std::string &id);

    const std::string &id() const;
    
    virtual std::string toString(bool debugging = false) const override;

  protected:
    std::string m_id;
};
} // namespace Tree::Exp