#include "Facility.h"

// Initialize the constructor for the Facility class that takes in the id, name, building, and category as parameters
Facility::Facility(string id, string name, string building, string category){
    this->id = id;
    this->name = name;
    this->building = building;
    this->category = category;
}

// Return the id, name, building, and category of the Facility object
string Facility::getId() const {
    return id;
}

string Facility::getName() const {
    return name;
}

string Facility::getBuilding() const {
    return building;
}

string Facility::getCategory() const {
    return category;
}
