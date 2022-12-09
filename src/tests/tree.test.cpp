#include "../decision_tree/tree.h"
#include <assert.h>

void test_lukaword_computation()
{
    BinaryDecisionTree tree(38, 8);
    BinaryDecisionTree tree2(2, 2);

    string expected_luka_word =
            "x3(x2(x1(false)(true))(x1(true)(false)))(x2(x1(false)(true))(x1(false)(false)))";
    string expected_luka_word2 = "x1(false)(true)";

    assert(tree.getLukasWord() == expected_luka_word && "test luka for table of 38");
    assert(tree2.getLukasWord() == expected_luka_word2 && "test luka for table of 2");

    // assert not
    assert(tree.getLukasWord() != expected_luka_word2 && "test luka for table of 38");
    assert(tree2.getLukasWord() != expected_luka_word && "test luka for table of 2");
}

void test_exportation()
{
    BinaryDecisionTree tree(NTL::conv<NTL::ZZ>("38"), NTL::conv<NTL::ZZ>("8"));
    tree.AdvencedCompression();
    tree.exportToDotFile("Test");
}

int main(int argc, const char **argv)
{
    test_lukaword_computation();
    test_exportation();
    return 0;
}