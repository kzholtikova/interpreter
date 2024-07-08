#pragma once


class Token {
public:
    virtual ~Token() {};

    virtual std::string toString() const = 0;  // Pure virtual function makes the class abstract
};

class Number : public Token {
private:
    int value;
public:
    Number(int num) : value(num) {};

    std::string toString() const override;
    int getValue() const;
};

class Operator : public Token {
private:
    char symbol;
    int precedence;
public:
    Operator(char op, int precedence) : symbol(op), precedence(precedence) {};

    std::string toString() const override;
    char getSymbol() const;
    int getPrecedence() const;
};
