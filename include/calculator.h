#pragma once
#include <vector>
#include <queue>
#include <stack>
#include "token.h"


class Calculator {
public:
    static double calculateExpression(const std::string& expr);
private:
    static double applyOperation(char op, double num1, double num2);
    static std::queue<Token> infixToPostfix(const std::string& infix);
    static void validateToken(const Token &prevT, const Token &t, bool isFirstToken, bool isLastToken);
    static void distributeToken(Token t, std::queue<Token>& outputQ, std::stack<Token>& opStack);
};