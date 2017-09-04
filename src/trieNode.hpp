#include <algorithm>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace trie {
template <class T>
class TrieNode_t {
    std::map<unsigned int, TrieNode_t*> m_childrenMap; // used to save all the children (access / insertion O(log n))
    unsigned int m_content; // used to store the current character code in it's structure
    bool m_endOfWord;
    T* m_nodeContent;

public:
    TrieNode_t(unsigned int); // it puts the code
    unsigned int getContent(); // used to return the content
    std::vector<TrieNode_t<T>*> getChildren(); // it gets a vector containing all the childrem of this node
    TrieNode_t<T>* insertNReturnChild(unsigned int); // it inserts a children with this code and returns it
    TrieNode_t<T>* getChild(unsigned int); // retrieves and returns the relative child
    bool isEndOfWord(); // check if it's the end of a word
    void setEndOfWord(bool); // set whether it's a end of word or not
    void setValue(const T&);
    T getValue();
};

/// IMPLEMENTATION ///

template <class T>
TrieNode_t<T>::TrieNode_t(unsigned int val)
    : m_content(val)
    , m_endOfWord(false)
{
}

template <class T>
std::vector<TrieNode_t<T>*> TrieNode_t<T>::getChildren()
{
    std::vector<TrieNode_t*> nodes;
    for (auto cur : this->m_childrenMap) {
        nodes.push_back(cur.second);
    }
    return nodes;
}

template <class T>
TrieNode_t<T>* TrieNode_t<T>::insertNReturnChild(unsigned int value)
{
    TrieNode_t* node = new TrieNode_t(value);
    this->m_childrenMap.insert({ value, node });
    return node;
}

template <class T>
TrieNode_t<T>* TrieNode_t<T>::getChild(unsigned int value)
{
    auto child = this->m_childrenMap.find(value);
    if (child != this->m_childrenMap.end()) {
        return child->second;
    }
    return nullptr;
}

template <class T>
unsigned int TrieNode_t<T>::getContent()
{
    return this->m_content;
}

template <class T>
bool TrieNode_t<T>::isEndOfWord()
{
    return this->m_endOfWord;
}

template <class T>
void TrieNode_t<T>::setEndOfWord(bool eow)
{
    this->m_endOfWord = eow;
}

template <class T>
void TrieNode_t<T>::setValue(const T& content)
{
    this->m_nodeContent = new T();
    (*this->m_nodeContent) = content;
}

template <class T>
T TrieNode_t<T>::getValue()
{
    return (*this->m_nodeContent);
}

}