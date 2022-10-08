#pragma once

#include <string>

class Message {
  public:
    enum class Type { Error, Warning };

    Message(Type type, const std::string &content);
    Type type() const;
    std::string content() const;

    static unsigned numWarnings();
    static unsigned numErrors();

  private:
    static unsigned s_numerrors;
    static unsigned s_numwarnings;

    Type m_type;
    std::string m_content;
};