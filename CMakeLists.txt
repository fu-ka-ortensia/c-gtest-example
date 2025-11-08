cmake_minimum_required(VERSION 3.10)
project(C_Test_Project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# デバッグ情報とカバレッジフラグを追加
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage -lgcov")

# テストを有効化
enable_testing()

# GoogleTest設定
add_subdirectory(GoogleTest)

# テストディレクトリを追加
add_subdirectory(tests)
