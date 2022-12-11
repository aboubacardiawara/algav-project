#include "../decision_tree/tree.h"
#include <cassert>
#include <chrono>
#include <iostream>
#include <iterator>
#include <string>
#include <thread>
#include <fstream>
#include <functional>
#include <algorithm>
#include <random>
#include <unordered_set>

#define NB_THREADS 8

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

long long parallel_for(NTL::ZZ nb_elements, function<void(const NTL::ZZ &start, const NTL::ZZ &end)> functor)
{
    auto chronoStart = chrono::high_resolution_clock::now();
    NTL::ZZ batch_size = nb_elements / NB_THREADS;
    NTL::ZZ batch_remainder = nb_elements % NTL::ZZ(NB_THREADS);
    vector<thread> my_threads(NB_THREADS);
    NTL::ZZ start, end;

    for (unsigned i = 0; i < NB_THREADS; ++i) {
        start = i * batch_size;
        end = start + batch_size;
        my_threads[i] = thread(functor, start, end);
    }

    start = NB_THREADS * batch_size;
    end = start + batch_remainder;
    functor(start, end);
    for_each(my_threads.begin(), my_threads.end(), mem_fn(&thread::join));

    auto elapsedTime =
            chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - chronoStart)
                    .count();
    return elapsedTime;
}

void writeResults(const int &nbVariable, const NTL::ZZ &nbPossibilities,
                  const unordered_map<unsigned int, NTL::ZZ *> &treeSizes, const float &calculationTime)
{
    ofstream myfile;
    string path = "Visualisation/ExaustiveTestResults/Variable" + to_string(nbVariable) + ".txt";
    myfile.open(path, ios::out | ios::trunc | ios::binary);

    myfile << "NbVariable: " << nbVariable << endl;
    myfile << "Number of Tree: " << nbPossibilities << endl;
    myfile << "Found values: " << treeSizes.size() << endl;
    myfile << fixed << "Total Calculations Took: " << (double)calculationTime / pow(10, 9) << " seconds"
           << endl;
    myfile << fixed << "Took: " << NTL::conv<double>(NTL::ZZ(calculationTime) / nbPossibilities) / pow(10, 9)
           << " seconds per Tree" << endl;

    for (auto it = treeSizes.begin(); it != treeSizes.end(); it++) {
        myfile << "Nb Boolean Functions: " << *it->second << endl;
        myfile << "Nb Nodes: " << it->first << endl;
        delete it->second;
    }
    myfile.close();
}

void test_extensive(unsigned int nbVariable)
{
    int treeSize = pow(2, nbVariable);
    NTL::ZZ nbPossibilities = NTL::power2_ZZ(treeSize);
    unordered_map<unsigned int, NTL::ZZ *> treeSizes;
    float calculationTime =
            parallel_for(nbPossibilities, [&treeSize, &treeSizes](const NTL::ZZ &s, const NTL::ZZ &e) {
                unordered_map<unsigned int, NTL::ZZ *> asyncSizeMap;
                unordered_map<unsigned int, NTL::ZZ *>::iterator result;
                int nbTreeNodes;

                for (NTL::ZZ i = s; i < e; i++) {
                    BinaryDecisionTree tree(i, NTL::ZZ(treeSize));
                    tree.AdvencedCompression();
                    nbTreeNodes = NTL::conv<int>(tree.getNbNodes());
                    result = asyncSizeMap.find(nbTreeNodes);
                    if (result == asyncSizeMap.end())
                        asyncSizeMap.insert({ nbTreeNodes, new NTL::ZZ(1) });
                    else
                        (*result->second)++;
                }

                for (auto it = asyncSizeMap.begin(); it != asyncSizeMap.end(); it++) {
                    result = treeSizes.find(it->first);
                    if (result == treeSizes.end())
                        treeSizes.insert({ it->first, it->second });
                    else
                        *result->second += *it->second;
                }
            });

    writeResults(nbVariable, nbPossibilities, treeSizes, calculationTime);
}

vector<NTL::ZZ> pick(unsigned int nbBitMax, NTL::ZZ k)
{
    random_device rd;
    mt19937 gen(rd());
    unordered_set<NTL::ZZ *> elems;
    while (elems.size() < k)
        elems.insert(new NTL::ZZ(NTL::RandomBits_ZZ(nbBitMax)));
    vector<NTL::ZZ> result;
    for (auto it = elems.begin(); it != elems.end(); it++) {
        result.push_back(**it);
        free(*it);
    }
    shuffle(result.begin(), result.end(), gen);
    return result;
}

void test_sampling(unsigned int nbVariable, unsigned int nbSamples)
{
    int treeSize = pow(2, nbVariable);
    NTL::ZZ nbPossibilities = NTL::ZZ(nbSamples);
    cout << "nbPossibilities: " << nbPossibilities << endl;
    unordered_map<unsigned int, NTL::ZZ *> treeSizes;
    unordered_map<unsigned int, NTL::ZZ *>::iterator result;
    vector<NTL::ZZ> vec = pick(treeSize, nbPossibilities);
    int nbTreeNodes;

    auto chronoStart = chrono::high_resolution_clock::now();
    cout << "Computing Samples" << endl;
    for (vector<NTL::ZZ>::iterator it = vec.begin(); it != vec.end(); it++) {
        BinaryDecisionTree tree(*it, NTL::ZZ(treeSize));
        tree.AdvencedCompression();
        nbTreeNodes = NTL::conv<int>(tree.getNbNodes());
        result = treeSizes.find(nbTreeNodes);
        if (result == treeSizes.end())
            treeSizes.insert({ nbTreeNodes, new NTL::ZZ(1) });
        else
            (*result->second)++;
    }

    writeResults(
            nbVariable, nbPossibilities, treeSizes,
            chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - chronoStart)
                    .count());
}

int main(int argc, char **argv)
{
    test_lukaword_computation();
    for (size_t i = 1; i <= 4; i++)
        test_extensive(i);

    // test_extensive(5);

    test_sampling(5, 500003);
    test_sampling(6, 400003);
    test_sampling(7, 486892);
    test_sampling(8, 56343);
    test_sampling(9, 94999);
    test_sampling(10, 17975);

    if (argc > 1) {
        BinaryDecisionTree tree(argv[1]);
        string filename = string("Demo") + argv[1];
        tree.exportToDotFile(filename);
        tree.AdvencedCompression();
        tree.exportToDotFile(filename + "_comp");
    }

    return 0;
}