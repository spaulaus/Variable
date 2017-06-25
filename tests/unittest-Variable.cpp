///@file test.cpp
///@brief A sample program to ensure that the Variable class is performing properly.
///@author S. V. Paulauskas
///@date November 11, 2013
/// @copyright Copyright (c) 2017 S. V. Paulauskas.
/// @copyright All rights reserved. Released under the Creative Commons Attribution-ShareAlike 4.0 International License
#include <stdexcept>
#include <sstream>
#include <UnitTest++.h>

#include "Variable.hpp"

static const double testValue1 = 3.0;
static const double testError1 = 0.4;
static const std::string testUnits1 = "MeV";
static const Variable variable1(testValue1, testError1, testUnits1);
static const Variable variable3(testValue1, testError1, testUnits1);

static const double testValue2 = 5.0;
static const double testError2 = 0.6;
static const std::string testUnits2 = "MeV";
static const Variable variable2(testValue2, testError2, testUnits2);

static const double tolerance = 0.00001;

static const Variable throwTester(0.1, 0.01, "a");

TEST (TestArithmeticOperators) {
    static const double expectedError = 0.721110;
    static const Variable addSubtractTolerance(tolerance, 0, testUnits1);

    Variable expectedAddition(8, expectedError, testUnits1);
    CHECK_CLOSE(expectedAddition, variable1 + variable2, addSubtractTolerance);
    CHECK_THROW(throwTester + variable1, std::invalid_argument);

    Variable expectedSubtraction(-2, expectedError, testUnits1);
    CHECK_CLOSE(expectedSubtraction, variable1 - variable2, addSubtractTolerance);
    CHECK_THROW(throwTester - variable1, std::invalid_argument);

    static const std::string multiplicationUnits = "MeV*MeV";
    CHECK_CLOSE(Variable(15, 2.69072, multiplicationUnits), variable1 * variable2,
                Variable(tolerance, 0, multiplicationUnits));

    static const std::string divisionUnits = "MeV/MeV";
    CHECK_CLOSE(Variable(0.6, 0.10763, divisionUnits), variable1/variable2, Variable(tolerance, 0, divisionUnits));
}

TEST (TestComparisonOperators) {
    CHECK_EQUAL(variable1, variable3);
    CHECK_THROW(variable1 == throwTester, std::invalid_argument);

    CHECK(variable1 != variable2);
    CHECK_THROW(variable1 != throwTester, std::invalid_argument);

    CHECK(variable2 > variable1);
    CHECK_THROW(variable1 > throwTester, std::invalid_argument);

    CHECK(variable1 >= variable3);
    CHECK_THROW(variable1 >= throwTester, std::invalid_argument);

    CHECK(variable1 < variable2);
    CHECK_THROW(variable1 < throwTester, std::invalid_argument);

    CHECK(variable1 <= variable3);
    CHECK_THROW(variable1 <= throwTester, std::invalid_argument);
}

TEST (TestBitwiseOperators) {
       

}

int main(int argc, char **argv) {
    return UnitTest::RunAllTests();
}
