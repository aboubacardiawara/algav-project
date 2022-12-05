#pragma once

#include <string>
#include <unordered_map>

using namespace std;

class AbstractNode;
typedef std::unordered_map<std::string, AbstractNode *> RefDictionary;

class AbstractNode
{
private:
    string _LukasWord = "";

public:
    AbstractNode() { }
    virtual ~AbstractNode() { }
    const string &getLukasWord() const;
    const string &setLukasWord(const string &value);
    virtual const string &calculateLukasWord() = 0;
    virtual const string toDotString() const = 0;
    AbstractNode *basicCompression(RefDictionary *const hashMap);
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

    const string toDotString() const override; //! Todo
    const string &calculateLukasWord() override;
    AbstractNode *basicCompression(RefDictionary *const hashMap)
    {
        return AbstractNode::basicCompression(hashMap);
    }

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
    const string toDotString() const override; //! Todo
    const string &calculateLukasWord() override;
    AbstractNode *basicCompression(RefDictionary *const hashMap);

private:
    //? - PrivateHelpers Funcs
};
