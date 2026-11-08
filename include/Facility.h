#ifndef FACILITY_H
#define FACILITY_H

#include <string>
using namespace std;

class Facility {
private:
    string id;
    string name;
    string building;
    string category;

public:
    // Create a constructor for the Facility class that takes in the id, name, building, and category as parameters
    Facility(string id, string name, string building, string category);
    
    string getId() const;
    string getName() const;
    string getBuilding() const;
    string getCategory() const; 
};

#endif
