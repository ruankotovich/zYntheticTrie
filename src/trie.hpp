#pragma once
#include "trieNode.hpp"
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

namespace trie {

template <typename T>
struct ActiveNode_t {
    TrieNode_t<T>* node;
    mutable int editDistance;
    mutable int positionDistance;
    ActiveNode_t(TrieNode_t<T>*, int);
    ActiveNode_t(TrieNode_t<T>*, int, int);
    bool operator<(const ActiveNode_t<T>&) const;
};

template <typename T>
struct ActiveNodeComparator_t {
    bool operator()(const ActiveNode_t<T>&, const ActiveNode_t<T>&) const;
};

template <typename T, typename C>
class Trie_t {
    TrieNode_t<T>* m_lambdaNode; // used to indicate the first node
    std::unordered_map<unsigned int, unsigned int> m_characterMap; // used to map all the characters to it's defined codes
    std::unordered_map<unsigned int, char> m_reverseCharacterMap; // used to map all the defined codes to it's characters (4fun)
    std::set<ActiveNode_t<T>> m_activeNodeSet; // uset to save the main activeNode set
    std::set<std::string> m_stopWords;
    void push_string_to_wchar(wchar_t*, std::string&); // push a string into a wchar_t array
    int m_searchLimitThreshold; // threshold used for delimit the answers amount (default : 5)
    int m_fuzzyLimitThreshold; // threshold used for delimit the edit distance from node (default : 1)
    std::set<ActiveNode_t<T>> buildNewSet(std::set<ActiveNode_t<T>>&, unsigned int);

public:
    Trie_t(); // default constructor, receiving the filename which wordmap will be readen
    void encodeCharacters(const std::string&); // used to start the encoding/decoding vector of  the characters contained on the file
    void addStopWords(const std::string&);
    bool isStopWord(std::string);
    void printTrie(); // print the tree { see the tree on http://mshang.ca/syntree/ =) }
    void putWord(std::string&, const T&); // include a string in the trie structure
    void setSearchLimitThreshold(int); // set the m_searchLimitThreshold
    void setFuzzyLimitThreshold(int); // set the m_fuzzyLimitThreshold
    void buildActiveNodeSet(); // used to build the activeNode set at once
    std::priority_queue<T, std::vector<T>, C> searchSimilarKeyword(const std::string&);
};
}
