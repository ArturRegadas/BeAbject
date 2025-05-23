#ifndef ASTNODE_H
#define ASTNODE_H

#include <vector>
#include <string>
#include <memory>

#include<iostream>

using namespace std;

//os ultimos nodos sao os valores, os demais operacoes
class ASTNode{
    public:
    virtual void print(int indent = 0) const = 0;
    virtual string generateCode() const = 0;
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

    string generateCode() const override {
        return to_string(value);
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
        cout<< "OperatorNode: " << Operator << "\n";
        left->print(indent+1);
        right->print(indent+1);
    }

    string generateCode() const override {
        return "(" + left->generateCode() + " " + string(1, Operator) + " " + right->generateCode() + ")";
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

    string generateCode() const override {
        return variable;
    }



};

class AssinmentNode : public ASTNode{
    private:
    string variable;
    unique_ptr<ASTNode> value;

    public:
    AssinmentNode(string v, unique_ptr<ASTNode> p) :
    variable(v), value(move(p)) {}

    void print(int indent = 0)const override{
        for(int i =0;i<indent;i++)cout<<" ";
        cout<<"Assinment: "<<variable<<"\n";
        value->print(indent + 2);
    }

    string generateCode() const override{
        return "int " + variable + " = " + value->generateCode() + ";";
    }

};

#endif