//
// Created by jetbrains on 04/10/2019.
//

#include <cstdint>
#include <iostream>

void test() {
    int a = 1;
    if (a == 1) {}


    // check the suppressing
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantCondition"
    if (a != 0) {

    }
#pragma clang diagnostic pop
}


void test1() {
    int a = 0;
    int b = 0;

    int *a_ptr = &a;
    *a_ptr = 1; // Modifies a, now a=1, b=0.

    if (a != b) {
        std::cout << "a != b\n";
    }
}

// https://youtrack.jetbrains.com/issue/CPP-13000
void test2() {
    int first = 0;
    int last = 0;

    std::cin >> first >> last;

    if (first == last) {}; // Condition is always true
}
