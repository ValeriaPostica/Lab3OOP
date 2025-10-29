#include "Individual.h"
#include <iostream>
#include <algorithm>
#include <cctype>

using json = nlohmann::json;

string toUpper(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// JSON Constructor
Individual::Individual(const json& entry) {
    id = entry.value("id", -1);
    isHumanoid = entry.value("isHumanoid", false);
    
    if (entry.contains("planet")) {
        originPlanet = toUpper(entry["planet"]);
    } else if (entry.contains("originPlanet")) {
        originPlanet = toUpper(entry["originPlanet"]);
    } else {
        originPlanet = "";
    }
    
    age = entry.value("age", -1);
    
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

// Getters
int Individual::getId() const {
    return id;
}

bool Individual::getIsHumanoid() const {
    return isHumanoid;
}

string Individual::getOriginPlanet() const {
    return originPlanet;
}

int Individual::getAge() const {
    return age;
}

vector<string> Individual::getPhysicalTraits() const {
    return physicalTraits;
}

// Helper methods
bool Individual::hasTrait(const string& trait) const {
    string upperTrait = toUpper(trait);
    return find(physicalTraits.begin(), physicalTraits.end(), upperTrait) != physicalTraits.end();
}

bool Individual::hasPlanet() const {
    return !originPlanet.empty();
}

bool Individual::hasAge() const {
    return age != -1;
}

bool Individual::hasHumanoidInfo() const {
    return true; // isHumanoid is always defined
}

//Rule-Based Classification System
string Individual::classify() const {
    // If we have absolutely no data, return undefined
    if (!hasPlanet() && physicalTraits.empty() && !hasAge() && !hasHumanoidInfo()) {
        return "undefined";
    }

    if (hasTrait("EXTRA_ARMS") && hasTrait("EXTRA_HEAD")) {
        return "hitch-hiker";
    }
    
    if (hasTrait("BLONDE") && hasTrait("POINTY_EARS")) {
        return "rings";
    }
    
    if (hasTrait("GREEN") && hasTrait("BULKY")) {
        return "hitch-hiker";
    }
    
    if (hasTrait("SHORT") && hasTrait("BULKY")) {
        return "rings";
    }
    
    if (hasTrait("HAIRY") && hasTrait("TALL")) {
        return "star-wars";
    }
    
    if (hasTrait("SHORT") && hasTrait("HAIRY")) {
        return "star-wars";
    }
    
    if (hasTrait("BLONDE") && hasTrait("TALL")) {
        return "marvel";
    }


    if (hasTrait("EXTRA_ARMS") || hasTrait("EXTRA_HEAD")) {
        return "hitch-hiker";
    }
    
    if (hasTrait("POINTY_EARS")) {
        return "rings";
    }
    
    if (hasTrait("GREEN")) {
        return "hitch-hiker";
    }
    
    if (hasTrait("HAIRY")) {
        return "star-wars";
    }

    if (isHumanoid && hasTrait("BULKY")) {
        return "rings";
    }
    
    if (!isHumanoid && hasTrait("BULKY")) {
        return "hitch-hiker";
    }
    
    
    if (isHumanoid && hasTrait("TALL")) {
        if (hasTrait("BLONDE")) return "marvel";
        return "marvel";
    }
    
    if (isHumanoid && hasTrait("BLONDE")) {
        return "marvel";
    }


    if (originPlanet == "KASHYYYK" && (hasTrait("HAIRY") || hasTrait("TALL"))) {
        return "star-wars";
    }
    
    if (originPlanet == "ENDOR" && (hasTrait("SHORT") || hasTrait("HAIRY"))) {
        return "star-wars";
    }
    
    if (originPlanet == "ASGARD" && (hasTrait("BLONDE") || hasTrait("TALL"))) {
        return "marvel";
    }
    
    if (originPlanet == "BETELGEUSE" && (hasTrait("EXTRA_ARMS") || hasTrait("EXTRA_HEAD"))) {
        return "hitch-hiker";
    }
    
    if (originPlanet == "VOGSPHERE" && (hasTrait("GREEN") || hasTrait("BULKY"))) {
        return "hitch-hiker";
    }
    
    if (originPlanet == "EARTH") {
        if (hasTrait("BLONDE") && hasTrait("POINTY_EARS")) return "rings";
        if (hasTrait("SHORT") && hasTrait("BULKY")) return "rings";
        if (hasTrait("BLONDE") || hasTrait("POINTY_EARS")) return "rings";
        if (hasTrait("SHORT") || hasTrait("BULKY")) return "rings";
    }

    if (isHumanoid && originPlanet == "ASGARD") {
        return "marvel";
    }
    
    if (!isHumanoid && originPlanet == "KASHYYYK") {
        return "star-wars";
    }
    
    if (!isHumanoid && originPlanet == "ENDOR") {
        return "star-wars";
    }
    
    if (isHumanoid && originPlanet == "BETELGEUSE") {
        return "hitch-hiker";
    }
    
    if (!isHumanoid && originPlanet == "VOGSPHERE") {
        return "hitch-hiker";
    }
    
    if (isHumanoid && originPlanet == "EARTH") {
        return "rings";
    }



    if (isHumanoid && (hasTrait("BLONDE") || hasTrait("TALL"))) {
        return "marvel";
    }
    
    if (!isHumanoid && hasTrait("BULKY")) {
        return "hitch-hiker";
    }
    
    if (isHumanoid && hasTrait("BULKY")) {
        return "rings";
    }
    
    if (hasTrait("HAIRY")) {
        return "star-wars";
    }


    if (isHumanoid && physicalTraits.empty() && !hasPlanet()) {
        return "marvel";
    }
    
    if (!isHumanoid && physicalTraits.empty() && !hasPlanet()) {
        return "star-wars";
    }

    return "undefined";
}

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