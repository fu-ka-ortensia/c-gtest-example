cmake_minimum_required(VERSION 3.10)

# モジュール名を設定
set(MODULE_NAME moduleA)

# テスト実行ファイルを作成
add_executable(test_${MODULE_NAME} 
    test_${MODULE_NAME}.cpp
    ../../target/jchg/${MODULE_NAME}/${MODULE_NAME}.c
)

# インクルードディレクトリを設定
target_include_directories(test_${MODULE_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/target/jchg/${MODULE_NAME}
    ${CMAKE_SOURCE_DIR}/target/inc
    ${CMAKE_SOURCE_DIR}/fff
)

# ライブラリをリンク
target_link_libraries(test_${MODULE_NAME}
    gtest
    gtest_main
    pthread
)

# カバレッジコンパイルオプション
target_compile_options(test_${MODULE_NAME} PRIVATE
    -O0 -g --coverage -fprofile-arcs -ftest-coverage
)
target_link_options(test_${MODULE_NAME} PRIVATE
    --coverage -fprofile-arcs -ftest-coverage
)

# テストを登録
add_test(NAME ModuleATests COMMAND test_${MODULE_NAME})
