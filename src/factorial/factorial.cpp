//File_name: factorial.cpp
//Author:    Stax The Engipreneur
//Date:      03 August 2018
//Details:   Factorial function test code. Changes made to function to make all assertions pass

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

//function to be tested
int factorial(int number) { return number <= 1 ? 1 : factorial(number - 1) * number; }

//five assertions within a case
TEST_CASE("testing the factorial function") {
    CHECK(factorial(0) == 1);
    CHECK(factorial(1) == 1);
    CHECK(factorial(2) == 2);
    CHECK(factorial(3) == 6);
    CHECK(factorial(10) == 3628800);
}
