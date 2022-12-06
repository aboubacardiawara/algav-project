#include "../decision_tree/tree.h"

void test_tree_build()
{
    BinaryDecisionTree test(38, 8);
    test.BasicCompression();
    cout << test.getLukasWord() << endl;
}

int main(int argc, const char **argv)
{
    test_tree_build();
    return 0;
}