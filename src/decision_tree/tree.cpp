#include "tree.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>
#include <set>
#include "../warming_up/warming_up.h"

/**
 * It exports the tree to a dot file.
 *
 * @param filename the name of the file to write to
 */
void BinaryDecisionTree::exportToDotFile(const string &filename)
{
    assert(this->_root != NULL);
    ofstream myfile;
    myfile.open(filename + ".dot", ios::out | ios::trunc | ios::binary);

    string toWrite;
    if (this->_dico.empty())
        toWrite = this->_root->toDotString();
    else
        for (auto it = this->_uniqueNodes.begin(); it != this->_uniqueNodes.end(); ++it)
            toWrite += (*it)->toDotString(false);

    myfile << "digraph{\n" + toWrite + "\n}";
    cout << "This tree has : " << getNbNodes() << " nodes" << endl;
    myfile.close();
}

/**
 * It returns the Lukasiewicz word of the tree
 *
 * @return The Lukasiewicz word of the tree.
 */
const string &BinaryDecisionTree::getLukasWord()
{
    assert(this->_root != NULL);
    return _root->calculateLukasWord();
}

/**
 * It takes a truth table and builds a decision tree that represents it
 *
 * @param truthTable a vector of booleans.
 */
void BinaryDecisionTree::_buildTree(const vector<bool> &truthTable)
{
    if (this->_root != NULL)
        delete this->_root;
    this->_nbNodes = 0;
    this->_root = _buildTree_aux(truthTable);
    this->_root->calculateLukasWord();
}

/**
 * It builds a binary decision tree from a table
 *
 * @param number The number to be converted to binary.
 * @param size the size of the table
 */
void BinaryDecisionTree::_buildTree(const NTL::ZZ &number, const NTL::ZZ &size)
{
    _buildTree(table(number, size));
}

/**
 * It takes a number and a size, and builds a binary decision tree with the number of leaf nodes
 * equal at least to the size.
 *
 * @param number the number to be converted to binary
 * @param size the size of the tree, i.e. the number of leaf in the tree.
 */
void BinaryDecisionTree::_buildTree(const int &number, const int &size)
{
    _buildTree(NTL::ZZ(number), NTL::ZZ(size));
}

/**
 * It takes a truth table and returns a pointer to a binary decision tree that evaluates to the same
 * truth table
 *
 * @param truthTable a vector of booleans
 *
 * @return A pointer to an AbstractNode.
 */
AbstractNode *BinaryDecisionTree::_buildTree_aux(const vector<bool> &truthTable)
{
    if (truthTable.size() == 1) {
        LeafNode *node = new LeafNode(truthTable[0]);
        node->setLabel(node->valueToString());
        this->_nbNodes++;
        return node;
    }

    size_t middle = truthTable.size() / 2;
    vector<bool>::const_iterator middleIter = truthTable.cbegin();
    advance(middleIter, middle);

    vector<bool> leftHalf(truthTable.begin(), middleIter);
    vector<bool> rightHalf(middleIter, truthTable.end());

    AbstractNode *node = new InternalNode(_buildTree_aux(leftHalf), _buildTree_aux(rightHalf));
    node->setLabel("x" + to_string((unsigned long long)log2(truthTable.size())));
    this->_nbNodes += 2;
    return node;
}

void BinaryDecisionTree::_resetNodeSet()
{
    this->_uniqueNodes.clear();
    for (RefDictionary::iterator it = _dico.begin(); it != _dico.end(); ++it)
        this->_uniqueNodes.insert(it->second);
    this->_nbNodes = this->_uniqueNodes.size();
}

void BinaryDecisionTree::BasicCompression()
{
    this->_root = this->_root->basicCompression(&_dico);
    this->_resetNodeSet();
}

void BinaryDecisionTree::AdvencedCompression()
{
    this->_root = this->_root->advencedCompression(&_dico);
    this->_resetNodeSet();
}

BinaryDecisionTree::~BinaryDecisionTree()
{

    if (_dico.empty())
        delete this->_root;
    else {
        for (auto it = this->_uniqueNodes.begin(); it != this->_uniqueNodes.end(); ++it)
            free(*it);
    }
}