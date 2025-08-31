#include <gtest/gtest.h>
#include <random>
#include <cstddef>
#include "aarand/aarand.hpp"

class SampleTest : public ::testing::TestWithParam<int> {};

TEST_P(SampleTest, WithInputs) {
    size_t n = 9;
    std::vector<int> counter(n);

    size_t s = GetParam();
    std::mt19937_64 rng(s); // different seed for a bit of variety.

    std::vector<int> input(n);
    size_t niters = 100000;
    for (size_t i = 0; i < niters; ++i) {
        std::vector<int> output(s);
        std::iota(input.begin(), input.end(), 0);
        aarand::sample(input.begin(), input.size(), s, output.begin(), rng);

        for (size_t j = 0; j < s; ++j) {
            ++counter[output[j]];
        }
    }

    // Checking that the everyone occurs in every position at the expected frequency.
    double expected = static_cast<double>(niters * s) / n;
    for (const auto& freq : counter) {
        EXPECT_TRUE(std::abs(expected - freq)/expected < 0.05); 
    }
}

TEST_P(SampleTest, WithBound) {
    size_t n = 9;
    size_t s = GetParam();
    std::vector<int> counter(n);

    std::mt19937_64 rng(s); // different seed for a bit of variety.

    size_t niters = 100000;
    for (size_t i = 0; i < niters; ++i) {
        std::vector<int> output(s);
        aarand::sample(n, s, output.begin(), rng);

        for (size_t j = 0; j < s; ++j) {
            ++counter[output[j]];
        }
    }

    // Checking that the everyone occurs in every position at the expected frequency.
    double expected = static_cast<double>(niters * s) / n;
    for (const auto& freq : counter) {
        EXPECT_TRUE(std::abs(expected - freq)/expected < 0.05); 
    }
}

INSTANTIATE_TEST_SUITE_P(
    Sample,
    SampleTest,
    ::testing::Values(1, 2, 4, 7, 9)
);

TEST(SampleTest, Extremes) {
    std::size_t n = 9;
    std::vector<int> blah(n);
    std::iota(blah.begin(), blah.end(), 0);
    
    std::mt19937_64 rng(999);
    std::vector<int> output(100);

    aarand::sample(blah.begin(), blah.size(), static_cast<std::size_t>(100), output.begin(), rng);
    EXPECT_EQ(blah, std::vector<int>(output.begin(), output.begin() + n));
    EXPECT_EQ(output[n], 0);

    std::fill(output.begin(), output.end(), 0);
    aarand::sample(n, static_cast<std::size_t>(100), output.begin(), rng);
    EXPECT_EQ(blah, std::vector<int>(output.begin(), output.begin() + n));    
    EXPECT_EQ(output[n], 0);
}
