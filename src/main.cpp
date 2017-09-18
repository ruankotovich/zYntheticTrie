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
    std::string name3 = "Soto";
    std::string name4 = "Roab";
    std::string name5 = "Bananation";
    std::string name6 = "SotoBanaNAO";
    std::string name7 = "Danyel";
    std::string name8 = "dougras";
    std::string name9 = "Duan";

    personTrie.emplaceIndividualWord(name, 20, name);
    personTrie.putIndividualWord(name2, Person(22, name2));
    personTrie.putIndividualWord(name3, Person(23, name3));
    personTrie.putIndividualWord(name4, Person(24, name4));
    personTrie.putIndividualWord(name5, Person(25, name5));
    personTrie.putIndividualWord(name6, Person(26, name6));
    personTrie.putIndividualWord(name7, Person(27, name7));
    personTrie.putIndividualWord(name8, Person(28, name8));
    personTrie.putIndividualWord(name9, Person(29, name9));

    std::string search;
    while (std::getline(std::cin, search)) {
        std::cout << " --- Searching \"" << search << "\"\n";
        auto a = personTrie.searchSimilarKeyword(search);
        while (!a.empty()) {
            std::cout << a.top().content->name << " - " << a.top().content->age << '\n';
            a.pop();
        }
    }
}
