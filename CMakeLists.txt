cmake_minimum_required(VERSION 3.11)
project(CppRpnCalculatorInTdd CXX)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
)

FetchContent_MakeAvailable(googletest)

find_package(Boost REQUIRED COMPONENTS regex)

add_library(rpn src/rpnCalculator.cpp)
target_link_libraries(rpn ${Boost_REGEX_LIBRARY})
target_compile_features(rpn PUBLIC cxx_std_20)

add_executable(tests src/tests.cpp)
target_link_libraries(tests gtest_main rpn)
target_compile_features(tests PUBLIC cxx_std_20)

add_custom_target(run_tests
                  COMMAND tests
                  DEPENDS tests)
