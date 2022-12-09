#pragma once

#include <string>
#include <unordered_map>
#include <sstream>

#include <iostream> /* To Remove */

using namespace std;

class AbstractNode;
typedef std::unordered_map<std::string, AbstractNode *> RefDictionary;

class AbstractNode
{
private:
    string _LukasWord = "";
    string _label = "";

public:
    AbstractNode() { }
    virtual ~AbstractNode() { }
    const string &getLukasWord() const;
    const string &setLukasWord(const string &value);
    void setLabel(const string &value) { this->_label = value; }
    const string &getLabel() const { return this->_label; }
    virtual const string &calculateLukasWord() = 0;

    const string stringOfAddr() const;
    virtual const string toDotString() const;
    virtual AbstractNode *basicCompression(RefDictionary *const hashMap);
    virtual AbstractNode *advencedCompression(RefDictionary *const hashMap);
};

class LeafNode : public AbstractNode
{
private:
    bool _value;

public:
    LeafNode(bool value);
    ~LeafNode() override { }
    const bool &getValue() const;
    void setValue(const bool &value);
    const string valueToString() const;
    const string toDotString() const override;
    const string &calculateLukasWord() override;

private:
    //? - PrivateHelpers Funcs
};

class InternalNode : public AbstractNode
{
private:
    AbstractNode *_left;
    AbstractNode *_right;

public:
    InternalNode(AbstractNode *left, AbstractNode *right);
    ~InternalNode() override;
    const string toDotString() const override;
    const string &calculateLukasWord() override;
    AbstractNode *basicCompression(RefDictionary *const hashMap) override;
    AbstractNode *advencedCompression(RefDictionary *const hashMap) override;

private:
    //? - PrivateHelpers Funcs
};
