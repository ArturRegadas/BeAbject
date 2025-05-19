#ifndef TYPES_H
#define TYPES_H

struct Token {
    enum Type {
        // SYMBOLS
        DECLARATION,        // %% 
        ASSIGN,             // <- 
        MATH_OPERATOR,      // +-/* 
        COLON,              // :
        SEMICOLON,          // ;
        CONDIDITIONAL_IF,           // ? (if)
        CONDIDITIONAL_ELSEIF,           // ?> (elseif)
        CONDIDITIONAL_ELSE,           // :> (if)
        LBRACE,             // {
        RBRACE,             // }
        LPAREN,             // (
        RPAREN,             // )
        OUTPUT,             // @ (print)

        // LOGIC OPERATORS
        GREATER,         // >
        LESS,            // <
        EQUAL,           // ==
        NOT_EQUAL,       // !=
        NOT,

        // TYPES
        TYPE_NUM,        // num
        TYPE_STR,        // str
        TYPE_BOOL,       // bool

        IDENTIFIER,      // nome de variável
        NUMBER,          // 123
        STRING,          // "abc"
        BOOL_VAL,        // true/false

        // Final
        EOF_TOKEN
    };
};

#endif // TYPES_H
