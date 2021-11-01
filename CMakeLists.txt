cmake_minimum_required(VERSION 3.12)
project(CppRpnCalculatorInTdd CXX)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
)

FetchContent_MakeAvailable(googletest)

add_library(rpn src/rpnCalculator.cpp)
target_compile_features(rpn PUBLIC cxx_std_20)

add_executable(tests src/rpnTests.cpp)
target_link_libraries(tests gtest_main rpn)
target_compile_features(tests PUBLIC cxx_std_20)

add_custom_target(run_tests
                  COMMAND tests
                  DEPENDS tests)
