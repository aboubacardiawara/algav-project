#pragma once

#include "../decision_tree/treeClasses.h"
#include "../arithmetic_lib/include/NTL/ZZ.h"
#include <vector>
using namespace std;

class BinaryDecisionTree
{
private:
    AbstractNode *_root = NULL;

public:
    BinaryDecisionTree(const vector<bool> &truthTable) { this->_buildTree(truthTable); }
    BinaryDecisionTree(const NTL::ZZ &number, const NTL::ZZ &size) { this->_buildTree(number, size); }
    BinaryDecisionTree(const int &number, const int &size) { this->_buildTree(number, size); }
    ~BinaryDecisionTree() { delete this->_root; }

    void exportToDotFile(const string &filename); //! Todo
    const string &getLukasWord();
    void BasicCompression();

private:
    void _buildTree(const vector<bool> &truthTable);
    void _buildTree(const NTL::ZZ &number, const NTL::ZZ &size);
    void _buildTree(const int &number, const int &size);
    AbstractNode *_buildTree_aux(const vector<bool> &truthTable);
};
