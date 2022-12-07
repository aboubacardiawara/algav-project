#include "treeClasses.h"

/**
 * This function returns the LukasWord of the AbstractNode.
 *
 * @return The LukasWord of the node.
 */
const string &AbstractNode::getLukasWord() const
{
    return this->_LukasWord;
}

/**
 * This function sets the value of the private member variable _LukasWord to the value of the
 * parameter value.
 *
 * @return The value of the variable.
 */
const string &AbstractNode::setLukasWord(const string &value)
{
    return this->_LukasWord = value;
}

/**
 * If the node is already in the hash map, then delete the node and return the node from the hash
 * map. Otherwise, add the node to the hash map and return the node
 *
 * @param hashMap A hash map that maps a Lukas word to a node.
 *
 * @return A pointer to the node.
 */
AbstractNode *AbstractNode::basicCompression(RefDictionary *const hashMap)
{
    RefDictionary::iterator sameNode = hashMap->find(getLukasWord());
    if (sameNode != hashMap->end()) {
        free(this);
        return sameNode->second;
    }
    hashMap->insert({ getLukasWord(), this });
    return this;
}

/**
 * `LeafNode` is a constructor that takes a `bool` and sets the `_value` member variable to that
 * `bool`
 *
 * @param value The value of the leaf node.
 */
LeafNode::LeafNode(bool value)
{
    this->_value = value;
}

/**
 * It returns the value of the leaf node.
 *
 * @return The value of the leaf node.
 */
const bool &LeafNode::getValue() const
{
    return this->_value;
}

/**
 * Sets the value of the leaf node.
 *
 * @param value The value of the leaf node.
 */
void LeafNode::setValue(const bool &value)
{
    this->_value = value;
}

/**
 * If the value is true, return the string "true", otherwise return the string "false"
 *
 * @return A string representation of the value of the node.
 */
const string LeafNode::valueToString() const
{
    return this->_value ? "true" : "false";
}

const string LeafNode::toDotString() const
{
    return ""; //!Todo
}

/**
 * The function returns the string "(value)"
 *
 * @return The Lukasiewicz word of the node.
 */
const string &LeafNode::calculateLukasWord()
{
    return setLukasWord(valueToString());
}

/**
 * This function creates a new internal node with the given left and right children.
 *
 * @param left The left child of the node.
 * @param right The right child of the node.
 */
InternalNode::InternalNode(AbstractNode *left, AbstractNode *right)
{
    this->_left = left;
    this->_right = right;
}

/**
 * Delete the left and right children of this node.
 */
InternalNode::~InternalNode()
{
    delete this->_left;
    delete this->_right;
}

const string InternalNode::toDotString() const
{
    return "";
} //! Todo

/**
 * The Lukasiewicz word of an internal node is the concatenation of the Lukasiewicz words of its
 * left and right children, with parentheses around the whole thing
 *
 * @return The Lukasiewicz word of the internal node.
 */
const string &InternalNode::calculateLukasWord()
{
    return setLukasWord("(" + _left->calculateLukasWord() + ")" + "(" +_right->calculateLukasWord() + ")");
}

/**
 * Compress a InternalNode
 *
 * @param hashMap A hash map that maps a Lukas word to a node.
 *
 * @return The node that is being returned is the node that is being compressed.
 */
AbstractNode *InternalNode::basicCompression(RefDictionary *const hashMap)
{
    this->_left = this->_left->basicCompression(hashMap);
    this->_right = this->_right->basicCompression(hashMap);
    return AbstractNode::basicCompression(hashMap);
}