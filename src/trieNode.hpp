#pragma once
#include "occurrence.hpp"
#include <list>
#include <map>
#include <vector>

namespace trie {

class TrieNode_t {
    std::map<unsigned int, TrieNode_t*> m_childrenMap; // used to save all the children (access / insertion O(log n))
    unsigned int m_content; // used to store the current character code in it's structure
    bool m_endOfStore; // used to classify this node as a "WK-end-of-word" scenario
    bool m_endOfCategory; // used to classify this node as a "WK-end-of-word" scenario
    std::list<Occurrence_t>* m_categoryOccurrences;
    std::list<Occurrence_t>* m_storeOccurrences;

public:
    TrieNode_t(unsigned int); // it puts the code
    unsigned int getContent(); // used to return the content
    std::vector<TrieNode_t*> getChildren(); // it gets a vector containing all the childrem of this node
    TrieNode_t* insertNReturnChild(unsigned int); // it inserts a children with this code and returns it
    TrieNode_t* getChild(unsigned int); // retrieves and returns the relative child
    bool isEndOfWord(); // check if it's the end of a word
    bool isEndOfCategory(); // check if it's the end of a category
    bool isEndOfStore(); // check if it's the end of a store
    void setEndOfCategory(bool); // set whether it's a end of word or not
    void setEndOfStore(bool); // set whether it's a end of word or not
    void buildOccurrences(Type);
    void addOccurrence(char, unsigned int, Type);
    std::list<const std::list<Occurrence_t>*> getOccurences(Type);
};

}
