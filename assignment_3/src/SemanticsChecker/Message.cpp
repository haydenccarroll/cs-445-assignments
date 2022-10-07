#include "Message.hpp"

unsigned Message::s_numerrors = 0;
unsigned Message::s_numwarnings = 0;

Message::Message(Type type, const std::string &content)
    : m_type(type), m_content(content) {
    if (type == Type::Error) {
        s_numerrors++;
    } else {
        s_numwarnings++;
    }
}

Message::Type Message::type() const { return m_type; }

std::string Message::content() const { return m_content; }

unsigned Message::numErrors() { return s_numerrors; }

unsigned Message::numWarnings() { return s_numwarnings; }