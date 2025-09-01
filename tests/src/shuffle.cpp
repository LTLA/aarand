#include <gtest/gtest.h>
#include <random>
#include "aarand/aarand.hpp"

TEST(ShuffleTest, Basic) {
    size_t n = 7;
    std::vector<int> blah(n);
    std::vector<std::vector<int> > counter(n, std::vector<int>(n));
    std::vector<unsigned char> local_count(n);

    std::mt19937_64 rng;
    size_t niters = 100000;
    for (size_t s = 0; s < niters; ++s) {
        std::iota(blah.begin(), blah.end(), 0);
        aarand::shuffle(blah.begin(), blah.size(), rng);

        for (size_t i = 0; i < n; ++i) {
            ++counter[i][blah[i]];
            EXPECT_EQ(local_count[blah[i]], 0); // check there aren't any duplicates.
            local_count[blah[i]] = 1;
        }

        for (size_t i = 0; i < n; ++i) {
            local_count[blah[i]] = 0;
        }
    }

    // Checking that the everyone occurs in every position at the expected frequency.
    double expected = static_cast<double>(niters) / n;
    for (const auto& current : counter) {
        for (const auto& freq : current) {
            EXPECT_TRUE(std::abs(expected - freq)/expected < 0.05); 
        }
    }

    // Shuffling an array of length 1 has no effect.
    blah.resize(1);
    blah[0] = 99;
    aarand::shuffle(blah.begin(), 1, rng);
    EXPECT_EQ(blah[0], 99);
}
