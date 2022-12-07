#include "../decision_tree/tree.h"
#include <assert.h>

void test_tree_build()
{
    BinaryDecisionTree test(38, 8);
    //test.BasicCompression();
    cout << test.getLukasWord() << endl;
    string expected_luka_word = "(((false)(true))((true)(false)))(((false)(true))((false)(false)))"; 
    cout << expected_luka_word << endl;
    assert(test.getLukasWord() == expected_luka_word && "test luka word");
}

int main(int argc, const char **argv)
{
    test_tree_build();
    return 0;
}