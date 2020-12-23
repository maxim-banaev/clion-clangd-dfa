// Local DFA
namespace loop_condition {
    void test1() {
        for (int i = 0; i < 10;) {
            if (i > 5)
                break;
        }
    }
}
