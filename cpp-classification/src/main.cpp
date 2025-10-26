#include <iostream>
#include <vector>
#include "FileReader.h"
#include "Individual.h"

using namespace std;

int main() {
 /* 
    //day2
    cout << "FILE READING AND JSON PARSING" << endl;
    
    try {
        cout << "\nTEST 1: Reading file and printing raw JSON"<<endl;
        FileReader reader("cpp-classification/resources/test-input.json");
        auto jsonData = reader.readFile();
        reader.printJsonToConsole(jsonData);

        cout << "\nTEST 2: Printing each JSON object separately" << endl;
        reader.printEachObjectSeparately(jsonData);

        cout << "\nTEST 3: Exploring JSON structure" << endl;
        if (jsonData.contains("data") && jsonData["data"].is_array()) {
            cout << "Found 'data' array with " << jsonData["data"].size() << " elements" << endl;
            
            //access first element's properties
            if (!jsonData["data"].empty()) {
                auto firstEntry = jsonData["data"][0];
                cout << "First entry ID: " << firstEntry.value("id", -1) << endl;
                cout << "First entry planet: " << firstEntry.value("planet", "unknown") << endl;
            }
        }
        
    } catch (const exception& e) {
        cerr << "ERROR: " << e.what() << endl;
        return 1;
    }
    
    cout << "\nTESTING COMPLETED SUCCESSFULLY" << endl;

*/



    //day3
    cout << "JSON TO CLASSES MAPPING" << endl;
    
    try {
        FileReader reader("cpp-classification/resources/input.json");
        auto jsonData = reader.readFile();
        auto dataArray = jsonData["data"];
        
        //container for Individual objects
        vector<Individual> individuals;
        
        cout << "\nMAPPING JSON TO INDIVIDUAL OBJECTS" << endl;
        for (const auto& entry : dataArray) {
            individuals.emplace_back(entry);
        }
        
        cout << "Created " << individuals.size() << " Individual objects" << endl;
        
        cout << "\nTEST 1: PRINTING ALL INDIVIDUALS" << endl;
        for (const auto& individual : individuals) {
            individual.printInfo();
        }
        
        cout << "\nTEST 2: PRINTING ONLY IDS" << endl;
        for (const auto& individual : individuals) {
            cout << "ID: " << individual.getId() << endl;
        }
        
        cout << "\nTEST 3: INDIVIDUALS WITH EVEN IDs" << endl;
        for (const auto& individual : individuals) {
            if (individual.getId() % 2 == 0) {
                individual.printInfo();
            }
        }
        
        cout << "\nTEST 4: INDIVIDUALS WITH ODD IDs" << endl;
        for (const auto& individual : individuals) {
            if (individual.getId() % 2 == 1) {
                individual.printInfo();
            }
        }
        
        cout << "\nTEST 5: HUMANOID STATISTICS" << endl;
        int humanoidCount = 0;
        int nonHumanoidCount = 0;
        
        for (const auto& individual : individuals) {
            if (individual.getIsHumanoid()) {
                humanoidCount++;
            } else {
                nonHumanoidCount++;
            }
        }

        cout << "Humanoids: " << humanoidCount << endl;
        cout << "Non-humanoids: " << nonHumanoidCount << endl;
        
        cout << "\nTEST 6: INDIVIDUALS WITH UNKNOWN AGE" << endl;
        for (const auto& individual : individuals) {
            if (individual.getAge() == -1) {
                individual.printInfo();
            }
        }
        
    } catch (const exception& e) {
        cerr << "ERROR: " << e.what() << endl;
        return 1;
    }
    
    cout << "\nMAPPING AND EXPERIMENTATION COMPLETE" << endl;
    return 0;
}