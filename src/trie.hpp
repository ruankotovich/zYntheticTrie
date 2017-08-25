#pragma once
#include "trieNode.hpp"
#include "unionData.hpp"
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

namespace trie {

struct ActiveNode_t {
    TrieNode_t* node;
    mutable int editDistance;
    mutable int positionDistance;
    ActiveNode_t(TrieNode_t*, int);
    ActiveNode_t(TrieNode_t*, int, int);
    bool operator<(const ActiveNode_t&) const;
};

struct ActiveNodeComparator_t {
    bool operator()(const ActiveNode_t&, const ActiveNode_t&) const;
};

class Trie_t {
    TrieNode_t* m_lambdaNode; // used to indicate the first node
    std::unordered_map<unsigned int, unsigned int> m_characterMap; // used to map all the characters to it's defined codes
    std::unordered_map<unsigned int, char> m_reverseCharacterMap; // used to map all the defined codes to it's characters (4fun)
    std::set<ActiveNode_t> m_activeNodeSet; // uset to save the main activeNode set
    std::set<std::string> m_stopWords;

    void push_string_to_wchar(wchar_t*, std::string&); // push a string into a wchar_t array
    int m_searchLimitThreshold; // threshold used for delimit the answers amount (default : 5)
    int m_fuzzyLimitThreshold; // threshold used for delimit the edit distance from node (default : 1)

    std::set<ActiveNode_t> buildNewSet(std::set<ActiveNode_t>&, unsigned int);

    std::unordered_map<unsigned int, UData::Store_t> m_storeTable;
    std::unordered_map<unsigned int, UData::Category_t> m_categoryTable;

    std::map<unsigned int, std::set<unsigned int>> m_relationStoCat;
    std::map<unsigned int, std::set<unsigned int>> m_relationCatSto;

public:
    Trie_t(); // default constructor, receiving the filename which wordmap will be readen
    void encodeCharacters(const std::string&); // used to start the encoding/decoding vector of  the characters contained on the file
    void addStopWords(const std::string&);
    bool isStopWord(std::string);
    void printTrie(); // print the tree { see the tree on http://mshang.ca/syntree/ =) }
    void putWordAsCategory(std::string&, char, unsigned int); // include a string in the trie structure
    void putWordAsStore(std::string&, char, unsigned int); // include a string in the trie structure
    void setSearchLimitThreshold(int); // set the m_searchLimitThreshold
    void setFuzzyLimitThreshold(int); // set the m_fuzzyLimitThreshold
    void buildActiveNodeSet(); // used to build the activeNode set at once
    void printData();
    std::priority_queue<Occurrence_t, std::vector<Occurrence_t>, OccurrencePriorityComparator_t> searchSimilarKeyword(const std::string&, Type type);

    std::set<UData::Category_t, UData::CategoryComparator_t> getCategoriesByStore(unsigned int id);
    std::set<UData::Store_t, UData::StoreComparator_t> getStoresByCategory(unsigned int id);

    bool addRelation(unsigned int, unsigned int);
    bool removeRelation(unsigned int, unsigned int);
    bool insertCategory(unsigned int, const std::string&);
    bool insertStore(unsigned int, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
    bool updateStore(unsigned int, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
    bool updateCategory(unsigned int, const std::string&);
    bool removeStore(unsigned int, bool);
    bool removeCategory(unsigned int, bool);
    UData::Store_t getStore(unsigned int);
    UData::Category_t getCategory(unsigned int);
};
}
