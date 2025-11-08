cmake_minimum_required(VERSION 3.10)

# tests root CMakeLists.txt
enable_testing()

# グローバルカバレッジ設定
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 --coverage")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

add_subdirectory(moduleA)
add_subdirectory(moduleB)
add_subdirectory(moduleC)
