#include "tree.h"
#include <cstdlib>
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
    const string path = "Visualisation/" + filename;
    assert(this->_root != NULL);
    ofstream myfile;
    myfile.open(path + ".dot", ios::out | ios::trunc | ios::binary);

    string toWrite;
    if (this->_dico.empty())
        toWrite = this->_root->toDotString();
    else
        for (auto it = this->_uniqueNodes.begin(); it != this->_uniqueNodes.end(); ++it)
            toWrite += (*it)->toDotString(false);

    myfile << "digraph{\n" + toWrite + "\n}";
    myfile.close();

    system(("dot -Tjpeg " + path + ".dot" + "> " + path + ".jpg").c_str());
    system(("rm " + path + ".dot").c_str());
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
    for (auto it = this->_uniqueNodes.begin(); it != this->_uniqueNodes.end(); ++it)
        delete (*it);
    this->_uniqueNodes.clear();

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

void BinaryDecisionTree::_buildTree(const string &arbitraryNumber)
{
    NTL::ZZ n = NTL::conv<NTL::ZZ>(arbitraryNumber.c_str());
    vector<bool> t = decomposition(n);

    float i = log2(t.size());
    return _buildTree(n, NTL::power2_ZZ(ceil(i)));
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
    return this->_buildTree_aux(truthTable.begin(), truthTable.end(), truthTable.size());
}
AbstractNode *BinaryDecisionTree::_buildTree_aux(const vector<bool>::const_iterator &begin,
                                                 const vector<bool>::const_iterator &end,
                                                 const vector<bool>::size_type &size)
{
    if (size == 1) {
        LeafNode *node = new LeafNode(*begin);
        node->setLabel(node->valueToString());
        this->_nbNodes++;
        this->_uniqueNodes.insert(node);
        return node;
    }

    vector<bool>::const_iterator middleIter = begin;
    vector<bool>::size_type middle = size / 2;
    for (vector<bool>::size_type i = middle; i > 0; i--)
        middleIter++;

    AbstractNode *node = new InternalNode(_buildTree_aux(begin, middleIter, middle),
                                          _buildTree_aux(middleIter, end, middle));

    node->setLabel("x" + to_string((unsigned long long)log2(middle) + 1));
    this->_nbNodes += 2;
    this->_uniqueNodes.insert(node);
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

    for (auto it = this->_uniqueNodes.begin(); it != this->_uniqueNodes.end(); ++it)
        delete (*it);
}