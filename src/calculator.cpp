#include <sstream>
#include "../include/calculator.h"

double Calculator::calculateExpression(const std::string& expr) {
    std::queue<Token> postfixQ = infixToPostfix(expr);
    std::stack<double> calculationStack;

    while (!postfixQ.empty()) {
        Token t = postfixQ.front();
        postfixQ.pop();
        if (t.getType() == Token::TokenType::Operator) {
            double num2 = calculationStack.top();
            calculationStack.pop();
            double num1 = calculationStack.top();
            calculationStack.pop();
            calculationStack.push(applyOperation(t.getOperator(), num1, num2));
        } else
            calculationStack.push(t.getNumber());
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

std::queue<Token> Calculator::infixToPostfix(const std::string& infix) {
    std::stringstream ss(infix);
    std::string str;
    std::queue<Token> outputQ;
    std::stack<Token> opStack;
    Token prevToken;

    while (std::getline(ss, str, ' ')) {
        Token t = Token(str);
        validateToken(prevToken, t, prevToken.getType() == Token::TokenType::None, ss.eof());
        distributeToken(t, outputQ, opStack);
        prevToken = t;
    }
    while (!opStack.empty()) {
        outputQ.push(opStack.top());
        opStack.pop();
    }
    return outputQ;
}

void Calculator::validateToken(const Token& prevT, const Token& t, bool isFirstToken, bool isLastToken) {
    if (((isFirstToken || isLastToken) && t.getType() == Token::TokenType::Operator) || prevT.getType() == t.getType()) {
        throw std::invalid_argument("Invalid expression near " + prevT.toString() + " " + t.toString());
    }
    if (prevT.getType() == Token::TokenType::Operator && prevT.getOperator() == '/'
    &&  t.getType() == Token::TokenType::Number && t.getNumber() == 0)
        throw std::invalid_argument("Division by zero");
}

void Calculator::distributeToken(Token t, std::queue<Token>& outputQ, std::stack<Token>& opStack) {
    if (t.getType() == Token::TokenType::Number)
        outputQ.push(t);
    else {
        while (!opStack.empty() && opStack.top().getPrecedence() >= t.getPrecedence()) {
            outputQ.push(opStack.top());
            opStack.pop();
        }
        opStack.push(t);
    }
}