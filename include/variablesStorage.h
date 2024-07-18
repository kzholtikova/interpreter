#pragma once
#include <vector>

class Variable {
private:
    std::string name;
    double value;
public:
    Variable(const std::string& name);
    std::string getName() const;
    double getValue() const;
};


class VariableStorage {
private:
    std::vector<Variable> vars;
public:
    void addVariable(const std::string& str);
    bool find(const std::string& varName);
    double getAt(const std::string &varName);
};