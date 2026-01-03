#include "catch2/catch_test_macros.hpp"

#include "linalg/Tuple.h"
#include "linalg/Matrix.h"

TEST_CASE("Constructing and inspecting a 4x4 matrix") {

    std::vector<double> data = {
           1,    2,    3,    4,
         5.5,  6.5,  7.5,  8.5,
           9,   10,   11,   12,
        13.5, 14.5, 15.5, 16.5
    };
    Matrix m(4, data);

    REQUIRE(m.at(0, 0) == 1);
    REQUIRE(m.at(0, 3) == 4);
    REQUIRE(m.at(1, 0) == 5.5);
    REQUIRE(m.at(1, 2) == 7.5);
    REQUIRE(m.at(2, 2) == 11);
    REQUIRE(m.at(3, 0) == 13.5);
    REQUIRE(m.at(3, 2) == 15.5);
}

TEST_CASE("Matrix equality with identical matrices") {
    Matrix a(4);
    Matrix b(4);

    a.at(0, 0) = 1; a.at(0, 1) = 2; a.at(0, 2) = 3; a.at(0, 3) = 4;
    a.at(1, 0) = 5; a.at(1, 1) = 6; a.at(1, 2) = 7; a.at(1, 3) = 8;
    a.at(2, 0) = 9; a.at(2, 1) = 10; a.at(2, 2) = 11; a.at(2, 3) = 12;
    a.at(3, 0) = 13; a.at(3, 1) = 14; a.at(3, 2) = 15; a.at(3, 3) = 16;

    b.at(0, 0) = 1; b.at(0, 1) = 2; b.at(0, 2) = 3; b.at(0, 3) = 4;
    b.at(1, 0) = 5; b.at(1, 1) = 6; b.at(1, 2) = 7; b.at(1, 3) = 8;
    b.at(2, 0) = 9; b.at(2, 1) = 10; b.at(2, 2) = 11; b.at(2, 3) = 12;
    b.at(3, 0) = 13; b.at(3, 1) = 14; b.at(3, 2) = 15; b.at(3, 3) = 16;

    REQUIRE(a == b);
}

TEST_CASE("Matrix equality with different matrices") {
    Matrix a(4);
    Matrix b(4);

    a.at(0, 0) = 1; a.at(0, 1) = 2; a.at(0, 2) = 3; a.at(0, 3) = 4;
    a.at(1, 0) = 5; a.at(1, 1) = 6; a.at(1, 2) = 7; a.at(1, 3) = 8;
    a.at(2, 0) = 9; a.at(2, 1) = 10; a.at(2, 2) = 11; a.at(2, 3) = 12;
    a.at(3, 0) = 13; a.at(3, 1) = 14; a.at(3, 2) = 15; a.at(3, 3) = 16;

    b.at(0, 0) = 1; b.at(0, 1) = 2; b.at(0, 2) = 3; b.at(0, 3) = 4;
    b.at(1, 0) = 5; b.at(1, 1) = 6; b.at(1, 2) = 7; b.at(1, 3) = 8;
    b.at(2, 0) = 9; b.at(2, 1) = 10; b.at(2, 2) = 11; b.at(2, 3) = 99; // Different value here
    b.at(3, 0) = 13; b.at(3, 1) = 14; b.at(3, 2) = 15; b.at(3, 3) = 16;

    REQUIRE(!(a == b));
}

TEST_CASE("Matrix equality with floating point precision") {
    Matrix a(4);
    Matrix b(4);

    a.at(0, 0) = 1.000001; a.at(0, 1) = 2.000001; a.at(0, 2) = 3.000001; a.at(0, 3) = 4.000001;
    a.at(1, 0) = 5.000001; a.at(1, 1) = 6.000001; a.at(1, 2) = 7.000001; a.at(1, 3) = 8.000001;
    a.at(2, 0) = 9.000001; a.at(2, 1) = 10.000001; a.at(2, 2) = 11.000001; a.at(2, 3) = 12.000001;
    a.at(3, 0) = 13.000001; a.at(3, 1) = 14.000001; a.at(3, 2) = 15.000001; a.at(3, 3) = 16.000001;

    b.at(0, 0) = 1.000002; b.at(0, 1) = 2.000002; b.at(0, 2) = 3.000002; b.at(0, 3) = 4.000002;
    b.at(1, 0) = 5.000002; b.at(1, 1) = 6.000002; b.at(1, 2) = 7.000002; b.at(1, 3) = 8.000002;
    b.at(2, 0) = 9.000002; b.at(2, 1) = 10.000002; b.at(2, 2) = 11.000002; b.at(2, 3) = 12.000002;
    b.at(3, 0) = 13.000002; b.at(3, 1) = 14.000002; b.at(3, 2) = 15.000002; b.at(3, 3) = 16.000002;
    REQUIRE(a == b);
}

TEST_CASE("Equality of different sized matrices") {
    Matrix a(3);
    Matrix b(4);

    REQUIRE(!(a == b));
}

TEST_CASE("Multiplying two matrices") {
    Matrix a(4);
    Matrix b(4);

    a.at(0, 0) = 1; a.at(0, 1) = 2; a.at(0, 2) = 3; a.at(0, 3) = 4;
    a.at(1, 0) = 5; a.at(1, 1) = 6; a.at(1, 2) = 7; a.at(1, 3) = 8;
    a.at(2, 0) = 9; a.at(2, 1) = 8; a.at(2, 2) = 7; a.at(2, 3) = 6;
    a.at(3, 0) = 5; a.at(3, 1) = 4; a.at(3, 2) = 3; a.at(3, 3) = 2;

    b.at(0, 0) = -2; b.at(0, 1) = 1; b.at(0, 2) = 2; b.at(0, 3) = 3;
    b.at(1, 0) = 3; b.at(1, 1) = 2; b.at(1, 2) = 1; b.at(1, 3) = -1;
    b.at(2, 0) = 4; b.at(2, 1) = 3; b.at(2, 2) = 6; b.at(2, 3) = 5;
    b.at(3, 0) = 1; b.at(3, 1) = 2; b.at(3, 2) = 7; b.at(3, 3) = 8;

    Matrix expected(4);
    expected.at(0, 0) = 20; expected.at(0, 1) = 22; expected.at(0, 2) = 50; expected.at(0, 3) = 48;
    expected.at(1, 0) = 44; expected.at(1, 1) = 54; expected.at(1, 2) = 114; expected.at(1, 3) = 108;
    expected.at(2, 0) = 40; expected.at(2, 1) = 58; expected.at(2, 2) = 110; expected.at(2, 3) = 102;
    expected.at(3, 0) = 16; expected.at(3, 1) = 26; expected.at(3, 2) = 46; expected.at(3, 3) = 42;
    Matrix result = a * b;
    REQUIRE(result == expected);
}

TEST_CASE("Multiplying a matrix by a tuple") {
    std::vector<double> data = {
        1, 2, 3, 4,
        2, 4, 4, 2,
        8, 6, 4, 1,
        0, 0, 0, 1
    };
    Matrix a(4, data);

    Tuple b(1, 2, 3, 1);

    Tuple result = a * b;

    REQUIRE(result.x == 18);
    REQUIRE(result.y == 24);
    REQUIRE(result.z == 33);
    REQUIRE(result.w == 1);
}

TEST_CASE("Multiplying a matrix by the identity matrix") {
    std::vector<double> data = {
        0, 1, 2, 4,
        1, 2, 4, 8,
        2, 4, 8, 16,
        4, 8, 16, 32
    };
    Matrix a(4, data);

    Matrix identity = Matrix::identity(4);

    Matrix result = a * identity;

    REQUIRE(result == a);
}

TEST_CASE("Transposing a matrix") {
    std::vector<double> data = {
        0, 9, 3, 0,
        9, 8, 0, 8,
        1, 8, 5, 3,
        0, 0, 5, 8
    };
    Matrix a(4, data);

    std::vector<double> expectedData = {
        0, 9, 1, 0,
        9, 8, 8, 0,
        3, 0, 5, 5,
        0, 8, 3, 8
    };
    Matrix expected(4, expectedData);

    Matrix result = a.transpose();

    REQUIRE(result == expected);
}

TEST_CASE("Calculating the determinant of a 2x2 matrix") {
    std::vector<double> data = {
        1, 5,
        -3, 2
    };
    Matrix a(2, data);

    double det = a.determinant();

    REQUIRE(APPROX_EQUAL(det, 17.0));
}

TEST_CASE("Calculating the determinant of a 3x3 matrix") {
    std::vector<double> data = {
        1, 2, 6,
        -5, 8, -4,
        2, 6, 4
    };
    Matrix a(3, data);

    double det = a.determinant();

    REQUIRE(APPROX_EQUAL(det, -196.0));
}

TEST_CASE("Calculating the determinant of a 4x4 matrix") {
    std::vector<double> data = {
        -2, -8, 3, 5,
        -3, 1, 7, 3,
        1, 2, -9, 6,
        -6, 7, 7, -9
    };
    Matrix a(4, data);

    double det = a.determinant();

    REQUIRE(APPROX_EQUAL(det, -4071.0));
}

TEST_CASE("Calculating the inverse of a matrix") {
    std::vector<double> data = {
        -5, 2, 6, -8,
        1, -5, 1, 8,
        7, 7, -6, -7,
        1, -3, 7, 4
    };
    Matrix a(4, data);

    Matrix inv = a.inverse();

    std::vector<double> expectedData = {
        0.21805, 0.45113, 0.24060, -0.04511,
        -0.80827, -1.45677, -0.44361, 0.52068,
        -0.07895, -0.22368, -0.05263, 0.19737,
        -0.52256, -0.81391, -0.30075, 0.30639
    };
    Matrix expected(4, expectedData);

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            REQUIRE(APPROX_EQUAL(inv.at(row, col), expected.at(row, col)));
        }
    }
}




