include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
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

include(GoogleTest)
gtest_discover_tests(libtest)

add_test(NAME aarand_tests COMMAND libtest)
