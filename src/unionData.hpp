#pragma once
#include "json.hpp"
#include <string>
#include <vector>

namespace UData {

struct Store_t {
    unsigned int id;
    std::string name;
    std::string lat;
    std::string lng;
    std::string max_radius;
    std::string address;
    std::string phone;
    std::string brand;
    nlohmann::json jsonObject;
    bool active;
    Store_t(unsigned int, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
    Store_t(unsigned int, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const nlohmann::json&);
};

struct Category_t {
    unsigned int id;
    std::string name;
    nlohmann::json jsonObject;
    bool active;
    Category_t(unsigned int, const std::string&);
    Category_t(unsigned int, const std::string&, const nlohmann::json&);
};

struct StoreComparator_t {
    bool operator()(const Store_t&, const Store_t&) const;
};

struct CategoryComparator_t {
    bool operator()(const Category_t&, const Category_t&) const;
};

void buildJson(Store_t&);
void buildJson(Category_t&);
void updateAll(Store_t&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
void updateAll(Category_t&, const std::string&);
std::vector<std::string> split(const std::string&, char delimiter);
unsigned int string2unsigned(const std::string&);
}
