#include <gtest/gtest.h>
#include "../include/functionHandler.h"

TEST(FunctionHandlerTest, ApplyFunctionReturnsCorrectResult) {
    double result = FunctionHandler::applyFunction("min(3,4)", 3);
    EXPECT_EQ(result, 3);
}

TEST(FunctionHandlerTest, ApplyFunctionThrowsForUnknownFunction) {
    EXPECT_THROW(FunctionHandler::applyFunction("ajkf(3,4)", 4), std::invalid_argument);
}

TEST(FunctionHandlerTest, ParseArgumentsHandlesNestedFunctions) {
    std::vector<double> expected = {3, 4, 1};
    std::vector<double> result = FunctionHandler::parseArguments("min(3,4),4,pow(2,0)");
    EXPECT_EQ(result, expected);
}

TEST(FunctionHandlerTest, ParseArgumentHandlesNegativeNumbers) {
    double result = FunctionHandler::parseArguments("-3")[0];
    EXPECT_EQ(result, -3);
}

TEST(FunctionHandlerTest, ParseArgumentHandlesNestedFunctions) {
    double result = FunctionHandler::parseArguments("min(3,4)")[0];
    EXPECT_EQ(result, 3);
}
