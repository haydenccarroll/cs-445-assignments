#pragma once

#include "../Node.hpp"

/// Namespace for expression nodes
namespace AST::Exp {

class Exp : public Node {
  public:
    Exp();
    Exp(unsigned);
    Exp(unsigned, ExpType);
    
    const ExpType &expType() const;

    virtual void setType(TypeInfo);
    virtual const TypeInfo &typeInfo() const;
    virtual TypeInfo &typeInfo();
    virtual bool is(ExpType) const override;

  protected:
    TypeInfo m_typeInfo;
    ExpType m_expType;

    virtual std::string typeTag() const override;
};
} // namespace AST::Exp