#include <iostream>
#include "../include/interpreter.h"
#include "../include/calculator.h"

void Interpreter::processLine(const std::string& line) {
    double result = Calculator::calculateExpression(line);
    std::cout << result << "\n";
}
