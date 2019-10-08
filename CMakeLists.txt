cmake_minimum_required(VERSION 3.15)
project(clangd-dfa-inspection-checker)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp
        ContextSensitiveAnalysis/ConstantCondition.cpp
        ContextSensitiveAnalysis/NullDereferences.cpp
        ContextSensitiveAnalysis/UnreachableCode.cpp
        ContextSensitiveAnalysis/EndlessLoop.cpp
        ContextSensitiveAnalysis/InfiniteRecursion.cpp
        ContextSensitiveAnalysis/EscapeAnalysis.cpp ContextSensitiveAnalysis/UnusedLocal.cpp LocalVariableEscapesScope.cpp NotInitializedVariable.cpp MissingReturn.cpp)