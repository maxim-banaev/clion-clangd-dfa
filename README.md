# Data Flow Analysis

Data Flow Analysis (DFA) tracks the flow of data in your code and detects potential issues based on that analysis. 
For example, DFA checks can identify conditions that are always false or always true, endless loops, missing return 
statements, infinite recursion, and other potential vulnerabilities.

Data flow analysis in CLion is call-context sensitive:

* each function is analysed for each call site separately,

* parameters and return values for different call sites are also analysed separately.

DFA can work globally (taking a whole translation unit of a program as a single unit for analysis) or locally 
(within a single function).

Global DFA works within the translation unit on all usages of the functions or fields that are guaranteed to be local 
inside it. This helps detect potential issues which can’t be captured by Local DFA.


## Description

The CMake-based project which contains list of test cases to track regression and vulnerability
