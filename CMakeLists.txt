cmake_minimum_required(VERSION 3.15)
project(clangd-dfa-inspection-checker)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
add_executable(main main.cpp
        ContextSensitiveAnalysis/ConstantCondition.cpp
        ContextSensitiveAnalysis/ConstantFunctionResult.cpp
        ContextSensitiveAnalysis/ConstantParameter.cpp
        ContextSensitiveAnalysis/EndlessLoop.cpp
        ContextSensitiveAnalysis/EscapeAnalysis.cpp
        ContextSensitiveAnalysis/InfiniteRecursion.cpp
        ContextSensitiveAnalysis/LoopCondition.cpp
        ContextSensitiveAnalysis/NullDereferences.cpp
        ContextSensitiveAnalysis/UnreachableCall.cpp
        ContextSensitiveAnalysis/UnreachableCode.cpp
        ContextSensitiveAnalysis/UnusedLocal.cpp
        ContextSensitiveAnalysis/UnusedParameter.cpp
        ContextSensitiveAnalysis/UnusedValue.cpp
        LocalVariableEscapesScope.cpp
        NotInitializedVariable.cpp
        MissingReturn.cpp )

add_executable(check main.cpp)