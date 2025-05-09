#ifndef TYPES_H
#define TYPES_H

struct Token {
    enum Type{
        KEYWORD,
        CLASS,
        ASSIGN,
        IDENTIFIER,
        COLON,
        NUMBER,
        OPERATOR,
        END
    };
};

#endif // TYPES_H