///@file test.cpp
///@brief A sample program to ensure that the Variable class is performing properly.
///@author S. V. Paulauskas
///@date November 11, 2013
/// @copyright Copyright (c) 2017 S. V. Paulauskas.
/// @copyright All rights reserved. Released under the Creative Commons Attribution-ShareAlike 4.0 International License
#include <UnitTest++.h>

#include "Variable.hpp"

static const double testValue1 = 3.0;
static const double testError1 = 0.4;
static const std::string testUnits1 = "MeV";
static const Variable variable1(testValue1, testError1, testUnits1);

static const double testValue2 = 5.0;
static const double testError2 = 0.6;
static const std::string testUnits2 = "MeV";
static const Variable variable2(testValue2, testError2, testUnits2);

static const double tolerance = 0.00001;

TEST (TestAdditionAndSubtraction) {
    static const double expectedError = sqrt(testError1 * testError1 + testError2 * testError2);
    static const Variable addSubtractTolerance(tolerance, 0, testUnits1);

    Variable expectedAddition(testValue1 + testValue2, expectedError, testUnits1);
    CHECK_CLOSE(expectedAddition, variable1 + variable2, addSubtractTolerance);

    Variable expectedSubtraction(testValue1 - testValue2, expectedError, testUnits1);
    CHECK_CLOSE(expectedSubtraction, variable1 - variable2, addSubtractTolerance);
}

TEST (TestMultiplication) {
    static const std::string multiplicationUnits = testUnits1 + "*" + testUnits2;
    static const Variable multiplyTolerance(tolerance, 0, multiplicationUnits);

    Variable expected(testValue1 * testValue2,
                      testValue1 * testValue2 * sqrt(pow(testError1 / testValue1, 2) + pow(testError2 / testValue2, 2)),
                      multiplicationUnits);
    CHECK_CLOSE(expected, variable1 * variable2, multiplyTolerance);
}

TEST(TestDivision) {
    static const std::string divisionUnits = testUnits1 + "/" + testUnits2;
    static const Variable divisionTolerance(tolerance, 0, divisionUnits);

    Variable expected(testValue1 / testValue2,
                      (testValue1 / testValue2)
                      * sqrt(pow(testError1 / testValue1, 2) + pow(testError2 / testValue2, 2)),
                      divisionUnits);
    CHECK_CLOSE(expected, variable1/variable2, divisionTolerance);
}

int main(int argc, char **argv) {
    return UnitTest::RunAllTests();
}
