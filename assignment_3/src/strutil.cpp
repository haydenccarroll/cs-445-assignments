#include <iostream>
#include <string>
#include <stdexcept>

#include "strutil.hpp"

std::string strutil::remove_quotes(std::string s) {
    return s.erase(0, 1).erase(s.length() - 1, s.length());
}

int strutil::str_len(const std::string &s) {
    int counter = 0;
    for (unsigned i = 0; i < s.length(); i++) {
        if (s[i] == '\\') {
            if (i == s.length() - 1) {
                return counter;
            } else {
                i++;
            }
        }
        counter++;
    }

    return counter;
}

char strutil::get_char(const std::string &s, int &index) {
    if (index >= s.length()) {
        throw std::runtime_error("getChar(): index out of bounds");
    }

    char c = '\0';

    if (s[index] == '\\') {
        if (s.length() - index > 1) {
            switch (s[index + 1]) {
            case 'n':
                c = '\n';
                break;
            case '0':
                c = '\0';
                break;
            default:
                c = s[index + 1];
                break;
            }
        }
        index += 2;
    } else {
        c = s[index];
        index++;
    }
    return c;
}

std::string strutil::make_str(const std::string &str) {
    std::string str2;
    for (int i = 0; i < str.length();) {
        str2 += get_char(str, i);
    }
    return str2;
}

char strutil::make_char(const std::string &str) {
    int index = 0;
    return get_char(str, index);
}

char strutil::make_char(const std::string &str, int lineNumber) {
    char c = make_char(str);
    int strlen = str_len(str);
    if (strlen > 1) {
        std::cout << "WARNING(" + std::to_string(lineNumber) +
                         "): character is " + std::to_string(strlen) +
                         " characters long and not a single character: ''" +
                         str + "''. The first char will be used.";
    }

    return c;
}