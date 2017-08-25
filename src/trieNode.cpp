#include "trieNode.hpp"
#include <iostream>

using namespace trie;

// TrieNode_t public methods
TrieNode_t::TrieNode_t(unsigned int val)
{
    this->m_content = val;
    this->m_endOfStore = false;
    this->m_endOfCategory = false;
}

std::vector<TrieNode_t*> TrieNode_t::getChildren()
{
    std::vector<TrieNode_t*> nodes;
    for (auto cur : this->m_childrenMap) {
        nodes.push_back(cur.second);
    }
    return nodes;
}

TrieNode_t* TrieNode_t::insertNReturnChild(unsigned int value)
{
    TrieNode_t* node = new TrieNode_t(value);
    this->m_childrenMap.insert({ value, node });
    return node;
}

TrieNode_t* TrieNode_t::getChild(unsigned int value)
{
    auto child = this->m_childrenMap.find(value);
    if (child != this->m_childrenMap.end()) {
        return child->second;
    }
    return nullptr;
}

unsigned int TrieNode_t::getContent()
{
    return this->m_content;
}

void TrieNode_t::setEndOfCategory(bool isEnd)
{
    this->m_endOfCategory = isEnd;
}

void TrieNode_t::setEndOfStore(bool isEnd)
{
    this->m_endOfStore = isEnd;
}

bool TrieNode_t::isEndOfCategory()
{
    return this->m_endOfCategory;
}

bool TrieNode_t::isEndOfStore()
{
    return this->m_endOfStore;
}

bool TrieNode_t::isEndOfWord()
{
    return this->m_endOfStore | this->m_endOfCategory;
}

void TrieNode_t::buildOccurrences(Type type)
{
    if (type == STORE) {
        this->m_storeOccurrences = new std::list<Occurrence_t>();
    } else {
        this->m_categoryOccurrences = new std::list<Occurrence_t>();
    }
}

void TrieNode_t::addOccurrence(char position, unsigned int reg, Type type)
{
    if (type == STORE) {
        this->m_storeOccurrences->emplace(this->m_storeOccurrences->begin(), reg, position, type);
    } else {
        this->m_categoryOccurrences->emplace(this->m_categoryOccurrences->begin(), reg, position, type);
    }
}

std::list<const std::list<Occurrence_t>*> TrieNode_t::getOccurences(Type type)
{
    std::list<const std::list<Occurrence_t>*> operList;

    if (type == STORE) {
        if (this->m_endOfStore) {
            operList.emplace_back(this->m_storeOccurrences);
        }
    } else if (type == CATEGORY) {
        if (this->m_endOfCategory) {
            operList.emplace_back(this->m_categoryOccurrences);
        }
    } else {

        if (this->m_endOfStore) {
            operList.emplace_back(this->m_storeOccurrences);
        }

        if (this->m_endOfCategory) {
            operList.emplace_back(this->m_categoryOccurrences);
        }
    }

    return operList;
}
