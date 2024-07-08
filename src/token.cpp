#include <string>
#include <map>
#include "../include/token.h"

const std::map<char, int> PRECEDENCES = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };

Token::Token(const std::string &str) {
    if (std::all_of(str.begin(), str.end(), ::isdigit)) {
        type = TokenType::Number;
        num = std::stoi(str);
    } else if (str.size() == 1 && PRECEDENCES.count(str[0])) {
        type = TokenType::Operator;
        op = str[0];
        precedence = PRECEDENCES.at(op);
    } else
        throw std::invalid_argument("Invalid symbol near " + str);
}

Token::Token() {
    type = TokenType::None;
    op = ' ';
}

Token::TokenType Token::getType() const {
    return type;
}

int Token::getNumber() const {
    return num;
}

char Token::getOperator() const {
    return op;
}

int Token::getPrecedence() const {
    return precedence;
}

std::string Token::toString() const {
    return type == TokenType::Number ? std::to_string(num) : std::string(1, op);
}
