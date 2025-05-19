#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <map>

#include "types.h"

struct Lexeme {
    Token::Type type;
    std::string value;
};

// Par Token::Type ↔ regex pattern
const std::vector<std::pair<Token::Type, std::string>> tokenPatterns = {
    {Token::DECLARATION,         R"(%%)"},
    {Token::ASSIGN,              R"(<-)"},
    {Token::EQUAL,               R"(==)"},
    {Token::NOT_EQUAL,           R"(!=)"},
    {Token::CONDIDITIONAL_ELSEIF,R"(\?>)"},
    {Token::CONDIDITIONAL_ELSE,  R"(:>)"},
    {Token::CONDIDITIONAL_IF,    R"(\?)"},
    {Token::OUTPUT,              R"(@)"},
    {Token::MATH_OPERATOR,       R"([\+\-\*/])"},
    {Token::GREATER,             R"(>)"},
    {Token::LESS,                R"(<)"},
    {Token::NOT,                 R"(!)"},
    {Token::COLON,               R"(:)"},
    {Token::SEMICOLON,           R"(;)"},
    {Token::LBRACE,              R"(\{)"},
    {Token::RBRACE,              R"(\})"},
    {Token::LPAREN,              R"(\()"},
    {Token::RPAREN,              R"(\))"},
    {Token::TYPE_NUM,            R"(\bnum\b)"},
    {Token::TYPE_STR,            R"(\bstr\b)"},
    {Token::TYPE_BOOL,           R"(\bbool\b)"},
    {Token::BOOL_VAL,            R"(\b(true|false)\b)"},
    {Token::NUMBER,              R"(\b\d+\b)"},
    {Token::STRING,              R"("(?:\\.|[^"\\])*")"},
    {Token::IDENTIFIER,          R"([a-zA-Z_][a-zA-Z0-9_]*)"}
};

std::vector<Lexeme> tokenize(const std::string& input) {
    std::vector<Lexeme> tokens;
    std::string remaining = input;

    std::smatch match;
    while (!remaining.empty()) {
        // Remove espaços no início
        if (std::regex_search(remaining, match, std::regex(R"(^\s+)"))) {
            remaining = match.suffix().str();
            continue;
        }

        bool matched = false;
        for (const auto& [type, pattern] : tokenPatterns) {
            std::regex regex("^" + pattern);
            if (std::regex_search(remaining, match, regex)) {
                std::string value = match.str();
                tokens.push_back({type, value});
                remaining = match.suffix().str();
                matched = true;
                break;
            }
        }

        if (!matched) {
            std::cerr << "Erro léxico: símbolo inválido próximo de: " << remaining << std::endl;
            break;
        }
    }

    tokens.push_back({Token::EOF_TOKEN, ""});
    return tokens;
}
