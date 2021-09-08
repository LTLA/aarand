#ifndef AARAND_AARAND_HPP
#define AARAND_AARAND_HPP

#include <cmath>

namespace aarand {

/**
 * @tparam Engine A random number generator class with `operator()`, `min()` (static) and `max()` (static) methods.
 *
 * @param eng Instance of an RNG class like `std::mt19937_64`.
 *
 * @return Draw from a standard uniform distribution.
 */
template<typename T = double, class Engine>
T standard_uniform(Engine& eng) {
    // Stolen from Boost.
    constexpr double factor = 1.0 / static_cast<double>(Engine::max() - Engine::min());
    double result;
    do {
        result = static_cast<double>(eng() - Engine::min()) * factor;
    } while (result == 1.0);
    return result;
}

/**
 * @tparam Engine A random number generator class with `operator()`, `min()` (static) and `max()` (static) methods.
 *
 * @param eng Instance of an RNG class like `std::mt19937_64`.
 *
 * @return A pair of independent draws from a standard normal distribution with mean 0 and variance 1.
 */
template<typename T = double, class Engine>
std::pair<T, T> standard_normal(Engine& eng) {
    constexpr double pi = 3.14159265358979323846;

    // Box-Muller gives us two random values at a time.
    double constant = std::sqrt(-2 * std::log(standard_uniform<T>(eng)));
    double angle = 2 * pi * standard_uniform<T>(eng);
    return std::make_pair(constant * std::sin(angle), constant * std::cos(angle));
}

/**
 * @tparam Engine A random number generator class with `operator()`, `min()` (static) and `max()` (static) methods.
 *
 * @param eng Instance of an RNG class like `std::mt19937_64`.
 *
 * @return Draw from a standard exponential distribution.
 */
template<typename T = double, class Engine>
T standard_exponential(Engine& eng) {
    return -std::log(standard_uniform(eng));
}

}

#endif
