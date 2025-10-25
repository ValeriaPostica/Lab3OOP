#include <iostream>
#include "FileReader.h"

using namespace std;
using json = nlohmann::json;

int main() {
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
    return 0;
}