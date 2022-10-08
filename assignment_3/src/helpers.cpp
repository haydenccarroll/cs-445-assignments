#include <iostream>
#include <string>
#include <stdexcept>

#include "helpers.h"

namespace helpers {

std::string remove_quotes(std::string str) {
    return str.substr(1, str.size() - 2);
}

char get_char(const std::string &s, int &index) {
    if (index >= s.length()) {
        throw std::runtime_error("idx out of bounds");
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

char make_char(const std::string &str, int lineNumber) {
    int idx = 0;
    char c = get_char(str, idx);
    int len = 0;
    for (unsigned i = 0; i < str.length(); i++) {
        if (str[i] == '\\') {
            if (i == str.length() - 1) {
                break;
            } else {
                i++;
            }
        }
        len++;
    }
    if (len > 1) {
        std::cout << "WARNING(" + std::to_string(lineNumber) +
                         "): character is " + std::to_string(len) +
                         " characters long and not a single character: ''" +
                         str + "''. The first char will be used.";
    }

    return c;
}
}