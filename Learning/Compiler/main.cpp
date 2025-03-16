#include <fstream>
#include <iostream>
#include <string>
#include <lexer/lexer.cpp>



using namespace std;

int main(int argc, char* argv[]){
    ifstream file(argv[1]);
    std::string line;
    
    if (file.is_open()) {
        while (getline(file, line, ';')) {
            line+=";";
            Lexer lexer(line);
            lexer.Tokenize();
            //lexer.printTokens();
        }
        file.close();
    } else {
        cerr << "Erro ao abrir o arquivo!\n";
    }

}