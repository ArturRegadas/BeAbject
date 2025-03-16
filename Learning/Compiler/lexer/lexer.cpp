#include <unordered_map>
#include <utility>
#include <cctype>
#include <vector>
#include <string>
#include <regex>

#include <iostream>
#include <fstream>

#define FIND(a, b) string(a).find(b) != string::npos
#define pb push_back


#define SWHITESPACE " \n\t"

#define CDIGITS 0-9
#define CLETTERS a-zA-Z_
#define CALLKEYS a-zA-Z_0-9
#define COPERATORS +-*/
#define SOPERATORS "+-*/"
#define CKEYWORDS create|if|else
#define SKEYWORDS "create|if|else"
#define CCLASS int|float
#define SCLASS "int|float"
#define CEND ;


using namespace std;

class Lexer
{
    private:
    string line;

    void printTokens(){
        for(auto i: tokens){
            cout << i.first << " " << i.second << endl;
        }
        cout<<"\n";
    }

    public: 
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

    vector<pair<Type, string>> tokens;
    Lexer(string a) : line(a){};

    


    void Tokenize(){
        regex patterns(R"((create|if|else)|(int)|(<-)|([a-zA-Z_][a-zA-Z0-9_]*)|(:)|([0-9]+)|([+*/-])|(;))");      
        auto tokens_begin = sregex_token_iterator(line.begin(), line.end(), patterns);
        auto tokens_end = sregex_token_iterator();

        for(auto i = tokens_begin; i != tokens_end; i++){
            string currentToken = i->str();
            if(FIND(SKEYWORDS, currentToken)){
                tokens.pb({KEYWORD, currentToken});
            }else if (FIND(SCLASS, currentToken)){
                tokens.pb({CLASS, currentToken});
            }else if(currentToken == "<-"){
                tokens.pb({ASSIGN, currentToken});
            }else if(isalpha(currentToken[0])){
                tokens.pb({IDENTIFIER, currentToken});
            }else if(currentToken == ":"){
                tokens.pb({COLON, currentToken});
            }else if(isdigit(currentToken[0])){
                tokens.pb({NUMBER, currentToken});
            }else if(FIND(SOPERATORS, currentToken[0])){
                tokens.pb({OPERATOR, currentToken});
            }else if(isalpha(currentToken[0])){
                tokens.pb({IDENTIFIER, currentToken});
            }else if(currentToken == ";"){
                tokens.pb({END, currentToken});
            }else{
                cout << "Invalid token: " << currentToken << endl;
            }
        }
    }

};


