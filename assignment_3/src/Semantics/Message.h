#pragma once

#include <string>

class Message {
  public:
    enum class MsgType { Error, Warning };

    Message(MsgType type, const std::string &content);
    MsgType type() const;
    std::string content() const;

    static unsigned numWarnings();
    static unsigned numErrors();

  private:
    static unsigned s_numerrors;
    static unsigned s_numwarnings;

    MsgType m_type;
    std::string m_content;
};
