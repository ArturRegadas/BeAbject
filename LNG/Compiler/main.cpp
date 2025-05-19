#include <fstream>
#include <iostream>
#include <string>
#include "token/Types.h"
#include "lexer/lexer.h"
#include "Parser/Parser.h"

using namespace std;

int main(int argc, char* argv[]){
    ifstream file(argv[1]);
    string line;
    
    if (file.is_open()) {
        while (getline(file, line, ';')) {
            line+=";";
            Lexer lexer(line);
            vector<pair<Token::Type, string>> tokens = lexer.tokenize();
            Parser parser(tokens);
            auto ast = parser.parse();
            cout << "#include <stdio.h>\n";
            cout << "int main() {\n";
            cout << "    " << ast->generateCode() << "\n";
            cout << "    return 0;\n";
            cout << "}\n";

        }
        file.close();
    } else {
        cerr << "Erro ao abrir o arquivo!\n";
    }

}