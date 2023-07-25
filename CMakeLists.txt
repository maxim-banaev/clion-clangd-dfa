cmake_minimum_required(VERSION 3.15)
project(clangd-dfa-inspection-checker)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
add_executable(main main.cpp
        ContextSensitiveAnalysis/ArrayIndexOutOfBounds.cpp
        ContextSensitiveAnalysis/ConstantCondition.cpp
        ContextSensitiveAnalysis/ConstantFunctionResult.cpp
        ContextSensitiveAnalysis/ConstantParameter.cpp
        ContextSensitiveAnalysis/DanglingPointer.cpp
        ContextSensitiveAnalysis/EndlessLoop.cpp
        ContextSensitiveAnalysis/EscapeAnalysis.cpp
        ContextSensitiveAnalysis/InfiniteRecursion.cpp
        ContextSensitiveAnalysis/LoopCondition.cpp
        ContextSensitiveAnalysis/NotInitializedField.cpp
        ContextSensitiveAnalysis/NullDereferences.cpp
        ContextSensitiveAnalysis/UnreachableCall.cpp
        ContextSensitiveAnalysis/UnreachableCode.cpp
        ContextSensitiveAnalysis/UnusedField.cpp
        ContextSensitiveAnalysis/UnusedLocal.cpp
        ContextSensitiveAnalysis/UnusedParameter.cpp
        ContextSensitiveAnalysis/UnusedValue.cpp
        LocalVariableEscapesScope.cpp
        NotInitializedVariable.cpp
        MissingReturn.cpp
)

add_executable(check main.cpp)