cmake_minimum_required(VERSION 3.10)

# moduleA test
add_executable(test_moduleA 
    test_moduleA.cpp
    ${CMAKE_SOURCE_DIR}/target/jchg/moduleA/moduleA.c
)

target_include_directories(test_moduleA PRIVATE 
    ${CMAKE_SOURCE_DIR}/target/jchg/moduleA
    ${CMAKE_SOURCE_DIR}/target/inc
)

# C言語ファイルのコンパイル設定
set_source_files_properties(${CMAKE_SOURCE_DIR}/target/jchg/moduleA/moduleA.c PROPERTIES LANGUAGE C)

# カバレッジオプション
target_compile_options(test_moduleA PRIVATE --coverage -fprofile-arcs -ftest-coverage)
target_link_options(test_moduleA PRIVATE --coverage -lgcov)

target_link_libraries(test_moduleA 
    gtest 
    gtest_main
    pthread
)

# テストを登録
add_test(NAME ModuleATests COMMAND test_moduleA)
