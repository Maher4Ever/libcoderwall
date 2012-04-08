cmake_minimum_required (VERSION 2.6)

enable_testing()

# Generate files name for the tests from the sources
#
# Example: coderwall.c => coderwall_test.c
#
foreach(filename ${CODERWALL_SRCS})
  string(REGEX REPLACE
    "(.*)\\.c" "\\1_test.c"
    test_file
    ${filename}
  )

  set (CODERWALL_TESTS_SRCS ${CODERWALL_TESTS_SRCS} ${test_file})
endforeach(filename)

include_directories (
  "${PROJECT_SOURCE_DIR}/lib"
  "${PROJECT_SOURCE_DIR}/include"

  "${PROJECT_BINARY_DIR}/tests" # For fixtures path

  "${gtest_SOURCE_DIR}/include"
  "${gtest_SOURCE_DIR}"
)

# GoogleTest has C++ headers, so compile our tests as if they contained C++ code.
set_source_files_properties(${CODERWALL_TESTS_SRCS} PROPERTIES LANGUAGE CXX)

# Generate a header file with a few info for the tests
configure_file (
  "${PROJECT_SOURCE_DIR}/tests/tests_helper.h.in"
  "${PROJECT_BINARY_DIR}/tests/tests_helper.h"
)

add_executable(coderwall_tests
  ${CODERWALL_TESTS_SRCS}
  tests_helper.c
)

target_link_libraries(coderwall_tests coderwall gtest gtest_main)

# Run tests with 'make check'
add_custom_target(check
                  COMMAND "${PROJECT_BINARY_DIR}/tests/coderwall_tests"
                  DEPENDS coderwall_tests)
