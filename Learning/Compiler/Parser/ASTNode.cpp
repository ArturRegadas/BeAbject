#include <vector>
#include <string>
#include <memory>

#include<iostream>

using namespace std;

//os ultimos nodos sao os valores, os demais operacoes
class ASTNode{
    public:
    virtual void print(int indent = 0) const = 0;
    virtual ~ASTNode() {}
};
class NumberNode : public ASTNode{
    private:
    int value;

    public:
    NumberNode(int a) : value(a) {}
    //fdel
    void print(int indent = 0) const override {
        for(int i =0;i<indent;i++)cout<<" ";
        cout<< "NumberNode: " << value << "\n";
    }
};
class OperatorNode : public ASTNode{
    private:
    char Operator;
    unique_ptr<ASTNode> left;
    unique_ptr<ASTNode> right;

    public:
    OperatorNode(char o, unique_ptr<ASTNode> l,unique_ptr<ASTNode> r):
        Operator(o) , left(move(l)) , right(move(r)){}
    //fdel
    void print(int indent = 0) const override {
        for(int i =0;i<indent;i++)cout<<" ";
        cout<< "NumberNode: " << Operator << "\n";
        left->print(indent+1);
        right->print(indent+1);
    }

};

class VariableNode : public ASTNode{
    private:
    string variable;

    public:
    VariableNode(string v): variable(v) {}

    void print(int indent = 0) const override {
        for(int i =0;i<indent;i++)cout<<" ";
        cout<<"Variable: "<<variable<<"\n";
    }
};

class AssinmentNode : public ASTNode{

};