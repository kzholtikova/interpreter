#pragma once
#include <string>
#include <map>
#include <functional>

typedef std::function<double(const std::vector<double>&)> function;

class FunctionHandler {
public:
    static std::map<std::string, function> funcStorage;

    static double applyFunction(const std::string& line, size_t argsPos);
    static std::vector<double> parseArguments(const std::string& argsStr);
};
