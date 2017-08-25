#include "trie.hpp"
#include "occurrence.hpp"
#include <algorithm>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace trie;

trie::ActiveNode_t::ActiveNode_t(TrieNode_t* nd, int ed)
    : node(nd)
    , editDistance(ed)
    , positionDistance(0)
{
}

trie::ActiveNode_t::ActiveNode_t(TrieNode_t* nd, int ed, int pos)
    : node(nd)
    , editDistance(ed)
    , positionDistance(pos)
{
}

bool trie::ActiveNode_t::operator<(const ActiveNode_t& anode) const
{
    return this->node < anode.node;
}

bool trie::ActiveNodeComparator_t::operator()(const ActiveNode_t& n1, const ActiveNode_t& n2) const
{
    return n1.editDistance > n2.editDistance;
}

// Trie_t private methods
void trie::Trie_t::buildActiveNodeSet()
{
    std::queue<std::pair<TrieNode_t*, int>> seekQueue;
    std::unordered_map<TrieNode_t*, TrieNode_t*> father;
    std::set<TrieNode_t*> visited;

    seekQueue.emplace(this->m_lambdaNode, 0); // add the lambdaNode to the seek
    m_activeNodeSet.emplace(this->m_lambdaNode, 0); // add the lambdaNode to the activeSet
    father.emplace(this->m_lambdaNode, nullptr); // set lambdaNode father as nullptr

    /* initialization */

    while (!seekQueue.empty()) {
        auto currentNode = seekQueue.front(); // get currentNode
        seekQueue.pop();

        for (TrieNode_t* child : currentNode.first->getChildren()) {

            // verify if the child hasn't been visited recently
            if (visited.find(child) == visited.end()) {
                int currentLevel = currentNode.second + 1;

                visited.emplace(child); // add child to the visited set
                father.emplace(child, currentNode.first); // set current vertex as father

                if (currentLevel < m_fuzzyLimitThreshold) { // add the child on the seek only if it has a threshold < fuzzy
                    seekQueue.emplace(child, currentLevel);
                }

                if (child->isEndOfWord()) { // verify if this child is end of word
                    TrieNode_t* currentChild = child;
                    m_activeNodeSet.emplace(currentChild, currentLevel); // add the child to the activeSet

                    auto currentChild_it = father.find(child);

                    // add all the father's father's father's ... father's of this child to the activeSet
                    while (currentChild_it->second != nullptr) {

                        if (m_activeNodeSet.emplace(currentChild_it->second, --currentLevel).second) {
                            currentChild_it = father.find(currentChild_it->second);
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }
}

void trie::Trie_t::push_string_to_wchar(wchar_t* w, std::string& a)
{
    setlocale(LC_ALL, "");
    const char* nw = a.c_str();
    mbsrtowcs(w, &nw, a.length(), NULL);
    w[a.length()] = 0;
}

void trie::Trie_t::encodeCharacters(const std::string& filename)
{
    // std::cout << "[LOG] Encoding characters." << std::endl;
    unsigned int lineCode = 1;
    std::string currentLine;
    std::ifstream fileInputStream(filename);

    while (std::getline(fileInputStream, currentLine)) {

        m_reverseCharacterMap.emplace(lineCode, currentLine.back());

        wchar_t anomalousCharacters[currentLine.size()];
        push_string_to_wchar(anomalousCharacters, currentLine);

        for (unsigned int i = 0; i < wcslen(anomalousCharacters); i++) {
            m_characterMap.emplace(anomalousCharacters[i], lineCode);
        }

        lineCode++;
    }

    m_reverseCharacterMap[0] = '#'; // lambda character
    std::cout << "Charmap has been mapped.\n";
}

void trie::Trie_t::addStopWords(const std::string& filename)
{
    std::string currentLine;
    std::ifstream fileInputStream(filename);

    while (std::getline(fileInputStream, currentLine)) {
        std::transform(currentLine.begin(), currentLine.end(), currentLine.begin(), ::tolower);
        m_stopWords.insert(currentLine);
    }
}

bool trie::Trie_t::isStopWord(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return m_stopWords.find(str) != m_stopWords.end();
}

// Trie_t public methods

trie::Trie_t::Trie_t()
    : m_searchLimitThreshold(5)
    , m_fuzzyLimitThreshold(1)
{
    this->m_lambdaNode = new TrieNode_t(0);

    DIR* dirp;
    struct dirent* directory;
    dirp = opendir("./stopwords");
    if (dirp) {
        while ((directory = readdir(dirp)) != NULL) {
            if (directory->d_type == DT_REG) {
                std::cout << "The stopword file \'" << directory->d_name << "\' has been detected.\n";
                this->addStopWords(std::string("./stopwords/") + (directory->d_name));
            }
        }
        closedir(dirp);
    }

    encodeCharacters("charmap.cm");
}

void trie::Trie_t::printTrie()
{
    TrieNode_t* currentNode;
    std::set<TrieNode_t*> visited;

    std::stack<TrieNode_t*> nodeStack;
    nodeStack.push(this->m_lambdaNode);

    while (!nodeStack.empty()) {
        currentNode = nodeStack.top();

        if (visited.find(currentNode) == visited.end()) {
            visited.insert(currentNode);
            std::cout << "[" << this->m_reverseCharacterMap[currentNode->getContent()] << (currentNode->isEndOfWord() ? "'" : " ");
            std::vector<TrieNode_t*> children = currentNode->getChildren();

            while (!children.empty()) {
                nodeStack.push(children.back());
                children.pop_back();
            }

        } else {
            nodeStack.pop();
            std::cout << "]";
        }
    }
}

void trie::Trie_t::putWordAsCategory(std::string& str, char position, unsigned int reference)
{
    TrieNode_t *currentRoot, *lastRoot;
    currentRoot = this->m_lambdaNode;

    wchar_t chart[str.size()];
    push_string_to_wchar(chart, str);

    for (unsigned int i = 0; i < wcslen(chart); i++) {

        unsigned int code = this->m_characterMap[chart[i]];

        lastRoot = currentRoot;
        currentRoot = currentRoot->getChild(code);
        if (!currentRoot) {
            currentRoot = lastRoot->insertNReturnChild(code);
        }
    }

    if (currentRoot != this->m_lambdaNode) {

        if (!currentRoot->isEndOfCategory()) {
            currentRoot->buildOccurrences(CATEGORY);
            currentRoot->setEndOfCategory(true);
        }
        currentRoot->addOccurrence(position, reference, CATEGORY);
    }
}

void trie::Trie_t::putWordAsStore(std::string& str, char position, unsigned int reference)
{
    TrieNode_t *currentRoot, *lastRoot;
    currentRoot = this->m_lambdaNode;

    wchar_t chart[str.size()];
    push_string_to_wchar(chart, str);

    for (unsigned int i = 0; i < wcslen(chart); i++) {

        unsigned int code = this->m_characterMap[chart[i]];

        lastRoot = currentRoot;
        currentRoot = currentRoot->getChild(code);
        if (!currentRoot) {
            currentRoot = lastRoot->insertNReturnChild(code);
        }
    }

    if (currentRoot != this->m_lambdaNode) {

        if (!currentRoot->isEndOfStore()) {
            currentRoot->buildOccurrences(STORE);
            currentRoot->setEndOfStore(true);
        }
        currentRoot->addOccurrence(position, reference, STORE);
    }
}

std::set<ActiveNode_t> trie::Trie_t::buildNewSet(std::set<ActiveNode_t>& set, unsigned int curChar)
{
    std::set<ActiveNode_t> activeNodeSet;

    /*
  ** Considering node N
  ** We can transform the content of this node for the currentWord by first adding a character. (Prebuilt Addiction)
  */
    // std::cout << "\nBuilding node for " << m_reverseCharacterMap[curChar] << '\n';
    for (auto curActiveNode = set.begin(); curActiveNode != set.end(); curActiveNode++) {
        if (curActiveNode->editDistance < m_fuzzyLimitThreshold) {
            // std::cout << " * Updating distance for node " << m_reverseCharacterMap[curActiveNode->node->getContent()] << " from " << curActiveNode->editDistance << " to " << curActiveNode->editDistance + 1 << '\n';
            activeNodeSet.emplace(curActiveNode->node, curActiveNode->editDistance + 1);
        }
    }

    /*
  ** Considering no+de P (child of N)
  ** -  C1. Different character from `curChar` : (Posbuilt Substitution Addiction)
  **    We can transform this character of P for the current character by substitution, relative to ED(N), then, we have to add P to
  **    the set if and only if ED(N)+1 [previously calculated and updated] < threshold
  **
  ** -  C2. Equals character from `curChar` : (Posbuilt Match Addiction)
  **    If this node character match with `curChar`, it means that we got to add it with ED(N) (indeed, when we got a match, we have ED=0) [1]
  **    Once doing it, we have to add the descendant nodes of P (called here `PChild`) with distance PChild = ED(P) + DeepthFrom(P, PChild) < threshold
  **
  ** Addendum [1] - I must update the distance only if the new distance is lower than the last distance (it happens when a previously father node have been calculated)
  */

    for (auto curActiveNode = set.begin(); curActiveNode != set.end(); curActiveNode++) {

        // std::cout << "\nScanning children of node " << m_reverseCharacterMap[curActiveNode->node->getContent()] << '\n';

        for (auto childOfcurActiveNode : curActiveNode->node->getChildren()) {
            // std::cout << " * Node " << m_reverseCharacterMap[childOfcurActiveNode->getContent()] << " found ";
            if (childOfcurActiveNode->getContent() != curChar) { // case 1
                // std::cout << " and haven't matched with the character,";
                if (curActiveNode->editDistance < m_fuzzyLimitThreshold) { // verify if ED(N)+1 < P
                    // std::cout << " but it's edit distance can be increased and it would be added to the set";
                    int newEditDistance = curActiveNode->editDistance + 1; // the new edit distance for the child

                    // retrieves to add the child, return FALSE if it was not possible, cuz the child was already added before (so, i've to verify which edit distance is lower : the current or the previous?)
                    auto childIteratorOnSet = activeNodeSet.emplace(childOfcurActiveNode, newEditDistance);

                    // if the child was not added (it was cuz' there was a activeNode marked on this node before) and the last ED is bigger than the new ED
                    if (!childIteratorOnSet.second) {
                        if (childIteratorOnSet.first->editDistance > newEditDistance) {
                            childIteratorOnSet.first->editDistance = newEditDistance; // guaranteed by addendum 1
                        }
                    }
                }
                // std::cout << '\n';
            } else { // case 2
                // std::cout << " and it matches with the character, so will be added to the set\n";
                // retrieves to add the child, return FALSE if it was not possible, cuz the child was already added before (so, i've to verify which edit distance is lower : the current or the previous?)
                auto childIteratorOnSet = activeNodeSet.emplace(childOfcurActiveNode, curActiveNode->editDistance);

                int currentChildDistance = childIteratorOnSet.first->editDistance;

                if (!childIteratorOnSet.second) { /* processor thanks! */
                    if (childIteratorOnSet.first->editDistance > curActiveNode->editDistance) {
                        currentChildDistance = childIteratorOnSet.first->editDistance = curActiveNode->editDistance;
                    }
                }

                /*
        **  I've to fetch the children and the entire set of children to the active node if
        **  and only if the dist( father, getChildRecursive(father)) ) < threshold;
        */
                // std::cout << "\t\tIt's children will be verifieds to be added to the set : \n";

                std::queue<TrieNode_t*> toRecover; // a queue to save which node is on the way
                toRecover.push(childIteratorOnSet.first->node); // adding the current matched node to the queue

                // while the distance is lesser than the limit and we got some node to recover...
                while (currentChildDistance < m_fuzzyLimitThreshold && !toRecover.empty()) {
                    // recover the current node from the queue
                    TrieNode_t*& currentNode = toRecover.front();
                    // std::cout << "\t\tCurrent node : " << m_reverseCharacterMap[currentNode->getContent()] << '\n';
                    // and update the distance to one more
                    ++currentChildDistance;

                    // for each child of the current node
                    for (auto child : currentNode->getChildren()) {

                        // we add this child to the active node set, once we can face it as a addiction operation inside the boundary imposed by the search
                        auto currentChildIterator = activeNodeSet.emplace(child, currentChildDistance);
                        // std::cout << "\t\t * Children " << m_reverseCharacterMap[currentChildIterator.first->node->getContent()] << " added to the set ";
                        // if there was this child within the activeNode, we have to keep the minor operation distance
                        if (!currentChildIterator.second) {
                            // std::cout << "by update/permanence ";
                            if (currentChildIterator.first->editDistance > currentChildDistance) {
                                currentChildIterator.first->editDistance = currentChildDistance;
                            }
                        }
                        // std::cout<<" with edit distance " << currentChildIterator.first->editDistance << '\n';

                        // and put it if and only if the currentDistance is lesser than the thresould (the memory and processment thank!)
                        if (currentChildDistance < m_fuzzyLimitThreshold) {
                            toRecover.push(child);
                        }
                    }
                    toRecover.pop();
                }
            }
        }
    }
    // std::cout << "\n\n";
    return activeNodeSet;
}

std::priority_queue<Occurrence_t, std::vector<Occurrence_t>, OccurrencePriorityComparator_t> Trie_t::searchSimilarKeyword(const std::string& keyword, Type type)
{
    std::set<Occurrence_t>* lastAnswerSet = nullptr;
    std::list<std::priority_queue<ActiveNode_t, std::vector<ActiveNode_t>, ActiveNodeComparator_t>> activeLists;
    std::string curKeyword;

    std::stringstream wordStream(keyword);

    while (std::getline(wordStream, curKeyword, ' ')) {

        std::transform(curKeyword.begin(), curKeyword.end(), curKeyword.begin(), ::tolower);

        if (this->isStopWord(curKeyword)) {
            std::cout << "There's a stopword" << '\n';
            if (!(wordStream.rdbuf()->in_avail() == 0)) {
                std::cout << "But it isn't on the last position, ignoring" << '\n';
                continue;
            }
        }

        std::set<ActiveNode_t> lastActiveNodes = this->m_activeNodeSet;

        wchar_t chart[curKeyword.size()];
        push_string_to_wchar(chart, curKeyword);

        for (unsigned int i = 0; i < wcslen(chart); i++) {
            lastActiveNodes = buildNewSet(lastActiveNodes, m_characterMap[chart[i]]);
        }

        auto currentList = activeLists.emplace(activeLists.end(), std::priority_queue<ActiveNode_t, std::vector<ActiveNode_t>, ActiveNodeComparator_t>());
        for (auto node : lastActiveNodes) {
            currentList->push(node);
        }
    }

    char iteration = 1;

    for (auto currentList : activeLists) {
        std::cout << "\n\n";
        std::set<Occurrence_t>* answerSet = new std::set<Occurrence_t>();
        std::unordered_set<TrieNode_t*> visitedNode;

        while (!currentList.empty()) {

            auto aNode = currentList.top();
            currentList.pop();

            if (visitedNode.find(aNode.node) == visitedNode.end()) {
                std::queue<TrieNode_t*> pQueue;
                pQueue.push(aNode.node);

                while (!pQueue.empty()) {
                    auto currentSeeker = pQueue.front();
                    visitedNode.insert(currentSeeker);
                    pQueue.pop();

                    if (currentSeeker->isEndOfWord()) {

                        // if (currentSeeker->isEndOfCategory()) {
                        //     for (auto categs : currentSeeker->getOccurences(CATEGORY)) {
                        //         for (auto cat : *categs) {
                        //             std::cout << " - " << this->m_categoryTable.find(cat.itemRef)->second.name << '\n';
                        //         }
                        //     }
                        // }

                        // if (currentSeeker->isEndOfStore()) {
                        //     for (auto stors : currentSeeker->getOccurences(STORE)) {
                        //         for (auto sto : *stors) {
                        //             std::cout << " - " << this->m_storeTable.find(sto.itemRef)->second.name << '\n';
                        //         }
                        //     }
                        // }

                        for (auto action : currentSeeker->getOccurences(type)) {

                            for (auto ocurrence : (*action)) {
                                ocurrence.weight = aNode.editDistance;
                                ocurrence.positionOnItem = abs(ocurrence.positionOnItem - iteration);
                                answerSet->insert(ocurrence);
                            }
                        }
                    }

                    for (TrieNode_t* curChild : currentSeeker->getChildren()) {
                        if (visitedNode.find(curChild) == visitedNode.end()) {
                            pQueue.emplace(curChild);
                        }
                    }
                }
            }
        }

        if (iteration > 1) {

            if (lastAnswerSet->size() > answerSet->size()) {
                std::set<Occurrence_t>* back = lastAnswerSet;
                lastAnswerSet = answerSet;
                answerSet = back;
            }

            // std::cout << "PREVIOUS ANSWER : \n";
            // for (auto ans : *lastAnswerSet) {

            //     if (ans.type == STORE) {
            //         std::cout << " - STO " << this->m_storeTable.find(ans.itemRef)->second.name << '\n';
            //     } else {
            //         std::cout << " - CAT " << this->m_categoryTable.find(ans.itemRef)->second.name << '\n';
            //     }
            // }

            // std::cout << "\n\n";

            // std::cout << "CURRENT ANSWER : \n";
            // for (auto ans : *answerSet) {
            //     if (ans.type == STORE) {
            //         std::cout << " - STO " << this->m_storeTable.find(ans.itemRef)->second.name << '\n';
            //     } else {
            //         std::cout << " - CAT " << this->m_categoryTable.find(ans.itemRef)->second.name << '\n';
            //     }
            // }
            // std::cout << '\n';

            for (auto ans = lastAnswerSet->begin(); ans != lastAnswerSet->end();) {

                auto iterator = answerSet->emplace(ans->itemRef, 0, ans->type);

                if (iterator.second) { // should it took place, it will be deleted
                    ans = lastAnswerSet->erase(ans);
                } else { // otherwise, it will be updated
                    ans->weight += iterator.first->weight;
                    ans->positionOnItem += iterator.first->positionOnItem;
                    ++ans;
                }
            }

            delete (answerSet);

        } else {
            lastAnswerSet = answerSet;
        }

        iteration++;
    }

    // if (lastAnswerSet != nullptr) {
    //     std::cout << "LAST ANSWER : \n";
    //     for (auto ans : *lastAnswerSet) {

    //         if (ans.type == STORE) {
    //             std::cout << " - STO " << this->m_storeTable.find(ans.itemRef)->second.name << '\n';
    //         } else {
    //             std::cout << " - CAT " << this->m_categoryTable.find(ans.itemRef)->second.name << '\n';
    //         }
    //     }
    // }

    std::priority_queue<Occurrence_t, std::vector<Occurrence_t>, OccurrencePriorityComparator_t> ocurrencesQueue;

    if (lastAnswerSet != nullptr) {
        for (auto ocur : *lastAnswerSet) {
            ocurrencesQueue.push(ocur);
        }

        delete (lastAnswerSet);
    }

    return ocurrencesQueue;
}

void trie::Trie_t::setSearchLimitThreshold(int limit)
{
    this->m_searchLimitThreshold = limit;
}

void trie::Trie_t::setFuzzyLimitThreshold(int limit)
{
    this->m_fuzzyLimitThreshold = limit;
}

void trie::Trie_t::printData()
{
    std::cout << " -- Categories -- \n";

    for (auto a : this->m_categoryTable) {
        std::cout << " - " << a.first << " , " << a.second.name << '\n';
    }

    std::cout << " -- Stores -- \n";

    for (auto a : this->m_storeTable) {
        std::cout << " - " << a.first << " , " << a.second.name << " , " << a.second.lat << " , " << a.second.lng << " , " << a.second.max_radius << '\n';
    }
}

std::set<UData::Category_t, UData::CategoryComparator_t> trie::Trie_t::getCategoriesByStore(unsigned int id)
{
    std::set<UData::Category_t, UData::CategoryComparator_t> categories;
    auto catIdSet = this->m_relationStoCat.find(id);

    if (catIdSet != this->m_relationStoCat.end()) {
        for (auto cat : catIdSet->second) {
            auto foundCat = this->m_categoryTable.find(cat);
            if (foundCat != this->m_categoryTable.end()) {
                categories.emplace(foundCat->second.id, foundCat->second.name, foundCat->second.jsonObject);
            }
        }
    }

    return categories;
}

std::set<UData::Store_t, UData::StoreComparator_t> trie::Trie_t::getStoresByCategory(unsigned int id)
{
    std::set<UData::Store_t, UData::StoreComparator_t> stores;

    auto stoIdSet = this->m_relationCatSto.find(id);

    if (stoIdSet != this->m_relationCatSto.end()) {
        for (auto sto : stoIdSet->second) {
            auto foundSto = this->m_storeTable.find(sto);
            if (foundSto != this->m_storeTable.end()) {
                stores.emplace(foundSto->second.id, foundSto->second.name, foundSto->second.lat, foundSto->second.lng, foundSto->second.max_radius, foundSto->second.address, foundSto->second.phone, foundSto->second.brand, foundSto->second.jsonObject);
            }
        }
    }

    return stores;
}

bool trie::Trie_t::insertCategory(unsigned int id, const std::string& name)
{
    // Tip on https://stackoverflow.com/questions/27960325/stdmap-emplace-without-copying-value / accessed on 1st August 2017
    auto emplaceIterator = this->m_categoryTable.emplace(std::piecewise_construct, std::forward_as_tuple(id), std::forward_as_tuple(id, name));

    char position = 1;
    std::string word;
    std::stringstream strstream(name);
    while (std::getline(strstream, word, ' ')) {

        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (!this->isStopWord(word)) {
            this->putWordAsCategory(word, position, id);
        }

        position++;
    }

    UData::buildJson(emplaceIterator.first->second);
    return true;
}

bool trie::Trie_t::insertStore(unsigned int id, const std::string& name, const std::string& lat, const std::string& lng, const std::string& max_radius, const std::string& address, const std::string& phone, const std::string& brand)
{
    auto emplaceIterator = this->m_storeTable.emplace(std::piecewise_construct, std::forward_as_tuple(id), std::forward_as_tuple(id, name, lat, lng, max_radius, address, phone, brand));

    char position = 1;
    std::string word;
    std::stringstream strstream(name);
    while (std::getline(strstream, word, ' ')) {

        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (!this->isStopWord(word)) {
            this->putWordAsStore(word, position, id);
        }

        position++;
    }

    UData::buildJson(emplaceIterator.first->second);
    return true;
}

bool trie::Trie_t::updateStore(unsigned int id, const std::string& name, const std::string& lat, const std::string& lng, const std::string& max_radius, const std::string& address, const std::string& phone, const std::string& brand)
{
    auto storeIterator = this->m_storeTable.find(id);

    if (storeIterator != m_storeTable.end()) {
        if (name.compare(storeIterator->second.name) != 0) {
            this->insertStore(id, name, lat, lng, max_radius, address, phone, brand);
            UData::updateAll(storeIterator->second, name, lat, lng, max_radius, address, phone, brand);
        }
        return true;
    } else {
        return false;
    }
}

bool trie::Trie_t::updateCategory(unsigned int id, const std::string& name)
{
    auto categoryIterator = this->m_categoryTable.find(id);

    if (categoryIterator != m_categoryTable.end()) {
        if (name.compare(categoryIterator->second.name) != 0) {
            this->insertCategory(id, name);
            UData::updateAll(categoryIterator->second, name);
        }
        return true;
    } else {
        return false;
    }
}

bool trie::Trie_t::addRelation(unsigned int relative, unsigned int relationary)
{
    // std::cout << relative << '-' << relationary << '\n';
    auto stoIterator = this->m_relationStoCat.find(relative); // category
    auto catIterator = this->m_relationCatSto.find(relationary); // store

    if (catIterator == this->m_relationCatSto.end()) {
        auto catSet = this->m_relationCatSto.emplace(relationary, std::set<unsigned int>());
        catSet.first->second.emplace(relative);
    } else {
        catIterator->second.emplace(relative);
    }

    if (stoIterator == this->m_relationStoCat.end()) {
        auto stoSet = this->m_relationStoCat.emplace(relative, std::set<unsigned int>());
        stoSet.first->second.emplace(relationary);
    } else {
        stoIterator->second.emplace(relationary);
    }

    return true;
}

bool trie::Trie_t::removeRelation(unsigned int relative, unsigned int relationary)
{
    auto stoIterator = this->m_relationStoCat.find(relative);
    auto catIterator = this->m_relationCatSto.find(relationary);

    if (catIterator != this->m_relationCatSto.end() && stoIterator != this->m_relationStoCat.end()) {

        auto relativeToRemove = catIterator->second.find(relative);
        auto relationaryToRemove = stoIterator->second.find(relationary);

        if (relativeToRemove != catIterator->second.end()) {
            catIterator->second.erase(relativeToRemove);
        }

        if (relationaryToRemove != stoIterator->second.end()) {
            stoIterator->second.erase(relationaryToRemove);
        }

        return true;
    } else {
        return false;
    }
}

bool trie::Trie_t::removeStore(unsigned int id, bool keepRelations)
{
    auto storeIterator = this->m_storeTable.find(id);

    if (storeIterator != m_storeTable.end()) {
        storeIterator->second.active = false;

        auto storeCatIterator = this->m_relationStoCat.find(id); // search all the categories of this store
        if (storeCatIterator != this->m_relationStoCat.end()) {

            for (auto toSeekAndRemoveCat : storeCatIterator->second) { // for each category
                auto seekStores = this->m_relationCatSto.find(toSeekAndRemoveCat); // search into its stores
                if (seekStores != this->m_relationCatSto.end()) { // and delete the "id" if it exist

                    auto storeFound = seekStores->second.find(id);

                    if (storeFound != seekStores->second.end()) {
                        seekStores->second.erase(storeFound);
                    }
                }
            }

            this->m_relationStoCat.erase(storeCatIterator);
        }

        m_storeTable.erase(storeIterator);

        return true;
    } else {
        return false;
    }
}

bool trie::Trie_t::removeCategory(unsigned int id, bool keepRelations)
{
    auto categoryIterator = this->m_categoryTable.find(id);

    if (categoryIterator != m_categoryTable.end()) { // find the category on the table

        auto catStoIterator = this->m_relationCatSto.find(id);

        if (catStoIterator != this->m_relationCatSto.end()) {
            for (auto stoId : catStoIterator->second) {

                auto stoCatIterator = this->m_relationStoCat.find(stoId);

                if (stoCatIterator != this->m_relationStoCat.end()) {
                    auto catFound = stoCatIterator->second.find(id);

                    if (catFound != stoCatIterator->second.end()) {
                        stoCatIterator->second.erase(catFound);
                    }
                }
            }

            this->m_relationCatSto.erase(catStoIterator);
        }

        this->m_categoryTable.erase(categoryIterator);
        return true;

    } else {
        return false;
    }
}

UData::Store_t trie::Trie_t::getStore(unsigned int id)
{
    return this->m_storeTable.find(id)->second;
}
UData::Category_t trie::Trie_t::getCategory(unsigned int id)
{
    return this->m_categoryTable.find(id)->second;
}
