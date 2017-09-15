#include "person.hpp"
#include "trie.hpp"
#include <iostream>
#include <map>

int main()
{
    trie::Trie_t<Person> personTrie;
    personTrie.buildActiveNodeSet();

    // personTrie.emplaceWord("Ruan",10, "Ruan");
    std::string name = "Duan";
    std::string name2 = "Daniel";
    personTrie.emplaceWord(name, 20, name);
    personTrie.emplaceWord(name2, 23, name2);

    auto a = personTrie.searchSimilarKeyword("Dan");
    while (!a.empty()) {
        std::cout << a.top().name << '\n';
        a.pop();
    }
}
