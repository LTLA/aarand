#include <gtest/gtest.h>
#include <random>
#include "aarand/aarand.hpp"

TEST(ExponentialTest, Basic) {
    std::mt19937_64 rng(42);
    size_t N = 10000000;

    double average = 0, min = 1, max = 0;
    for (size_t i = 0; i < N; ++i) {
        double val = aarand::standard_exponential<>(rng);
        average += val;
        min = std::min(min, val);
        max = std::max(max, val);
    }

    average /= N;
    EXPECT_TRUE(std::abs(average - 1) < 1e-3);
    EXPECT_TRUE(min > 0);
    EXPECT_TRUE(min < 1e-3);
    EXPECT_TRUE(max > 3);
}
