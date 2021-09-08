# Aaron's `random` C++ library

## Overview

This library implements distribution functions to convert random numbers from C++11 (P)RNGs into samples of the relevant distribution.
It provides implementations of some of the standard distribution functions in `<random>`, namely the uniform and normal distributions.
Why is a separate library necessary?
Because the standard functions are not guaranteed to give the same result across different library implementations - 
see [discussion here](https://stackoverflow.com/questions/24550963/stl-random-distributions-and-portability) - 
and I don't want to drag Boost into my project dependencies.

## Quick start

Just stick the `aarand.hpp` header file into your project somewhere.

```cpp
#include "aarand.hpp"
#include <random>
#include <iostream>

int main() {
    std::mt19937_64 rng(42);
    double val = aarand::standard_uniform(rng);
    std::cout << "Uniform value is: " << val << std::endl;

    auto paired = aarand::standard_normal(rng);
    std::cout << "Normal values are: " << paired.first << ", " << paired.second << std::endl;
    return 0;
}
```

If you're using CMake, you can just use `FetchContent`.
Note that this requires the header to be included from `aarand/aarand.hpp`.

```
include(FetchContent)

FetchContent_Declare(
  aarand
  GIT_REPOSITORY https://github.com/LTLA/aarand
  GIT_TAG master
)

FetchContent_MakeAvailable(aarand)

target_link_libraries(mylib aarand)
```

## Available distributions

Currently, only the bare bones are available:

- Standard uniform distribution (`standard_uniform`)
- Standard normal distribution (`standard_normal`)
- Standard exponential distribution (`standard_exponential`)

Contributions are welcome.
