// summary: should be 4 warnings
#include <string>
#include <vector>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"
#pragma ide diagnostic ignored "UnusedValue"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
// Local DFA
namespace local_variable_escapes_scope {
    std::string something_string;
    void test1() {
        char val[10];
        something_string = val; // shouldn't warn here
    }

    char* char_pointer_char;
    void test2() {
        char val[10];
        char_pointer_char = val; // warn here
    }

    std::vector<int> int_vector;
    void test3() {
        std::vector<int> val = {1, 2};
        int_vector = val; // shouldn't warn here
    }

    class [[maybe_unused]] Test4 {
        std::string something_string_field;
        char* char_pointer_char_filed;
    public:
        void test4() {
            char val[10];
            something_string = val; // shouldn't warn here
            char_pointer_char = val; // warn here
        }

        static void test4_1() {
            char val[10];
            something_string = val; // shouldn't warn here
            char_pointer_char = val; // warn here
        }

        void test4_2() {
            char val[10];
            something_string_field = val; // shouldn't warn here
            char_pointer_char_filed = val; // shouldn't warn here
        }
    };

    void test5(char val[10]) {
        something_string = val; // shouldn't warn here
        char_pointer_char = val; // shouldn't warn here
    }

    struct Dummy {};

    Dummy* something_dummy;
    void test6() {
        Dummy val[10];
        something_dummy = val; // warn here
    }
}


// Global DFA
namespace {
    std::string something_string;
    void test1() {
        char val[10];
        something_string = val; // shouldn't warn here
    }

    char* char_pointer_char;
    void test2() {
        char val[10];
        char_pointer_char = val; // shouldn't warn here
    }
    std::vector<int> int_vector;
    void test3() {
        std::vector<int> val = {1, 2};
        int_vector = val; // shouldn't warn here
    }
} // namespace

void checkGlobalDFA() {
    test1();
    test2();
    test3();
}
#pragma clang diagnostic pop