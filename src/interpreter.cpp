#include <iostream>
#include "../include/interpreter.h"
#include "../include/calculator.h"
#include "../include/functionHandler.h"

void Interpreter::processLine(const std::string& line) {
    double result;
    size_t delimPos;
    if (std::isdigit(line[0]))
        result = Calculator::calculateExpression(line);
    else if ((delimPos = line.find('(')) != std::string::npos && line.back() == ')')
        result = FunctionHandler::applyFunction(line, delimPos);
    else
        throw std::invalid_argument("Invalid syntax");

    std::cout << result << "\n";
}
