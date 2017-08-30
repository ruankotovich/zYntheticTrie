#include "trieNode.hpp"

using namespace trie;

template <typename T>
TrieNode_t<T>::TrieNode_t(unsigned int val)
    : m_content(val)
    , m_endOfWord(false)
{
}

template <typename T>
std::vector<TrieNode_t<T>*> TrieNode_t<T>::getChildren()
{
    std::vector<TrieNode_t*> nodes;
    for (auto cur : this->m_childrenMap) {
        nodes.push_back(cur.second);
    }
    return nodes;
}

template <typename T>
TrieNode_t<T>* TrieNode_t<T>::insertNReturnChild(unsigned int value)
{
    TrieNode_t* node = new TrieNode_t(value);
    this->m_childrenMap.insert({ value, node });
    return node;
}

template <typename T>
TrieNode_t<T>* TrieNode_t<T>::getChild(unsigned int value)
{
    auto child = this->m_childrenMap.find(value);
    if (child != this->m_childrenMap.end()) {
        return child->second;
    }
    return nullptr;
}

template <typename T>
unsigned int TrieNode_t<T>::getContent()
{
    return this->m_content;
}

template <typename T>
bool TrieNode_t<T>::isEndOfWord()
{
    return this->m_endOfWord;
}

template <typename T>
void TrieNode_t<T>::setEndOfWord(bool eow)
{
    this->m_endOfWord = eow;
}

template <typename T>
void TrieNode_t<T>::setValue(const T& content)
{
    this->m_nodeContent = new T();
    (*this->m_nodeContent) = content;
}

template <typename T>
T TrieNode_t<T>::getValue()
{
    return (*this->m_nodeContent);
}
