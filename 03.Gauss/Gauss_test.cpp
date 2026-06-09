#include <random>
#include <stdexcept>

#include "gtest/gtest.h"

#include "Gauss_solve.h"

TEST(GaussSolve, Small2x2)
{
    GaussMatrix ab(2, 3);
    ab << 2, 1, 5,
          1, 3, 7;

    GaussVector x = Gauss_solve(ab);

    EXPECT_NEAR(x(0), 1.6, 1e-9);
    EXPECT_NEAR(x(1), 1.8, 1e-9);
}

TEST(GaussSolve, Classic3x3)
{
    GaussMatrix ab(3, 4);
    ab << 2, 1, -1, 8,
          -3, -1, 2, -11,
          -2, 1, 2, -3;

    GaussVector x = Gauss_solve(ab);

    EXPECT_NEAR(x(0), 2.0, 1e-9);
    EXPECT_NEAR(x(1), 3.0, 1e-9);
    EXPECT_NEAR(x(2), -1.0, 1e-9);
}

TEST(GaussSolve, SingularMatrixThrows)
{
    GaussMatrix ab(2, 3);
    ab << 1, 2, 3,
          2, 4, 6;

    EXPECT_THROW(Gauss_solve(ab), std::runtime_error);
}

TEST(GaussSolve, GeneratedLargeSystem)
{
    const int n = 30;

    std::mt19937 generator(42);
    std::uniform_real_distribution<double> distribution(-10.0, 10.0);

    GaussMatrix a(n, n);
    GaussVector expected(n);

    for (int row = 0; row < n; ++row)
    {
        expected(row) = distribution(generator);

        for (int col = 0; col < n; ++col)
        {
            a(row, col) = distribution(generator);
        }
    }

    for (int row = 0; row < n; ++row)
    {
        a(row, row) += 100.0;
    }

    GaussVector b = a * expected;
    GaussMatrix ab(n, n + 1);

    ab.block(0, 0, n, n) = a;
    ab.col(n) = b;

    GaussVector actual = Gauss_solve(ab);

    for (int row = 0; row < n; ++row)
    {
        EXPECT_NEAR(actual(row), expected(row), 1e-7);
    }
}
