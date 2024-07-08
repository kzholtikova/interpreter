#pragma once
#include <string>
#include "token.h"

class Interpreter {
public:
    static void processLine(const std::string& line);
};