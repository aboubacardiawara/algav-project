#include "../decision_tree/tree.h"
#include <assert.h>


void test_tree_build()
{
    BinaryDecisionTree test(38, 8);
}

void test_lukaword_computation()
{
    BinaryDecisionTree tree(38, 8);
    BinaryDecisionTree tree2(2, 2);
    string expected_luka_word = "(((false)(true))((true)(false)))(((false)(true))((false)(false)))"; 
    string expected_luka_word2 = "(false)(true)"; 

    assert(tree.getLukasWord() == expected_luka_word && "test luka for table of 38");
    assert(tree2.getLukasWord() == expected_luka_word2 && "test luka for table of 2");
    
    // assert not
    assert(tree.getLukasWord() != expected_luka_word2 && "test luka for table of 38");
    assert(tree2.getLukasWord() != expected_luka_word && "test luka for table of 2");
}

void test_compression() {
    BinaryDecisionTree tree(38, 8);
    // size before compression

    // size after compression
}

int main(int argc, const char **argv)
{
    //test_tree_build();
    test_lukaword_computation();
    return 0;
}