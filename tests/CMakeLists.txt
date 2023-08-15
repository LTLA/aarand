include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/afd902e992b720d1b3e106bc5e425a5768872265.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Avoid installing GoogleTest when installing this project.
option(INSTALL_GTEST "Enable installation of googletest." OFF)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    libtest 
    src/uniform.cpp
    src/normal.cpp
    src/exponential.cpp
    src/shuffle.cpp
    src/sample.cpp
)

target_link_libraries(
    libtest
    gtest_main
    aarand
)

target_compile_options(libtest PRIVATE -Wall -Werror -Wpedantic -Wextra)

include(GoogleTest)
gtest_discover_tests(libtest)
