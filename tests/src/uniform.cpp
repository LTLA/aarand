#include <gtest/gtest.h>
#include <random>
#include "aarand/aarand.hpp"

TEST(UniformTest, Basic) {
    std::mt19937_64 rng(42);
    size_t N = 1000000;

    double average = 0, min = 1, max = 0;
    for (size_t i = 0; i < N; ++i) {
        double val = aarand::standard_uniform<>(rng);
        average += val;
        min = std::min(min, val);
        max = std::max(max, val);
    }

    average /= N;
    EXPECT_TRUE(std::abs(average - 0.5) < 1e-3);
    EXPECT_TRUE(min >= 0);
    EXPECT_TRUE(min < 1e-3);
    EXPECT_TRUE(max > 0.999);
    EXPECT_TRUE(max < 1);
}

class DiscreteUniformTest : public ::testing::TestWithParam<int> {};

TEST_P(DiscreteUniformTest, Discrete) {
    std::mt19937_64 rng(42);
    size_t N = 1000000;
    int upper = GetParam();

    double average = 0;
    int min = 1, max = 0;
    for (size_t i = 0; i < N; ++i) {
        int val = aarand::discrete_uniform<>(rng, upper);
        average += val;
        min = std::min(min, val);
        max = std::max(max, val);
    }

    average /= N;
    EXPECT_TRUE(std::abs(1 - average / (static_cast<double>(upper - 1)/2)) < 1e-2);
    EXPECT_TRUE(min == 0);
    EXPECT_TRUE(max == upper - 1); // should sample enough to hit the max.
}

INSTANTIATE_TEST_SUITE_P(
    DiscreteUniform,
    DiscreteUniformTest,
    ::testing::Values(3, 7, 11, 123, 7531, 131313)
);
