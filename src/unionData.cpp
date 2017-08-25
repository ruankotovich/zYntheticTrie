#include "unionData.hpp"
#include <iostream>
#include <sstream>

using namespace UData;

UData::Store_t::Store_t(unsigned int _id, const std::string& _name, const std::string& _lat, const std::string& _lng, const std::string& _max_radius, const std::string& _address, const std::string& _phone, const std::string& _brand)
    : id(_id)
    , name(_name)
    , lat(_lat)
    , lng(_lng)
    , max_radius(_max_radius)
    , address(_address)
    , phone(_phone)
    , brand(_brand)
    , active(true)
{
}
UData::Store_t::Store_t(unsigned int _id, const std::string& _name, const std::string& _lat, const std::string& _lng, const std::string& _max_radius, const std::string& _address, const std::string& _phone, const std::string& _brand, const nlohmann::json& _json)
    : id(_id)
    , name(_name)
    , lat(_lat)
    , lng(_lng)
    , max_radius(_max_radius)
    , address(_address)
    , phone(_phone)
    , brand(_brand)
    , jsonObject(_json)
    , active(true)
{
}

UData::Category_t::Category_t(unsigned int _id, const std::string& _name)
    : id(_id)
    , name(_name)
    , active(true)
{
}
UData::Category_t::Category_t(unsigned int _id, const std::string& _name, const nlohmann::json& _json)
    : id(_id)
    , name(_name)
    , jsonObject(_json)
    , active(true)
{
}

bool UData::CategoryComparator_t::operator()(const Category_t& cat1, const Category_t& cat2) const
{
    return cat1.id < cat2.id;
}

bool UData::StoreComparator_t::operator()(const Store_t& sto1, const Store_t& sto2) const
{
    return sto1.id < sto2.id;
}

void UData::buildJson(Store_t& store)
{
    store.jsonObject["id"] = store.id;
    store.jsonObject["name"] = store.name;
    store.jsonObject["lat"] = store.lat;
    store.jsonObject["lng"] = store.lng;
    store.jsonObject["max_radius"] = store.max_radius;
    store.jsonObject["address"] = store.address;
    store.jsonObject["phone"] = store.phone;
    store.jsonObject["brand"] = store.brand;

    // store.json = "{\"id\":" + std::to_string(store.id) + ",\"name\":\"" + store.name + "\",\"lat\":" + store.lat + ",\"lng\":" + store.lng + ",\"maxRadius\":" + store.max_radius + ",\"address\":\"" + store.address + "\",\"phone\":\"" + store.phone + "\",\"brand\":\"" + store.brand + "\"}";
}

void UData::buildJson(Category_t& cat)
{
    cat.jsonObject["id"] = cat.id;
    cat.jsonObject["name"] = cat.name;
    // cat.json = "{\"id\":" + std::to_string(cat.id) + ",\"name\":\"" + cat.name + "\"}";
}

void UData::updateAll(Category_t& cat, const std::string& name)
{
    cat.name = name;
    UData::buildJson(cat);
}

void UData::updateAll(Store_t& sto, const std::string& name, const std::string& lat, const std::string& lng, const std::string& max_radius, const std::string& address, const std::string& phone, const std::string& brand)
{
    sto.name = name;
    sto.lat = lat;
    sto.lng = lng;
    sto.max_radius = max_radius;
    sto.address = address;
    sto.phone = phone;
    sto.brand = brand;
    UData::buildJson(sto);
}

std::vector<std::string> UData::split(const std::string& str, char delimiter)
{

    std::vector<std::string> internal;
    std::stringstream ss(str);
    std::string tok;

    while (getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}

unsigned int UData::string2unsigned(const std::string& str)
{
    return std::stoul(str);
}
