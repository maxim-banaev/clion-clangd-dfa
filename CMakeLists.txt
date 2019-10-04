cmake_minimum_required(VERSION 3.15)
project(clangd-dfa-inspection-checker)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp ContextSensitiveAnalysis/ConstantCondition.cpp)