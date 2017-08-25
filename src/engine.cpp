#include "engine.hpp"
#include "geoDistance.hpp"
#include <cmath>
#include <iostream>
#include <set>
#include <sstream>

using namespace trie;

std::string trie::Engine::insertCategory(unsigned int id, const std::string& name)
{
    return this->trie->insertCategory(id, name) ? "{\"info\":\"Categoria inserida com sucesso.\"}" : "{\"error\":\"Categoria já existe!\"}";
}

std::string trie::Engine::insertStore(unsigned int id, const std::string& name, const std::string& lat, const std::string& lng, const std::string& max_radius, const std::string& address, const std::string& phone, const std::string& brand)
{
    return this->trie->insertStore(id, name, lat, lng, max_radius, address, phone, brand) ? "{\"info\":\"Store inserido com sucesso.\"}" : "{\"error\":\"Store já existe!\"}";
}

std::string trie::Engine::updateStore(unsigned int id, const std::string& name, const std::string& lat, const std::string& lng, const std::string& max_radius, const std::string& address, const std::string& phone, const std::string& brand)
{
    return this->trie->updateStore(id, name, lat, lng, max_radius, address, phone, brand) ? "{\"info\":\"Store alterado com sucesso.\"}" : "{\"error\":\"Store não existe!\"}";
}

std::string trie::Engine::updateCategory(unsigned int id, const std::string& name)
{
    return this->trie->updateCategory(id, name) ? "{\"info\":\"Categoria alterada com sucesso.\"}" : "{\"error\":\"Categoria não existe!\"}";
}

std::string trie::Engine::newRelationStoreCategory(unsigned int id_store, unsigned int id_category)
{
    return this->trie->addRelation(id_store, id_category) ? "{\"info\":\"Relação Adicionada\"}" : "{\"error\":\"Relação Não Adicionada\"}";
}

std::string trie::Engine::removeRelationStoreCategory(unsigned int id_store, unsigned int id_category)
{
    // std::cout << "[LOG] Trying to remove a relation evolving \"" << id_store << "\" and \"" << id_category << "\"" << std::endl;
    return this->trie->removeRelation(id_store, id_category) ? "{\"info\":\"Relação Removida\"}" : "{\"error\":\"Relação Não Removida\"}";
}

std::string trie::Engine::removeStore(unsigned int id)
{
    // std::cout << "[LOG] Trying to remove a store with id \"" << id << "\"" << std::endl;
    return this->trie->removeStore(id, false) ? "{\"info\":\"Store removido.\"}" : "{\"error\":\"Store não removido!\"}";
}

std::string trie::Engine::removeCategory(unsigned int id)
{
    return this->trie->removeCategory(id, false) ? "{\"info\":\"Categoria removida.\"}" : "{\"error\":\"Categoria não removida!\"}";
}

std::string trie::Engine::searchForStore(std::string query, int n_return, int offset, const std::string& lat, const std::string& lng)
{
    std::string realQuery, curWord;
    std::stringstream queryStream(query);
    double d_lat, d_lng;
    double d_relativeLat, d_relativeLng;
    if (lat.size() > 0) {
        std::stringstream(lat) >> d_lat;
        std::stringstream(lng) >> d_lng;
    }
    std::stringstream latStream, lngStream;

    while (std::getline(queryStream, curWord, ' ')) {
        realQuery += curWord + ' ';
    }

    // std::cout << "[LOG] Searching for \"" << realQuery << "\"\n";

    if (realQuery.size() > 0) {
        curWord.clear();

        realQuery.pop_back();

        std::cout << "[LOG] Searching for \"" << realQuery << "\"\n";
        auto fuzzyWords = trie->searchSimilarKeyword(realQuery, STORE);

        // std::cout << "[LOG] " << fuzzyWords.size() << " results found." << std::endl;
        // std::cout << "[LOG] Paging from " << offset << " to " << offset + n_return << std::endl;

        int itemCount = fuzzyWords.size(); // it's possible once it searches only stores

        curWord += "{\"stores\":[";
        --offset;
        --n_return;

        while (!fuzzyWords.empty() && offset >= 0) {
            fuzzyWords.pop();
            --offset;
        }

        while (!fuzzyWords.empty() && n_return >= 0) {
            auto ocurrence = fuzzyWords.top();
            auto trieObject = trie->getStore(ocurrence.itemRef);
            nlohmann::json editJsonObject = trieObject.jsonObject;
            if (lat.size() > 0) {
                latStream.clear();
                lngStream.clear();

                latStream.str(trieObject.lat);
                lngStream.str(trieObject.lng);

                latStream >> d_relativeLat;
                lngStream >> d_relativeLng;

                editJsonObject["distance"] = distanceInKmBetweenEarthCoordinates(d_lat, d_lng, d_relativeLat, d_relativeLng);
            } else {
                editJsonObject["distance"] = -1;
            }

            curWord += editJsonObject.dump() + ",";
            fuzzyWords.pop();
            n_return--;
        }

        if (curWord[curWord.size() - 1] == ',') {
            curWord.pop_back();
        }

        curWord += "],\"count\":\"" + std::to_string(itemCount) + "\"}";
    } else {
        curWord = "{\"error\":\"Empty query\"}";
    }

    // std::cout << "[LOG] Output has been set to variable." << std::endl;

    return curWord;
}

std::string trie::Engine::searchForStoreByCategory(std::string query, int n_return, int offset, const std::string& lat, const std::string& lng)
{
    std::string realQuery, curWord;
    std::stringstream queryStream(query);
    double d_lat, d_lng;
    double d_relativeLat, d_relativeLng;
    if (lat.size() > 0) {
        std::stringstream(lat) >> d_lat;
        std::stringstream(lng) >> d_lng;
    }
    std::stringstream latStream, lngStream;

    while (std::getline(queryStream, curWord, ' ')) {
        realQuery += curWord + ' ';
    }

    std::cout << "[LOG] Searching for \"" << realQuery << "\"\n";
    if (realQuery.size() > 0) {
        curWord.clear();

        realQuery.pop_back();

        auto fuzzyWords = trie->searchSimilarKeyword(realQuery, CATEGORY);

        // std::cout << "[LOG] " << fuzzyWords.size() << " results found." << std::endl;
        // std::cout << "[LOG] Paging from " << offset << " to " << offset + n_return << std::endl;

        int itemCount = 0;

        while (!fuzzyWords.empty() && offset >= 0) {
            auto regStores = trie->getStoresByCategory(fuzzyWords.top().itemRef);

            while (offset > 0 && regStores.size() > 0) {
                regStores.erase(regStores.begin());
                ++itemCount;
                --offset;
            }

            fuzzyWords.pop();

            if (offset <= 0) {

                curWord += "{\"stores\":[";

                for (auto store : regStores) {
                    if (n_return > 0) {
                        nlohmann::json editJsonObject = store.jsonObject;
                        if (lat.size() > 0) {
                            latStream.clear();
                            lngStream.clear();

                            latStream.str(store.lat);
                            lngStream.str(store.lng);

                            latStream >> d_relativeLat;
                            lngStream >> d_relativeLng;

                            editJsonObject["distance"] = distanceInKmBetweenEarthCoordinates(d_lat, d_lng, d_relativeLat, d_relativeLng);
                        } else {
                            editJsonObject["distance"] = -1;
                        }
                        curWord += editJsonObject.dump() + ",";
                        n_return--;
                    }
                    itemCount++;
                }

                while (!fuzzyWords.empty() && n_return > 0) {
                    for (auto store : trie->getStoresByCategory(fuzzyWords.top().itemRef)) {
                        if (n_return > 0) {
                            nlohmann::json editJsonObject = store.jsonObject;
                            if (lat.size() > 0) {
                                latStream.clear();
                                lngStream.clear();

                                latStream.str(store.lat);
                                lngStream.str(store.lng);

                                latStream >> d_relativeLat;
                                lngStream >> d_relativeLng;

                                editJsonObject["distance"] = distanceInKmBetweenEarthCoordinates(d_lat, d_lng, d_relativeLat, d_relativeLng);
                            } else {
                                editJsonObject["distance"] = -1;
                            }
                            curWord += editJsonObject.dump() + ",";
                            n_return--;
                        }
                        itemCount++;
                    }
                    fuzzyWords.pop();
                }

                if (curWord[curWord.size() - 1] == ',') {
                    curWord.pop_back();
                }

                curWord += "],\"count\":\"" + std::to_string(itemCount) + "\"}";
                return curWord;
            }
        }

        return "{\"count\":\"0\",\"stores\":[]}";

    } else {
        curWord = "{\"error\":\"Empty query\"}";
    }

    // std::cout << "[LOG] Output has been set to variable." << std::endl;

    return curWord;
}

std::string trie::Engine::search(std::string query, int n_return, int offset, const std::string& lat, const std::string& lng)
{
    std::string realQuery, curWord;
    std::stringstream queryStream(query);
    double d_lat, d_lng;
    double d_relativeLat, d_relativeLng;
    if (lat.size() > 0) {
        std::stringstream(lat) >> d_lat;
        std::stringstream(lng) >> d_lng;
    }
    std::stringstream latStream, lngStream;
    std::set<unsigned int> visitedStores;

    while (std::getline(queryStream, curWord, ' ')) {
        realQuery += curWord + ' ';
    }

    if (realQuery.size() > 0) {
        curWord.clear();

        realQuery.pop_back();
        std::cout << "[LOG] Searching for \"" << realQuery << "\"\n";
        auto fuzzyWords = trie->searchSimilarKeyword(realQuery, BOTH);

        std::cout << fuzzyWords.size() << " results found." << std::endl;
        std::cout << "Paging from " << offset << " to " << offset + n_return << std::endl;

        --n_return;

        curWord += "{\"stores\":[";

        while (!fuzzyWords.empty() && offset > 0) {

            auto ocurrence = fuzzyWords.top();

            if (ocurrence.type == STORE) {
                visitedStores.emplace(ocurrence.itemRef);
                --offset;
            } else {
                auto abstract_conjuct = trie->getStoresByCategory(ocurrence.itemRef);
                for (auto store : abstract_conjuct) {
                    if (visitedStores.emplace(store.id).second) {

                        if (offset <= 0 && n_return >= 0) {
                            nlohmann::json editJsonObject = store.jsonObject;
                            if (lat.size() > 0) {

                                latStream.clear();
                                lngStream.clear();

                                latStream.str(store.lat);
                                lngStream.str(store.lng);

                                latStream >> d_relativeLat;
                                lngStream >> d_relativeLng;
                                editJsonObject["distance"] = distanceInKmBetweenEarthCoordinates(d_lat, d_lng, d_relativeLat, d_relativeLng);
                            } else {
                                editJsonObject["distance"] = -1;
                            }

                            curWord += editJsonObject.dump() + ",";
                            --n_return;
                        }

                        --offset;
                    }
                }
            }

            fuzzyWords.pop();
        }

        while (!fuzzyWords.empty()) {
            auto ocurrence = fuzzyWords.top();

            if (ocurrence.type == STORE) {
                if (visitedStores.emplace(ocurrence.itemRef).second) {
                    if (n_return >= 0) {
                        auto trieStore = trie->getStore(ocurrence.itemRef);
                        nlohmann::json editJsonObject = trieStore.jsonObject;
                        if (lat.size() > 0) {
                            latStream.clear();
                            lngStream.clear();

                            latStream.str(trieStore.lat);
                            lngStream.str(trieStore.lng);

                            latStream >> d_relativeLat;
                            lngStream >> d_relativeLng;

                            editJsonObject["distance"] = distanceInKmBetweenEarthCoordinates(d_lat, d_lng, d_relativeLat, d_relativeLng);
                        } else {
                            editJsonObject["distance"] = -1;
                        }

                        curWord += editJsonObject.dump() + ",";
                        n_return--;
                    }
                }
            } else {
                auto conjuct = trie->getStoresByCategory(ocurrence.itemRef);

                for (auto store : conjuct) {
                    if (visitedStores.emplace(store.id).second) {
                        if (n_return >= 0) {
                            nlohmann::json editJsonObject = store.jsonObject;
                            if (lat.size() > 0) {
                                latStream.clear();
                                lngStream.clear();

                                latStream.str(store.lat);
                                lngStream.str(store.lng);

                                latStream >> d_relativeLat;
                                lngStream >> d_relativeLng;

                                editJsonObject["distance"] = distanceInKmBetweenEarthCoordinates(d_lat, d_lng, d_relativeLat, d_relativeLng);
                            } else {
                                editJsonObject["distance"] = -1;
                            }
                            curWord += editJsonObject.dump() + ",";
                            n_return--;
                        }
                    }
                }
            }

            fuzzyWords.pop();
        }

        if (curWord[curWord.size() - 1] == ',') {
            curWord.pop_back();
        }

        curWord += "],\"count\":\"" + std::to_string(visitedStores.size()) + "\"}";

    } else {
        curWord = "{\"error\":\"Empty query\"}";
    }

    // std::cout << "[LOG] Output has been set to variable." << std::endl;

    return curWord;
}

void trie::Engine::printTrieInfos()
{
    this->trie->printData();
}

struct StoresDistanceComparator {
    bool operator()(const std::pair<std::string, double>& pairOne, const std::pair<std::string, double>& pairTwo)
    {
        return pairOne.second > pairTwo.second;
    }
};

std::string trie::Engine::getStoresByCategory(unsigned int id, const std::string& lat, const std::string& lng)
{
    // std::cout << "[LOG] Seeking for stores from category \"" << id << "\"" << std::endl;
    double d_lat, d_lng;
    double d_relativeLat, d_relativeLng;
    if (lat.size() > 0) {
        std::stringstream(lat) >> d_lat;
        std::stringstream(lng) >> d_lng;
    }
    std::stringstream latStream, lngStream;

    std::string ret = "{";
    auto stores = trie->getStoresByCategory(id);
    if (stores.size() > 0) {
        ret += "\"catId\":" + std::to_string(id) + ",";
        ret += "\"stores\":[";

        std::priority_queue<std::pair<std::string, double>, std::vector<std::pair<std::string, double>>, StoresDistanceComparator> orderedStores;

        for (auto store : stores) {
            double calculatedDistance;
            if (lat.size() > 0) {
                latStream.clear();
                lngStream.clear();

                latStream.str(store.lat);
                lngStream.str(store.lng);

                latStream >> d_relativeLat;
                lngStream >> d_relativeLng;

                calculatedDistance = distanceInKmBetweenEarthCoordinates(d_lat, d_lng, d_relativeLat, d_relativeLng);
            } else {
                calculatedDistance = -1;
            }

            store.jsonObject["distance"] = calculatedDistance;

            orderedStores.push({ store.jsonObject.dump(), calculatedDistance });
            // std::stringstream(store.lat) >> d_relativeLat;
            // std::stringstream(store.lng) >> d_relativeLng;
            // orderedStores.push();
            // ret += store.jsonObject.dump() + (count < stores.size() ? "," : "");
        }

        while (!orderedStores.empty()) {
            ret += orderedStores.top().first + (orderedStores.size() > 1 ? "," : "");
            orderedStores.pop();
        }

        ret += "]";
    } else {
        ret += "\"error\":\"there ain't stores related to this category.\"";
    }
    ret += "}";

    // std::cout << "[LOG] Output has been set to variable." << std::endl;

    return ret;
}

std::string trie::Engine::getCategoriesByStore(unsigned int id)
{

    // std::cout << "[LOG] Seeking for categories from store \"" << id << "\"" << std::endl;
    std::string ret = "{";
    auto categories = trie->getCategoriesByStore(id);
    if (categories.size() > 0) {
        ret += "\"stoId\":" + std::to_string(id) + ",";
        ret += "\"categories\":[";

        unsigned int count = 0;

        for (auto category : categories) {
            count++;
            ret += category.jsonObject.dump() + (count < categories.size() ? "," : "");
        }
        ret += "]";
    } else {
        ret += "\"error\":\"there ain't categories related to this store.\"";
    }
    ret += "}";

    // std::cout << "[LOG] Output has been set to variable." << std::endl;

    return ret;
}

void trie::Engine::limitErrors(int errors)
{
    // std::cout << "[LOG] Error limit has been changed to " << errors << std::endl;
    this->trie->setFuzzyLimitThreshold(errors);
}

trie::Engine::Engine()
{
    std::cout << "[LOG] Trie has been initializated" << std::endl;
    this->trie = new trie::Trie_t();
}

trie::Engine::~Engine()
{
    delete (this->trie);
}

void trie::Engine::init()
{
    std::cout << "[LOG] ActiveNodeSet has been build" << std::endl;
    this->trie->buildActiveNodeSet();
}
