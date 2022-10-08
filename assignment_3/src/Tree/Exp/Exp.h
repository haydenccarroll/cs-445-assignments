#pragma once

#include "../Node.h"

// Namespace for expression nodes
namespace Tree::Exp {

class Exp : public Node {
  public:
    Exp();
    Exp(unsigned);
    Exp(unsigned, ExpType);
    
    const ExpType &expType() const;

    virtual void setType(SuperDataType);
    virtual const SuperDataType &typeInfo() const;
    virtual SuperDataType &typeInfo();
    virtual bool is(ExpType) const override;

  protected:
    SuperDataType m_typeInfo;
    ExpType m_expType;

    virtual std::string typeTag() const override;
};
} // namespace Tree::Exp