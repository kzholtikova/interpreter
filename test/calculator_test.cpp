#include <gtest/gtest.h>
#include "../include/calculator.h"

TEST(CalculatorTest, IncorrectOrderErrorFirstToken) {
    EXPECT_THROW(Calculator::calculateExpression("* 2 + 3"), std::invalid_argument);
}

TEST(CalculatorTest, IncorrectOrderErrorLastToken) {
    EXPECT_THROW(Calculator::calculateExpression("2 * 3 +"), std::invalid_argument);
}

TEST(CalculatorTest, IncorrectOrderErrorWithNumbers) {
    EXPECT_THROW(Calculator::calculateExpression("2 2 3 * 4"), std::invalid_argument);
}

TEST(CalculatorTest, IncorrectOrderErrorWithOperators) {
    EXPECT_THROW(Calculator::calculateExpression("2 + * 3"), std::invalid_argument);
}

TEST(CalculatorTest, InvalidSymbolError) {
    EXPECT_THROW(Calculator::calculateExpression("5 - 2 & 3"), std::invalid_argument);
}

TEST(CalculatorTest, InvalidSymbolErrorAmongDigits) {
    EXPECT_THROW(Calculator::calculateExpression("2 / 3a76 * 4"), std::invalid_argument);
}

TEST(CalculatorTest, DivisionByZeroError) {
    EXPECT_THROW(Calculator::calculateExpression("2 / 0"), std::invalid_argument);
}

TEST(CalculatorTest, PrecedenceConsideration) {
    EXPECT_DOUBLE_EQ(Calculator::calculateExpression("2 + 3 * 4"), 14.0);
    EXPECT_DOUBLE_EQ(Calculator::calculateExpression("2 * 3 + 4"), 10.0);
}

TEST(CalculatorTest, CorrectExpressionResult) {
    EXPECT_DOUBLE_EQ(Calculator::calculateExpression("5 + 3 * 7 - 2 / 4"), 25.5);
}

TEST(CalculatorTest, CorrectSingleTokenEvaluation) {
    EXPECT_DOUBLE_EQ(Calculator::calculateExpression("3"), 3);
}
