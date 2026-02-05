#include<iostream>
#include<sstream>
#include<string>
#include <cctype>

namespace ansi {
bool isoctaldigit(char c) {
    return '0' <= c && c < '8';
}


std::ostream& clearScreen(std::ostream &os) {
    return os << "\x1b[2J";
}

std::ostream &clearScreenFromCursor(std::ostream &os) {
    return os << "\x1b[0J";
}

std::ostream &clearLine(std::ostream &os) {
    return os << "\x1b[K";
}


std::ostream& save(std::ostream &os) {
    return os << "\x1b"<<"7";
}

std::ostream& load(std::ostream &os) {
    return os << "\x1b"<<"8";
}

std::string moveCursor(int line, int column) {
    std::stringstream ss;
    ss << "\x1b[" << line << ';' << column << 'H';
    return ss.str();
}

std::string unescape(std::string& input) {
    std::string result;
    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] == '\\' && i + 1 < input.size()) {
            char type = input[i + 1];
            
            if (type == 'x' || type == 'u' || type == '0') {
                int max_digits;
                switch (type) {
                    case 'x': max_digits=2; break;
                    case 'u': max_digits=4; break;
                    case '0': max_digits=3; break;
                }
                
                size_t start = i + 2;
                size_t count = 0;
                while (count < max_digits && (start + count) < input.size() && 
                       ((type=='x' || type=='u') && std::isxdigit(static_cast<unsigned char>(input[start + count]))
                        || type=='0' && isoctaldigit(input[start+count]))
                    
                    ) {
                    count++;
                }

                if (count > 0) {
                    std::string numStr = input.substr(start, count);
                    int value = type=='0' ? std::stoi(numStr, nullptr, 8) : std::stoi(numStr, nullptr, 16);
                    
                    if (value <= 0x7F) {
                        // 1-byte ASCII
                        result += static_cast<char>(value);
                    } else if (value <= 0x7FF) {
                        // 2-byte sequence
                        result += static_cast<char>(0xC0 | (value >> 6));
                        result += static_cast<char>(0x80 | (value & 0x3F));
                    } else if (value <= 0xFFFF) {
                        // 3-byte sequence (standard for \uXXXX)
                        result += static_cast<char>(0xE0 | (value >> 12));
                        result += static_cast<char>(0x80 | ((value >> 6) & 0x3F));
                        result += static_cast<char>(0x80 | (value & 0x3F));
                    } else {
                        // 4-byte sequence
                        result += static_cast<char>(0xF0 | (value >> 18));
                        result += static_cast<char>(0x80 | ((value >> 12) & 0x3F));
                        result += static_cast<char>(0x80 | ((value >> 6) & 0x3F));
                        result += static_cast<char>(0x80 | (value & 0x3F));
                    }
                    
                    i += 1 + count; 
                } else {
                    // No digits found after \x or \u
                    // Do nothing
                }
            } else {
                switch (type) {
                    case 'a': result += '\a'; break;
                    case 'b': result += '\b'; break;
                    case 't': result += '\t'; break;
                    case 'n': result += '\n'; break;
                    case 'v': result += '\v'; break;
                    case 'f': result += '\f'; break;
                    case 'r': result += '\r'; break;
                    case 'e': result += '\e'; break;
                    case '\\': result += '\\'; break;
                    default:  {result += '\\'; result += type;} break;
                }
                i++;
            }
        } else {
            result += input[i];
        }
    }
    return result;
}


}