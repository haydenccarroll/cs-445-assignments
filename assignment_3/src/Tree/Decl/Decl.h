#pragma once

#include "../Node.h"

#include <map>
#include <optional>
#include <string>

// Namespace for declaration nodes
namespace Tree::Decl {

// Base declaration node
class Decl : public Node {
  public:
    Decl();
    // param lineNum - Line number the node appears on
    Decl(unsigned lineNum);
    Decl(unsigned lineNum, DeclType declType);
    
    const std::string &id() const;
    const DeclType &declType() const;
    SuperDataType &typeInfo();
    const SuperDataType &typeInfo() const;

    virtual bool is(DeclType t) const override;
    // Set the node and its sibling's types to the provided type
    // param type - Type to set
    virtual void setType(DataType type);

  protected:
    DeclType m_declType;
    SuperDataType m_typeInfo;
    std::string m_id;

    virtual std::string typeTag() const override;
};
} // namespace Tree::Decl