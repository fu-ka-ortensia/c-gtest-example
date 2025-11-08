cmake_minimum_required(VERSION 3.10)

# Set module name
set(MODULE_NAME moduleB)

# Create test executable
add_executable(test_${MODULE_NAME} 
    test_${MODULE_NAME}.cpp
    ../../target/jchg/${MODULE_NAME}/${MODULE_NAME}.c
)

# Include directories
target_include_directories(test_${MODULE_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/target/jchg/${MODULE_NAME}
    ${CMAKE_SOURCE_DIR}/target/inc
    ${CMAKE_SOURCE_DIR}/fff
)

# Link libraries
target_link_libraries(test_${MODULE_NAME}
    gtest
    gtest_main
    pthread
)

# Compile options for coverage
target_compile_options(test_${MODULE_NAME} PRIVATE
    -O0 -g --coverage -fprofile-arcs -ftest-coverage
)
target_link_options(test_${MODULE_NAME} PRIVATE
    --coverage -fprofile-arcs -ftest-coverage
)

# Register test
add_test(NAME ModuleBTests COMMAND test_${MODULE_NAME})
