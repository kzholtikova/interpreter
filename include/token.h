#pragma once


class Token {  // child Number and Operator classes
public:
    enum TokenType { Number, Operator, None};

    Token(const std::string& str);
    Token();
    TokenType getType() const;
    int getNumber() const;
    char getOperator() const;
    int getPrecedence() const;
    std::string toString() const;
private:
    TokenType type;
    int num;
    char op;
    int precedence;
};
