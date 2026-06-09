#include <random>
#include <stdexcept>

#include "gtest/gtest.h"

#include "Gauss_solve.h"

TEST(GaussSolve, TwoByTwo)
{
    GaussMatrix ab(2, 3);

    ab(0, 0) = 2.0;
    ab(0, 1) = 1.0;
    ab(0, 2) = 5.0;
    ab(1, 0) = 1.0;
    ab(1, 1) = 3.0;
    ab(1, 2) = 7.0;

    GaussVector result = Gauss_solve(ab);

    EXPECT_NEAR(result(0), 1.6, 0.000000001);
    EXPECT_NEAR(result(1), 1.8, 0.000000001);
}

TEST(GaussSolve, ThreeByThree)
{
    GaussMatrix ab(3, 4);

    ab(0, 0) = 2.0;
    ab(0, 1) = 1.0;
    ab(0, 2) = -1.0;
    ab(0, 3) = 8.0;

    ab(1, 0) = -3.0;
    ab(1, 1) = -1.0;
    ab(1, 2) = 2.0;
    ab(1, 3) = -11.0;

    ab(2, 0) = -2.0;
    ab(2, 1) = 1.0;
    ab(2, 2) = 2.0;
    ab(2, 3) = -3.0;

    GaussVector result = Gauss_solve(ab);

    EXPECT_NEAR(result(0), 2.0, 0.000000001);
    EXPECT_NEAR(result(1), 3.0, 0.000000001);
    EXPECT_NEAR(result(2), -1.0, 0.000000001);
}

TEST(GaussSolve, SingularMatrix)
{
    GaussMatrix ab(2, 3);

    ab(0, 0) = 1.0;
    ab(0, 1) = 2.0;
    ab(0, 2) = 3.0;
    ab(1, 0) = 2.0;
    ab(1, 1) = 4.0;
    ab(1, 2) = 6.0;

    EXPECT_THROW(Gauss_solve(ab), std::runtime_error);
}

TEST(GaussSolve, GeneratedSystem)
{
    const int size = 30;

    std::mt19937 generator(42);
    std::uniform_int_distribution<int> distribution(-10, 10);

    GaussMatrix matrix(size, size);
    GaussVector expected(size);

    for (int row = 0; row < size; ++row)
    {
        expected(row) = distribution(generator);

        for (int column = 0; column < size; ++column)
        {
            matrix(row, column) = distribution(generator);
        }
    }

    for (int row = 0; row < size; ++row)
    {
        matrix(row, row) += 100.0;
    }

    GaussVector right_part = matrix * expected;
    GaussMatrix augmented(size, size + 1);

    for (int row = 0; row < size; ++row)
    {
        for (int column = 0; column < size; ++column)
        {
            augmented(row, column) = matrix(row, column);
        }

        augmented(row, size) = right_part(row);
    }

    GaussVector result = Gauss_solve(augmented);

    for (int row = 0; row < size; ++row)
    {
        EXPECT_NEAR(result(row), expected(row), 0.000001);
    }
}
