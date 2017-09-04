#include "trie.hpp"
#include "person.hpp"
#include <iostream>
#include <map>

int main()
{
  trie::Trie_t<Person> personTrie;
  personTrie.buildActiveNodeSet();
  Person p, p2;

  p.age = 20;
  p.name = "Duan";

  p2.age = 23;
  p2.name = "Daniel";

  personTrie.putWord(p.name, p);
  personTrie.putWord(p2.name, p2);

  auto a = personTrie.searchSimilarKeyword("Dan");
  while(!a.empty()){
    std::cout << a.top().name << '\n';
    a.pop();
  }
}
