#pragma once // Même effet que IFNDEF X DEFINE X

#include <string>
using namespace std;

/*
    A definir.
    Je veux qu'il soit assez generique.
    Comme ça s'il y'a lieu d'enrichir e reste du code sera moins touché.
  */
class Data
{

private:
    // TODO - Fields
public:
    // TODO - PublicApi
    Data(/* Fields */);
    ~Data(); // Does nothing
private:
    //? - PrivateHelpers Funcs
};

class Node
{
private:
    Node *left;
    Node *right;
    Data *value;

public:
    // TODO - PublicApi
    Node(Data *value);
    ~Node(); // TODO We delete recursivly childs nodes

private:
    //? - PrivateHelpers Funcs
};

class BinaryDecisionTree
{
private:
    // - Fields
    Node root; // Not a pointer because root live and die with tree

public:
    BinaryDecisionTree(/* Fields */);
    ~BinaryDecisionTree(); // Does nothing
    void exportToDotFile(const string &filename); // TODO write a valid .dot file of the tree
    // TODO - PublicApi
private:
    //? - PrivateHelpers Funcs
};
