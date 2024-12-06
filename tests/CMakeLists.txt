#*************************************************
#                 Test Setup Header:             *
#*************************************************
find_program(VALGRIND_BINARY
    NAMES valgrind
    HINTS "/usr/bin" "/usr/local/bin" 
)

if(${VALGRIND_BINARY} STREQUAL "VALGRIND_BINARY-NOTFOUND")
    message(WARNING "Valgrind not found on this system. Disabling Valgrind tests.")
else()
    message(STATUS "Using Valgrind: ${VALGRIND_BINARY}")
endif()


add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third_party/googletest)
set(TESTS_SRC ${CMAKE_CURRENT_LIST_DIR}/src)


#*************************************************
#                  Test Definitions:             *
#*************************************************

#*************************************************
#                     Unit Tests                 *
#*************************************************
add_executable(unit_tests
    ${TESTS_SRC}/trie_tests.cpp
)
target_include_directories(unit_tests PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/third_party/googletest/include
    get_filename_component(REALPATH ${CMAKE_CURRENT_LIST_DIR}/../include)
)

#if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
#    target_compile_options(unit_tests
#        PRIVATE -O0   #May want to move this outside CMake.
#        PRIVATE -g
#        PRIVATE -fsanitize=address
#        PRIVATE -fsanitize=leak
#        PRIVATE -Lasan
#    )
#endif()



target_link_libraries( unit_tests
    trie
    GTest::gtest_main
)


include(GoogleTest)
gtest_add_tests(
    TARGET unit_tests
    TEST_PREFIX "utest_"
)

set(UTEST_BINARY "${CMAKE_BINARY_DIR}/tests/unit_tests")


#**************************************************
#                   Memory Checks:                *
#**************************************************
add_test(valgrind_leak_test
    COMMAND ${VALGRIND_BINARY} {UTEST_BINARY}
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

