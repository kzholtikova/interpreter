#pragma once
#include <queue>
#include <stack>
#include "token.h"


class Calculator {
public:
    static double calculateExpression(const std::string& expr);
private:
    static double applyOperation(char op, double num1, double num2);
    static std::queue<Token*> infixToPostfix(const std::string& infix);
    static Token* tokenize(const std::string& str);
    static void validateToken(Token* prevTptr, Token* tPtr, bool isLastToken);
    static void distributeToken(Token* tPtr, std::queue<Token*>& outputQ, std::stack<Operator*>& opStack);
};