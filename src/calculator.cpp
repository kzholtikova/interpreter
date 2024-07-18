#include <iostream>
#include <sstream>
#include <map>
#include "../include/calculator.h"
#include "../include/interpreter.h"

const std::map<char, int> PRECEDENCES = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };

double Calculator::calculateExpression(const std::string& expr) {
    std::queue<Token*> postfixQ = infixToPostfix(expr);
    std::stack<double> calculationStack;

    while (!postfixQ.empty()) {
        Token* tPtr = postfixQ.front();
        postfixQ.pop();
        auto* opPtr = dynamic_cast<Operator*>(tPtr);
        if (opPtr != nullptr) {
            double num2 = calculationStack.top();
            calculationStack.pop();
            double num1 = calculationStack.top();
            calculationStack.pop();
            calculationStack.push(applyOperation(opPtr->getSymbol(), num1, num2));
        } else
            calculationStack.push(static_cast<Number*>(tPtr)->getValue());
    }

    return calculationStack.top();
}

double Calculator::applyOperation(char op, double num1, double num2) {
    switch (op) {
        case '+':
             return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            return num1 / num2;
    }
    return 0;
}

std::queue<Token*> Calculator::infixToPostfix(const std::string& infix) {
    std::stringstream ss(infix);
    std::string str;
    std::queue<Token*> outputQ;
    std::stack<Operator*> opStack;
    Token* prevTptr = nullptr;

    while (std::getline(ss, str, ' ')) {
        Token* tPtr = tokenize(str);
        validateToken(prevTptr, tPtr, ss.eof());
        distributeToken(tPtr, outputQ, opStack);
        prevTptr = tPtr;
    }
    while (!opStack.empty()) {
        outputQ.push(opStack.top());  // polymorphism – a derived class's handled as an instance of its base class
        opStack.pop();
    }
    return outputQ;
}

Token* Calculator::tokenize(const std::string& str) {
    if (str.size() == 1 && PRECEDENCES.count(str[0]))
        return new Operator(str[0], PRECEDENCES.at(str[0]));
    if ((str[0] == '-' || std::isdigit(str[0])) && std::all_of(str.begin() + 1, str.end(), ::isdigit))
        return new Number(std::stoi(str));
    if (std::all_of(str.begin(), str.end(), ::isalpha) && Interpreter::variables.find(str))
        return new Number(static_cast<int>(Interpreter::variables.getAt(str)));

    throw std::invalid_argument("Invalid symbol near " + str);
};

void Calculator::validateToken(Token* prevTptr, Token* tPtr, bool isLastToken) {
    if (((prevTptr == nullptr || isLastToken) && dynamic_cast<Number*>(tPtr) == nullptr) ||
    (prevTptr != nullptr && typeid(*prevTptr) == typeid(*tPtr)))
        throw std::invalid_argument("Invalid expression near " + (prevTptr ? prevTptr->toString() : "") + " " + tPtr->toString());

    auto* prevOpPtr = dynamic_cast<Operator*>(prevTptr);
    auto* currNumPtr = dynamic_cast<Number*>(tPtr);
    if (prevOpPtr != nullptr && prevOpPtr->getSymbol() == '/' &&  currNumPtr != nullptr && currNumPtr->getValue() == 0)
        throw std::invalid_argument("Division by zero");
}

void Calculator::distributeToken(Token* tPtr, std::queue<Token*>& outputQ, std::stack<Operator*>& opStack) {
    if (dynamic_cast<Number*>(tPtr) != nullptr)
        outputQ.push(tPtr);
    else {
        auto* opPtr = static_cast<Operator*>(tPtr);
        while (!opStack.empty() && opStack.top()->getPrecedence() >= opPtr->getPrecedence()) {
            outputQ.push(opStack.top());
            opStack.pop();
        }
        opStack.push(opPtr);
    }
}