#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <unordered_set>

enum TokenType {
    KEYWORD,    // "create"
    TYPE,       // "int"
    ASSIGN,     // "<-"
    IDENTIFIER, // "x"
    EQUAL,      // "="
    NUMBER,     // "2", "3"
    OPERATOR,   // "+", "*", "/"
    COLON,      // ":"
    SEMICOLON   // ";"
};

struct Token {
    TokenType type;
    std::string value;
};

std::unordered_set<std::string> keywords = {"create", "if", "else"};

std::vector<Token> lexer(const std::string& code) {
    std::vector<Token> tokens;

    // Regex para capturar cada token
    std::regex patterns(R"((create|if|else)|(int)|(<-)|([a-zA-Z_][a-zA-Z0-9_]*)|(:)|([0-9]+)|([+*/-])|(;))");      

    // Iterador para buscar os tokens na string
    auto words_begin = std::sregex_iterator(code.begin(), code.end(), patterns);
    auto words_end = std::sregex_iterator();

    // Iterar sobre cada token encontrado
    for (auto i = words_begin; i != words_end; ++i) {
        std::string match = (*i).str();
        std::cout<<match<<"\n";
        
        if (keywords.count(match)) {
            tokens.push_back({KEYWORD, match});
        } else if (match == "int") {
            tokens.push_back({TYPE, match});
        } else if (match == "<-") {
            tokens.push_back({ASSIGN, match});
        }else if (match == ":") {
            tokens.push_back({COLON, match});
        } else if (match == ";") {
            tokens.push_back({SEMICOLON, match});
        } else if (std::regex_match(match, std::regex("[0-9]+"))) {
            tokens.push_back({NUMBER, match});
            
        } else if (std::regex_match(match, std::regex("[+\\-*/]"))) {
          tokens.push_back({OPERATOR, match});
        } else {
            tokens.push_back({IDENTIFIER, match});
            }
        }
            
    return tokens;
    }

void printTokens(const std::vector<Token>& tokens){
    for (const auto& token : tokens) {
        std::cout << "Token: " << token.value << std::endl;
    }
}

int main() {
    std::string code1 = "create int<- x: 2+3*4;";
    std::string code2 = "create int<-dads:21+3;";

    std::cout << "---- Código 1 ----\n";
    printTokens(lexer(code1));

    std::cout << "\n---- Código 2 ----\n";
    printTokens(lexer(code1));

    return 0;
}
