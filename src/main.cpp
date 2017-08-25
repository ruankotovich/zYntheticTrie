#include "engine.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

int main(int argc, char* argv[])
{
    trie::Engine engine;
    std::ifstream fistreamCat(argv[1]);
    std::ifstream fistreamSto(argv[2]);
    std::ifstream fistreamRel(argv[3]);
    std::string currentLine;

    while (std::getline(fistreamCat, currentLine)) {
        auto cat_got = UData::split(currentLine, ';');
        engine.insertCategory(UData::string2unsigned(cat_got[0]), cat_got[1]);
    }

    while (std::getline(fistreamSto, currentLine)) {
        auto sto_got = UData::split(currentLine, ';');
        engine.insertStore(UData::string2unsigned(sto_got[0]), sto_got[1], sto_got[2], sto_got[3], sto_got[4], sto_got[5], sto_got[6], sto_got[7]);
    }

    while (std::getline(fistreamRel, currentLine)) {
        auto rel_got = UData::split(currentLine, ',');
        engine.newRelationStoreCategory(UData::string2unsigned(rel_got[0]), UData::string2unsigned(rel_got[1]));
    }

    engine.init();

    char command;
    std::cout << "\n > ";

    while (cin >> command) {
        switch (command) {
        case 'P':
        case 'p': {
            engine.printTrieInfos();
        } break;

        case 'S':
        case 's': {
            unsigned int id;
            std::cin >> id;
            std::cout << engine.getCategoriesByStore(id) << std::endl;
        } break;

        case 'C':
        case 'c': {
            unsigned int id;
            std::string lat, lng;
            std::cin >> id >> lat >> lng;
            if(lat == ":"){
                lat.clear();
            }
            std::cout << engine.getStoresByCategory(id, lat, lng) << std::endl;
        } break;

        case 'r':
        case 'R': {
            char wut;
            std::cin >> wut;
            switch (wut) {

            case 'r':
            case 'R': {
                unsigned int id1;
                unsigned int id2;
                std::cin >> id1 >> id2;
                std::cout << engine.removeRelationStoreCategory(id1, id2) << std::endl;
            } break;

            case 's':
            case 'S': {
                unsigned int id1;
                std::cin >> id1;
                std::cout << engine.removeStore(id1) << std::endl;
            } break;

            case 'c':
            case 'C': {
                unsigned int id1;
                std::cin >> id1;
                std::cout << engine.removeCategory(id1) << std::endl;
            } break;
            }
        } break;

        case 'u':
        case 'U': {
            char wut;
            std::cin >> wut;
            switch (wut) {

            case 's':
            case 'S': {
                unsigned int id;
                std::string name;
                std::string lat;
                std::string lng;
                std::string max_radius;
                std::string address;
                std::string phone;
                std::string brand;

                std::cin >> id >> name >> lat >> lng >> max_radius >> address >> phone >> brand;
                std::cout << engine.updateStore(id, name, lat, lng, max_radius, address, phone, brand) << std::endl;

            } break;

            case 'c':
            case 'C': {
                unsigned int id;
                std::string name;
                std::cin >> id >> name;
                std::cout << engine.updateCategory(id, name);
            } break;
            }
        } break;

        case 'F':
        case 'f': {
            char wut;
            std::cin >> wut;

            switch (wut) {
            case 's':
            case 'S': {
                int n_ret, offs;
                std::string realQuery, lat, lng;
                std::cin >> n_ret >> offs >> lat >> lng;

                if (lat == ":") {
                    lat.clear();
                }

                std::getline(std::cin, realQuery);
                realQuery.erase(0, 1);
                std::cout << engine.searchForStore(realQuery, n_ret, offs, lat, lng) << std::endl;
            } break;

            case 'c':
            case 'C': {
                int n_ret, offs;
                std::string realQuery, lat, lng;
                std::cin >> n_ret >> offs >> lat >> lng;

                if (lat == ":") {
                    lat.clear();
                }

                std::getline(std::cin, realQuery);
                realQuery.erase(0, 1);
                std::cout << engine.searchForStoreByCategory(realQuery, n_ret, offs, lat, lng) << std::endl;
            } break;

            case 'w':
            case 'W': {
                int n_ret, offs;
                std::string realQuery, lat, lng;
                std::cin >> n_ret >> offs >> lat >> lng;
                std::getline(std::cin, realQuery);
                realQuery.erase(0, 1);

                if (lat == ":") {
                    lat.clear();
                }

                std::cout << engine.search(realQuery, n_ret, offs, lat, lng) << std::endl;

            } break;
            }
        } break;
        }

        std::cout << "\n > ";
    }
}
