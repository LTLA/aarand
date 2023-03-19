# Aaron's `random` C++ library

![Unit tests](https://github.com/LTLA/aarand/actions/workflows/run-tests.yaml/badge.svg)
![Documentation](https://github.com/LTLA/aarand/actions/workflows/doxygenate.yaml/badge.svg)

## Overview

This library implements distribution functions to convert random numbers from C++11 (P)RNGs into samples of the relevant distribution.
It provides implementations of some of the standard distribution functions in `<random>`, namely the uniform and normal distributions.
Why is a separate library necessary?
Because the standard functions are not guaranteed to give the same result across different library implementations - 
see [discussion here](https://stackoverflow.com/questions/24550963/stl-random-distributions-and-portability) - 
and I don't want to drag Boost into my project dependencies.

## Quick start

Usage is pretty simple - just plug in your favorite PRNG into desired distribution function:

```cpp
#include "aarand/aarand.hpp"
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

Check out the [reference documentation](https://ltla.github.io/aarand) for more details.

## Building projects

### CMake with `FetchContent`

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

### CMake with `find_package()`

```cmake
find_package(ltla_aarand CONFIG REQUIRED)
target_link_libraries(mylib PRIVATE ltla::aarand)
```

To install the library use:

```sh
mkdir build && cd build
cmake .. -DAARAND_TESTS=OFF
cmake --build . --target install
```

### Manual

Copy and paste the [`aarand.hpp`](include/aarand/aarand.hpp) header file into your project and `#include` it as appropriate. 

## Available distributions

Currently, only the bare bones are available:

- Standard uniform distribution (`standard_uniform`)
- Standard normal distribution (`standard_normal`)
- Standard exponential distribution (`standard_exponential`)
- Discrete uniform distribution (`discrete_uniform`)
- Shuffling an input vector (`shuffle`)
- Sampling from an input vector or from an integer bound (`sample`)

Contributions are welcome.
