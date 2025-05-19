#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

map<string, int> variables;

vector<string> tokenize(const string& code) {
    istringstream stream(code);
    vector<string> tokens;
    string token;
    while (stream >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

void processAssignment(const vector<string>& tokens) {
    if (tokens.size() == 3 && tokens[1] == "=") {
        int value = stoi(tokens[2]);
        variables[tokens[0]] = value;
    }
}

void processPrint(const vector<string>& tokens) {
    if (tokens.size() == 2 && tokens[0] == "print") {
        string varName = tokens[1];
        if (variables.find(varName) != variables.end()) {
            cout << variables[varName] << endl;
        } else {
            cout << "Error: Variable not defined" << endl;
        }
    }
}

void interpret(const string& code) {
    istringstream stream(code);
    string line;
    while (getline(stream, line)) {
        auto tokens = tokenize(line);
        if (tokens.empty()) continue;

        if (tokens[0] == "print") {
            processPrint(tokens);
        } else {
            processAssignment(tokens);
        }
    }
}

int main() {
    string code =
        "x = 5\n"
        "y = 10\n"
        "print x\n"
        "print y\n";

    interpret(code);

    return 0;
}
