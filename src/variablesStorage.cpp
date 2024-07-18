#include "../include/variablesStorage.h"
#include "../include/interpreter.h"

Variable::Variable(const std::string& str) {
    size_t delimPos = str.find(' = ');
    if (delimPos != std::string::npos && delimPos + 3 < str.size()) {
        std::string varName = str.substr(0, delimPos);
        if (std::all_of(name.begin(), name.end(), ::isalpha)) {
            name = varName;
            std::string valueStr = str.substr(delimPos + 3);
            value = Interpreter::processExpression(valueStr);
        } else
            throw std::invalid_argument("Invalid variable name");
    } else
        throw std::invalid_argument("Invalid variable definition syntax");
}

std::string Variable::getName() const {
    return name;
}

double Variable::getValue() const {
    return value;
}

void VariableStorage::addVariable(const std::string& str) {
    vars.emplace_back(str);
}

bool VariableStorage::find(const std::string& varName) {
    return std::any_of(vars.begin(), vars.end(), [&varName](const Variable& var) {
        return var.getName() == varName;
    });
}

double VariableStorage::getAt(const std::string &varName) {
    for (const auto& var : vars) {
        if (var.getName() == varName)
            return var.getValue();
    }
    throw std::invalid_argument("Variable not found");
}
