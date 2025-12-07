#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

namespace jsonparse {
    enum class TokenType {
        TOKEN_LBRACE,      // {
        TOKEN_RBRACE,      // }
        TOKEN_LBRACKET,    // [
        TOKEN_RBRACKET,    // ]
        TOKEN_COLON,       // :
        TOKEN_COMMA,       // ,
        TOKEN_STRING,      // "hello"
        TOKEN_NUMBER,      // 123, 45.67
        TOKEN_TRUE,        // true
        TOKEN_FALSE,       // false
        TOKEN_NULL,        // null
        TOKEN_EOF
    };

    struct Token {
        TokenType type;
        std::string text;
    };

    std::vector<Token> tokenize(const std::string& input) {
        std::vector<Token> outTokens;
        size_t i = 0;
        
        while (i < input.length()) {
            char currentChar = input[i];
            
            // Skip whitespace
            if (std::isspace(currentChar)) {
                i++;
                continue;
            }
            
            // Parse strings
            if (currentChar == '"') {
                size_t start = i;
                i++; // Skip opening quote
                std::string result;
                
                while (i < input.length() && input[i] != '"') {
                    if (input[i] == '\\' && i + 1 < input.length()) {
                        i++;
                        switch (input[i]) {
                            case '"': result += '"'; break;
                            case '\\': result += '\\'; break;
                            case 'n': result += '\n'; break;
                            case 't': result += '\t'; break;
                            case 'r': result += '\r'; break;
                            default: result += input[i];
                        }
                    } else {
                        result += input[i];
                    }
                    i++;
                }
                
                if (i >= input.length()) {
                    throw std::runtime_error("Unterminated string at position " + std::to_string(start));
                }
                
                i++;
                outTokens.push_back({TokenType::TOKEN_STRING, result});
                continue;
            }
            
            if (std::isdigit(currentChar) || (currentChar == '-' && i + 1 < input.length() && std::isdigit(input[i + 1]))) {
                size_t start = i;
                
                if (currentChar == '-') {
                    i++;
                }
                
                while (i < input.length() && std::isdigit(input[i])) {
                    i++;
                }
                
                if (i < input.length() && input[i] == '.') {
                    i++;
                    while (i < input.length() && std::isdigit(input[i])) {
                        i++;
                    }
                }
                
                // Exponent part (e or E)
                if (i < input.length() && (input[i] == 'e' || input[i] == 'E')) {
                    i++;
                    if (i < input.length() && (input[i] == '+' || input[i] == '-')) {
                        i++;
                    }
                    while (i < input.length() && std::isdigit(input[i])) {
                        i++;
                    }
                }
                
                outTokens.push_back({TokenType::TOKEN_NUMBER, input.substr(start, i - start)});
                continue;
            }
            
            // Parse keywords: true, false, null
            if (std::isalpha(currentChar)) {
                size_t start = i;
                while (i < input.length() && std::isalpha(input[i])) {
                    i++;
                }
                std::string keyword = input.substr(start, i - start);
                
                if (keyword == "true") {
                    outTokens.push_back({TokenType::TOKEN_TRUE, "true"});
                } else if (keyword == "false") {
                    outTokens.push_back({TokenType::TOKEN_FALSE, "false"});
                } else if (keyword == "null") {
                    outTokens.push_back({TokenType::TOKEN_NULL, "null"});
                } else {
                    throw std::runtime_error("Unknown keyword: " + keyword);
                }
                continue;
            }
            
            // Single character tokens
            switch (currentChar) {
                case '{':
                    outTokens.push_back({TokenType::TOKEN_LBRACE, "{"});
                    i++;
                    continue;
                case '}':
                    outTokens.push_back({TokenType::TOKEN_RBRACE, "}"});
                    i++;
                    continue;
                case '[':
                    outTokens.push_back({TokenType::TOKEN_LBRACKET, "["});
                    i++;
                    continue;
                case ']':
                    outTokens.push_back({TokenType::TOKEN_RBRACKET, "]"});
                    i++;
                    continue;
                case ':':
                    outTokens.push_back({TokenType::TOKEN_COLON, ":"});
                    i++;
                    continue;
                case ',':
                    outTokens.push_back({TokenType::TOKEN_COMMA, ","});
                    i++;
                    continue;
                default:
                    throw std::runtime_error("Unexpected character: " + std::string(1, currentChar));
            }
        }
        
        outTokens.push_back({TokenType::TOKEN_EOF, ""});
        return outTokens;
    }
}
