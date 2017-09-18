#include "person.hpp"
#include "trie.hpp"
#include <iostream>
#include <map>

int main()
{
    trie::Trie_t<Person> personTrie;
    personTrie.buildActiveNodeSet();

    std::string name = "Duan";
    std::string name2 = "Daniel";
    std::string name3 = "Soto Bana";
    std::string name4 = "Roab Soto";
    std::string name5 = "Soto Bananation";
    std::string name6 = "Soto Bana NAO";
    std::string name7 = "Dougras Danyel";
    std::string name8 = "Eu sou o dougras";

    personTrie.emplaceWord(name, 20, name);
    personTrie.emplaceWord(name2, 22, name2);
    personTrie.emplaceWord(name3, 23, name3);
    personTrie.emplaceWord(name4, 24, name4);
    personTrie.emplaceWord(name5, 25, name5);
    personTrie.emplaceWord(name6, 26, name6);
    personTrie.emplaceWord(name7, 27, name7);
    personTrie.emplaceWord(name8, 28, name8);

    std::string search;
    while (std::cin >> search) {
        std::cout << " --- \n";
        auto a = personTrie.searchSimilarKeyword(search);
        while (!a.empty()) {
            std::cout << a.top().name << '\n';
            a.pop();
        }
    }
}
