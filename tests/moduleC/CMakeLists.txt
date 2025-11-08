cmake_minimum_required(VERSION 3.10)

# moduleC test
add_executable(test_moduleC 
    test_moduleC.cpp
)

target_include_directories(test_moduleC PRIVATE 
    ${CMAKE_SOURCE_DIR}/target/jchg/moduleC
    ${CMAKE_SOURCE_DIR}/target/inc
    ${CMAKE_SOURCE_DIR}/fff
)

# カバレッジオプション
target_compile_options(test_moduleC PRIVATE --coverage -fprofile-arcs -ftest-coverage)
target_link_options(test_moduleC PRIVATE --coverage -lgcov)

target_link_libraries(test_moduleC 
    gtest 
    gtest_main
    pthread
)

# テストを登録
add_test(NAME ModuleCTests COMMAND test_moduleC)
