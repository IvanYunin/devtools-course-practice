// Copyright 2019 Ivan Yunin

#include <gtest/gtest.h>

#include "include/complex_number.h"

TEST(Yunin_Ivan_ComplexNumberTest, Priority_Of_Multiplication_Operation) {
    // Arrange

    ComplexNumber z1(1.0, 1.0);
    ComplexNumber z2(2.0, 2.0);
    ComplexNumber z3(3.0, 3.0);
    ComplexNumber ans(1.0, 13.0);

    // Act

    ComplexNumber res = z1 + z2 * z3;
    // Assert

    EXPECT_EQ(ans, res);
}

TEST(Yunin_Ivan_ComplexNumberTest, Rize_To_Third_Degree ) {
    // Arrange

    ComplexNumber z(7, 3);
    ComplexNumber ans(154, 414);

    // Act

    ComplexNumber res = z * z * z;

    // Assert

    EXPECT_EQ(ans, res);
}

TEST(Yunin_Ivan_ComplexNumberTest, Multiply_On_Own_Real_Part) {
    // Arrange
    ComplexNumber z(10.0, 10.0);
    ComplexNumber ans(100.0, 100.0);


    // Act
    ComplexNumber res = z.getRe() * z;

    // Assert
    EXPECT_EQ(ans, res);
}