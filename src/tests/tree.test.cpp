#include "../decision_tree/tree.h"
#include <format>

void test_tree_build()
{
    BinaryDecisionTree test(NTL::ZZ(3083208324893420823), NTL::ZZ(62));
    test.BasicCompression();
    cout << test.getLukasWord() << endl;
}

int main(int argc, const char **argv)
{
    test_tree_build();
    return 0;
}