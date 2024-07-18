#include <iostream>
#include <sstream>
#include "../include/functionHandler.h"

std::map<std::string, function> FunctionHandler::funcStorage = {
        {"min", [](const std::vector<double>& args) { return std::min(args[0], args[1]); }},
        {"max", [](const std::vector<double>& args) { return std::max(args[0], args[1]); }},
        {"pow", [](const std::vector<double>& args) { return std::pow(args[0], args[1]); }},
        {"abs", [](const std::vector<double>& args) { return std::abs(args[0]); }}
};

double FunctionHandler::applyFunction(const std::string& line, size_t argsPos) {
    std::string funcName = line.substr(0, argsPos);
    if (funcStorage.count(funcName)) {
        std::vector<double> args = parseArguments(line.substr(argsPos + 1, line.size() - argsPos - 2));
        return funcStorage.at(funcName)(args);
    } else
        throw std::invalid_argument("Unknown function: " + funcName);
}

std::vector<double> FunctionHandler::parseArguments(const std::string& argsStr) {  // format: "a, b"
    std::vector<double> args;
    std::stringstream ss;
    int parenthesesCounter = 0;

    for (char ch : argsStr) {
        if (ch == ',' && parenthesesCounter == 0) {
            args.push_back(evaluateArgument(ss.str()));
            ss.str(std::string());
            ss.clear();
        } else {
            if (ch == '(')
                parenthesesCounter++;
            else if (ch == ')')
                parenthesesCounter--;
            ss << ch;
        }
    }

    if (!ss.str().empty())
        args.push_back(evaluateArgument(ss.str()));
    return args;
}

double FunctionHandler::evaluateArgument(std::string arg) {  // ss.str() returns a temporary std::string object, can be used only with const
    arg.erase(arg.begin(), std::find_if_not(arg.begin(), arg.end(), ::isspace));  // trim leading space
    arg.erase(std::find_if_not(arg.rbegin(), arg.rend(), ::isspace).base(), arg.end());  // trim trailing space

    if (arg.find('(') != std::string::npos && arg.back() == ')') {
        return applyFunction(arg, arg.find('('));
    } else if ((arg.front() == '-' || std::isdigit(arg.front())) && std::all_of(arg.begin() + 1, arg.end(), ::isdigit)) {
        return std::stoi(arg);
    } else {
        throw std::invalid_argument("Invalid function arguments: " + arg);
    }
}
