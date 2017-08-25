#pragma once
#include <list>

namespace trie {

#define STORE 0
#define CATEGORY 1
#define BOTH 2
typedef char Type;

struct Occurrence_t {
    unsigned int itemRef;
    mutable char positionOnItem;
    mutable int weight;
    mutable Type type;
    Occurrence_t(unsigned int, char);
    Occurrence_t(unsigned int, char, Type);
    bool operator<(const Occurrence_t&) const;
};

struct OccurrencePriorityComparator_t {
    bool operator()(const Occurrence_t&, const Occurrence_t&);
};
}
