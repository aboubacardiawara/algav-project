#pragma once

#include "../decision_tree/treeClasses.h"
#include "../arithmetic_lib/include/NTL/ZZ.h"
#include <vector>
using namespace std;

class BinaryDecisionTree
{
private:
    AbstractNode *_root = NULL;
    RefDictionary _dico;

public:
    BinaryDecisionTree(const vector<bool> &truthTable) { this->_buildTree(truthTable); }
    BinaryDecisionTree(const NTL::ZZ &number, const NTL::ZZ &size) { this->_buildTree(number, size); }
    BinaryDecisionTree(const int &number, const int &size) { this->_buildTree(number, size); }
    ~BinaryDecisionTree();

    void exportToDotFile(const string &filename);
    const string &getLukasWord();
    const RefDictionary &getDico() const { return this->_dico; }
    void BasicCompression();
    void AdvencedCompression();

private:
    void _buildTree(const vector<bool> &truthTable);
    void _buildTree(const NTL::ZZ &number, const NTL::ZZ &size);
    void _buildTree(const int &number, const int &size);
    AbstractNode *_buildTree_aux(const vector<bool> &truthTable);
};
