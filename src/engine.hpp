#pragma once
#include "trie.hpp"

namespace trie {

class Engine {
    Trie_t* trie;

public:
    Engine();
    ~Engine();

    /*01*/ std::string searchForStore(std::string query, int n_return, int offset, const std::string&, const std::string&);
    /*01*/ std::string searchForStoreByCategory(std::string query, int n_return, int offset, const std::string&, const std::string&);
    /*10*/ std::string search(std::string query, int n_return, int offset, const std::string&, const std::string&);

    /*10*/ std::string insertStore(unsigned int id, const std::string& name, const std::string& lat, const std::string& lng, const std::string& max_radius, const std::string& address, const std::string& phone, const std::string& brand);
    /*10*/ std::string insertCategory(unsigned int id, const std::string& name);

    /*??*/ std::string updateStore(unsigned int id, const std::string& name, const std::string& lat, const std::string& lng, const std::string& max_radius, const std::string& address, const std::string& phone, const std::string& brand);
    /*??*/ std::string updateCategory(unsigned int id, const std::string& name);

    /*10*/ std::string newRelationStoreCategory(unsigned int id_store, unsigned int id_category);
    /*10*/ std::string removeRelationStoreCategory(unsigned int id_store, unsigned int id_category);

    /*10*/ std::string removeStore(unsigned int id);
    /*10*/ std::string removeCategory(unsigned int id);

    /*10*/ std::string getStoresByCategory(unsigned int id, const std::string&, const std::string&);
    /*10*/ std::string getCategoriesByStore(unsigned int id);

    /*10*/ void limitErrors(int);
    /*10*/ void printTrieInfos();
    /*10*/ void init();
};
}
