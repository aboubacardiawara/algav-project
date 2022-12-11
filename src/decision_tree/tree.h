#pragma once

#include "../decision_tree/treeClasses.h"
#include "../arithmetic_lib/include/NTL/ZZ.h"
#include <vector>
#include <set>
using namespace std;

class BinaryDecisionTree
{
private:
    AbstractNode *_root = NULL;
    RefDictionary _dico;
    set<AbstractNode *> _uniqueNodes;
    NTL::ZZ _nbNodes = NTL::ZZ::zero();

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
    const NTL::ZZ &getNbNodes() const { return this->_nbNodes; }

private:
    void _buildTree(const vector<bool> &truthTable);
    void _buildTree(const NTL::ZZ &number, const NTL::ZZ &size);
    void _buildTree(const int &number, const int &size);
    void _resetNodeSet();
    AbstractNode *_buildTree_aux(const vector<bool> &truthTable);
    AbstractNode *_buildTree_aux(const vector<bool>::const_iterator &begin,
                                 const vector<bool>::const_iterator &end,
                                 const vector<bool>::size_type &size);
};
