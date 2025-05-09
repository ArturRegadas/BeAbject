#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <map>

#include "ASTNode.h"
#include "../token/Types.h"

#include "../lexer/lexer.h"

#define F first
#define S second
using namespace std;


class Parser : private Token{
    private:
    //          .first, ,second
    vector<pair<Type, string>> tokens;
    size_t pos = 0;
    
    

    std::pair<Type, std::string> current() const {
        return tokens[pos];
    }

    void advance() {
        if (pos < tokens.size()) pos++;
    }

    bool match(Type type) {
        if (current().first == type) {
            advance();
            return true;
        }
        return false;
    }

    unique_ptr<ASTNode> parseExpression() {
        return parseAddSub();
    }

    unique_ptr<ASTNode> parseAddSub() {
        auto node = parseMulDiv();
        while (current().F == Type::OPERATOR &&
              (current().S == "+" || current().S == "-")) {
            char op = current().S[0];
            advance();
            auto right = parseMulDiv();
            node = make_unique<OperatorNode>(op, move(node), move(right));
        }
        return node;
    }

    unique_ptr<ASTNode> parseMulDiv() {
        auto node = parseFactor();
        while (current().F == Type::OPERATOR &&
              (current().S == "*" || current().S == "/")) {
            char op = current().S[0];
            advance();
            auto right = parseFactor();
            node = make_unique<OperatorNode>(op, move(node), move(right));
        }
        return node;
    }

    unique_ptr<ASTNode> parseFactor() {
        if (match(Type::NUMBER))
            return make_unique<NumberNode>(stoi(tokens[pos - 1].S));
        if (match(Type::IDENTIFIER))
            return make_unique<VariableNode>(tokens[pos - 1].S);
        throw runtime_error("Fator inválido");
    }

    public:
    Parser(vector<pair<Type, string>> t) : tokens(t) {}

    unique_ptr<ASTNode> parse() {
        if (!match(Type::KEYWORD))
            throw runtime_error("Esperado 'create'");
        if (!match(Type::CLASS))
            throw runtime_error("Esperado tipo");
        if (!match(Type::ASSIGN))
            throw runtime_error("Esperado '<-'");
        if (!match(Type::IDENTIFIER))
            throw runtime_error("Esperado nome de variável");
        string var = tokens[pos - 1].S;
        if (!match(Type::COLON))
            throw runtime_error("Esperado ':'");

        auto expr = parseExpression();

        if (!match(Type::END))
            throw runtime_error("Esperado ';'");

        return make_unique<AssinmentNode>(var, move(expr));
    }
};

int main(){
    string code = "create int<- x: 2+3*4;";
    Lexer lexer(code);
    auto tokens = lexer.tokenize();

    Parser parser(tokens);
    auto ast = parser.parse();

    ast->print();

}
