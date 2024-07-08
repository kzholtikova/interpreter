#include <string>
#include "../include/token.h"

int Number::getValue() const {
    return value;
}

std::string Number::toString() const {
    return std::to_string(value);
}

char Operator::getSymbol() const {
    return symbol;
}

int Operator::getPrecedence() const {
    return precedence;
}

std::string Operator::toString() const {
    return std::string(1, symbol);
}
