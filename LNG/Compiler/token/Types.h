#ifndef TYPES_H
#define TYPES_H

struct Token {
    enum Type{
        KEYWORD,    //create|if|else
        CLASS,      //int|double|bool
        ASSIGN,     // <-
        IDENTIFIER, //varible name
        COLON,      //=
        NUMBER,     //0-9
        LEFT_PAREN, //(
        RIGHT_PAREN, //)
        OPERATOR,   //+-/*
        END         //;
    };
};

#endif // TYPES_H