#include <string>

struct Person {
    std::string name;
    int age;
    bool operator()(const Person& p1, const Person& p2)
    {
        return p1.age < p2.age;
    }
};