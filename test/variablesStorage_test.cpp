#include <gtest/gtest.h>
#include "../include/variablesStorage.h"
#include "../include/interpreter.h"

TEST(VariableStorageTest, AddVariableStoresVariable) {
    VariableStorage vs;
    vs.addVariable("x = 5");
    EXPECT_TRUE(vs.find("x"));
}

TEST(VariableStorageTest, AddVariableThrowsForInvalidSyntax) {
    VariableStorage vs;
    EXPECT_THROW(vs.addVariable("x = "), std::invalid_argument);
}

TEST(VariableStorageTest, FindReturnsFalseForNonExistingVariable) {
    VariableStorage vs;
    EXPECT_FALSE(vs.find("y"));
}

TEST(VariableStorageTest, GetAtReturnsValueForExistingVariable) {
    VariableStorage vs;
    vs.addVariable("x = 5");
    EXPECT_EQ(vs.getAt("x"), 5);
}

TEST(VariableStorageTest, GetAtThrowsForNonExistingVariable) {
    VariableStorage vs;
    EXPECT_THROW(vs.getAt("y"), std::invalid_argument);
}