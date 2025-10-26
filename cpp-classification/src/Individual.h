#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <string>
#include <vector>
#include "../include/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

class Individual {
private:
    int id;
    bool isHumanoid;
    string originPlanet;
    int age;
    vector<string> physicalTraits;

public:
    Individual(const json& entry);
    
    //getters
    int getId() const;
    bool getIsHumanoid() const;
    string getOriginPlanet() const;
    int getAge() const;
    vector<string> getPhysicalTraits() const;
    
    //display method
    void printInfo() const;
};

#endif