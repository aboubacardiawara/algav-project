#include "../decision_tree/tree.h"
#include <assert.h>
#include <chrono>
#include <string>
#include <ctime>
#include <unistd.h>
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
    BinaryDecisionTree tree(NTL::conv<NTL::ZZ>("63688"), NTL::conv<NTL::ZZ>("16"));
    tree.AdvencedCompression();
    tree.exportToDotFile("Test");
}

void test_extensive_test(int nbVariable)
{
    int treeSize = pow(2, nbVariable);
    NTL::ZZ nbPossibilities = NTL::power2_ZZ(treeSize);
    set<int> treeSizes;

    const clock_t time = clock();
    for (NTL::ZZ i = NTL::ZZ::zero(); i < nbPossibilities; i++) {
        cout << i << endl;
        BinaryDecisionTree tree(i, NTL::ZZ(treeSize));
        tree.AdvencedCompression();
        treeSizes.insert(tree.getNbNodes());
    }
    float took = float(clock() - time) / CLOCKS_PER_SEC;
    float average = NTL::conv<float>((NTL::ZZ(clock() - time) / nbPossibilities)) / CLOCKS_PER_SEC;
    cout << "NbVariable: " << nbVariable << endl;
    cout << "Total Calculations Took : " << took << " seconds" << endl;
    cout << "Took : " << average << " seconds per Tree" << endl;
    cout << "Found values : " << treeSizes.size() << endl;
}

int main()
{
    test_extensive_test(5);
    return 0;
}