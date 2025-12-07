#include <string>
namespace exprparse{
    enum class TokenType {
        TOKEN_NUMBER,
        TOKEN_OPERATOR,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
    };

    struct Token{
        TokenType type;
        std::string text;
    }

    bool std::vector<Token> tokenize(const std::string& input){
        std::vector<Token> outToken
        size_t i = 0;
        while(i < input.length()){
            char currentChar = input[i];
            if(std::isspace(currentChar)){
                i++;
                continue;
            }
            if(std::isdigit(currentChar)){
                int start = i;
                while(i < input.length() && std::isdigit(input[i])){
                    i++;
                }
                outTokens.push_back({TokenType::TOKEN_NUMBER, input.substr(start, i - start)});
                continue;
            }
            if(currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/'){
                outTokens.push_back({TokenType::TOKEN_OPERATOR, std::string(1, currentChar)});
                i++;
                continue;
            }
            if(currentChar == '('){
                outTokens.push_back({TokenType::TOKEN_LPAREN, "("});
                i++;
                continue;
            }
            if(currentChar == ')'){
                outTokens.push_back({TokenType::TOKEN_RPAREN, ")"});
                i++;
                continue;
            }
        }
    }

}