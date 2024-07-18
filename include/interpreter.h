#pragma once
#include <string>
#include "token.h"
#include "variablesStorage.h"

class Interpreter {
public:
    static VariableStorage variables;

    static void processLine(const std::string& line);
    static double processExpression(const std::string& line);
};