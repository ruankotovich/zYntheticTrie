#include "occurrence.hpp"

using namespace trie;

trie::Occurrence_t::Occurrence_t(unsigned int ref, char position)
    : itemRef(ref)
    , positionOnItem(position)
    , weight(0)
{
}

trie::Occurrence_t::Occurrence_t(unsigned int ref, char position, Type type)
    : itemRef(ref)
    , positionOnItem(position)
    , weight(0)
    , type(type)
{
}

bool trie::Occurrence_t::operator<(const Occurrence_t& par1) const
{
    return this->type == par1.type ? this->itemRef < par1.itemRef : this->type < par1.type;
}

bool trie::OccurrencePriorityComparator_t::operator()(const Occurrence_t& o1, const Occurrence_t& o2)
{
    return o1.type > o2.type || ((o1.weight << o1.positionOnItem) > (o2.weight << o2.positionOnItem));
}
