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
template <typename T>
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
}