#include "Individual.h"
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;
using json = nlohmann::json;

string toUpper(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

//maps JSON to Individual object
Individual::Individual(const json& entry) {
    id = entry.value("id", -1);
    isHumanoid = entry.value("isHumanoid", false);
    
    //handle both "planet" and "originPlanet" field names
    if (entry.contains("planet")) {
        originPlanet = toUpper(entry["planet"]);
    } else if (entry.contains("originPlanet")) {
        originPlanet = toUpper(entry["originPlanet"]);
    } else {
        originPlanet = "";
    }
    
    age = entry.value("age", -1);
    
    //handle both "traits" and "physicalTraits" field names
    if (entry.contains("traits") && entry["traits"].is_array()) {
        for (const auto& trait : entry["traits"]) {
            physicalTraits.push_back(toUpper(trait));
        }
    } else if (entry.contains("physicalTraits") && entry["physicalTraits"].is_array()) {
        for (const auto& trait : entry["physicalTraits"]) {
            physicalTraits.push_back(toUpper(trait));
        }
    }
}

//getters
int Individual::getId() const { return id; }
bool Individual::getIsHumanoid() const { return isHumanoid; }
string Individual::getOriginPlanet() const { return originPlanet; }
int Individual::getAge() const { return age; }
vector<string> Individual::getPhysicalTraits() const { return physicalTraits; }

//display method
void Individual::printInfo() const {
    cout << "ID: " << id << endl;
    cout << "Humanoid: " << (isHumanoid ? "Yes" : "No") << endl;
    cout << "Planet: " << (originPlanet.empty() ? "Unknown" : originPlanet) << endl;
    cout << "Age: " << (age == -1 ? "Unknown" : to_string(age)) << endl;
    
    cout << "Traits: ";
    if (physicalTraits.empty()) {
        cout << "None";
    } else {
        for (const auto& trait : physicalTraits) {
            cout << trait << " ";
        }
    }
    
    cout << endl << "-------------------" << endl;
}