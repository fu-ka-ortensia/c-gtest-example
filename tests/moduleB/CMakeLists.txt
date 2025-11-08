cmake_minimum_required(VERSION 3.10)

# moduleB test
add_executable(test_moduleB 
    test_moduleB.cpp
    ${CMAKE_SOURCE_DIR}/target/jchg/moduleB/moduleB.c
)

target_include_directories(test_moduleB PRIVATE 
    ${CMAKE_SOURCE_DIR}/target/jchg/moduleB
    ${CMAKE_SOURCE_DIR}/target/inc
)

# C言語ファイルのコンパイル設定
set_source_files_properties(${CMAKE_SOURCE_DIR}/target/jchg/moduleB/moduleB.c PROPERTIES LANGUAGE C)

# カバレッジオプション
target_compile_options(test_moduleB PRIVATE --coverage -fprofile-arcs -ftest-coverage)
target_link_options(test_moduleB PRIVATE --coverage -lgcov)

target_link_libraries(test_moduleB 
    gtest 
    gtest_main
    pthread
)

# テストを登録
add_test(NAME ModuleBTests COMMAND test_moduleB)
