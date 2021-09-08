#ifndef AARAND_AARAND_HPP
#define AARAND_AARAND_HPP

#include <cmath>
#include <limits>

namespace aarand {

/**
 * @tparam T Floating point type.
 * @tparam Engine A random number generator class with `operator()`, `min()` (static) and `max()` (static) methods,
 * where the `result_type` is an unsigned integer value.
 *
 * @param eng Instance of an RNG class like `std::mt19937_64`.
 *
 * @return Draw from a standard uniform distribution.
 */
template<typename T = double, class Engine>
T standard_uniform(Engine& eng) {
    static_assert(!std::numeric_limits<typename Engine::result_type>::is_signed);
    static_assert(std::numeric_limits<typename Engine::result_type>::is_integer);

    // Stolen from Boost, see https://www.boost.org/doc/libs/1_67_0/boost/random/uniform_01.hpp
    // The +1 probably doesn't matter for 64-bit generators, but is helpful for engines with 
    // fewer output bits, to reduce the (small) probability of sampling 1's.
    constexpr double factor = 1.0 / (static_cast<T>(Engine::max() - Engine::min()) + 1.0);
    double result;
    do {
        result = static_cast<T>(eng() - Engine::min()) * factor;
    } while (result == 1.0);
    return result;
}

/**
 * @tparam T Floating point type.
 * @tparam Engine A random number generator class with `operator()`, `min()` (static) and `max()` (static) methods,
 * where the `result_type` is an unsigned integer value.
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
 * @tparam T Floating point type.
 * @tparam Engine A random number generator class with `operator()`, `min()` (static) and `max()` (static) methods,
 * where the `result_type` is an unsigned integer value.
 *
 * @param eng Instance of an RNG class like `std::mt19937_64`.
 *
 * @return Draw from a standard exponential distribution.
 */
template<typename T = double, class Engine>
T standard_exponential(Engine& eng) {
    return -std::log(standard_uniform(eng));
}

template<typename T = int, class Engine>
T discrete_uniform(Engine& eng, T max) {
    typedef typename Engine::result_type R;
    static_assert(std::numeric_limits<R>::is_integer);
    static_assert(!std::numeric_limits<R>::is_signed);

    constexpr R range = Engine::max() - Engine::min();
    static_assert(range >= std::numeric_limits<T>::max());

    // Under the assertion above, it is impossible for max == Engine::max() +
    // 1. So we don't have to deal with the crap about combining draws to get
    // enough entropy, which is 90% of the Boost implementation.
    const R limit = range - range % max;
    T draw;
    do {
        draw = (eng() - Engine::min()) % max;
    } while (draw > limit);
    return draw;
}




}

#endif
