cmake_minimum_required(VERSION 3.11)
project(CppRpnCalculatorInTdd CXX)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
)

FetchContent_MakeAvailable(googletest)

add_library(rpn src/rpnCalculator.cpp)

add_executable(tests src/tests.cpp)
target_link_libraries(tests gtest_main rpn)

add_custom_target(run_tests
                  COMMAND tests
                  DEPENDS tests)
