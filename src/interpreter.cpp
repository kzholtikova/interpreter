#include <iostream>
#include "../include/interpreter.h"
#include "../include/calculator.h"
#include "../include/functionHandler.h"

VariableStorage Interpreter::variables;

void Interpreter::processLine(const std::string& line) {
    if (line.rfind("var ", 0) == 0)
        Interpreter::variables.addVariable(line.substr(4, line.size()));
    else
        std::cout << processExpression(line) << "\n";
}

double Interpreter::processExpression(const std::string& line) {
    std::string trimmedLine = line.substr(line.find_first_not_of(' '), line.find_last_not_of(' ') + 1);
    size_t delimPos;
    if ((delimPos = line.find('(')) != std::string::npos && line.back() == ')')
        return FunctionHandler::applyFunction(line, delimPos);
    else
        return Calculator::calculateExpression(line);
}

