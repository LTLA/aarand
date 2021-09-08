#include <gtest/gtest.h>
#include <random>
#include "aarand/aarand.hpp"

TEST(NormalTest, Basic) {
    std::mt19937_64 rng(42);
    size_t N = 1000000;

    // Welford's algorithm here.
    double average = 0, var = 0;
    auto add = [&](double val, double n) {
        double delta = val - average;
        average += delta / n;
        var += delta * (val - average);
    };

    for (size_t i = 0; i < N; ++i) {
        auto paired = aarand::standard_normal<>(rng);
        add(paired.first, 2 * i + 1);
        add(paired.second, 2 * i + 2);
    }

    var /= 2 * N  - 1;
    EXPECT_TRUE(std::abs(average) < 1e-3);
    EXPECT_TRUE(std::abs(var - 1) < 1e-3);
}
