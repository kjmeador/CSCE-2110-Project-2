#include "../include/FacilityDatabase.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

string FacilityDatabase::normalizeID(string id) const {
    for (int i = 0; i < id.length(); i++) {
        id[i] = toupper(static_cast<unsigned char>(id[i]));
    }

    return id;
}

bool FacilityDatabase::isValidID(string id) const {
    id = normalizeID(id);

    if (id.length() != 4 || id[0] != 'F') {
        return false;
    }

    for (int i = 1; i < 4; i++) {
        if (!isdigit(static_cast<unsigned char>(id[i]))) {
            return false;
        }
    }

    return true;
}

void FacilityDatabase::loadFacilities(string filename, const CampusGraph& graph) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        cout << "Accepted: 0 | Rejected: 0" << endl;
        return;
    }

    string line;
    int lineNumber = 0;
    int accepted = 0;
    int rejected = 0;

    while (getline(file, line)) {
        lineNumber++;

        if (line.find_first_not_of(" \t\r\n") == string::npos) {
            continue;
        }

        size_t comment = line.find_first_not_of(" \t\r\n");

        if (line[comment] == '#') {
            continue;
        }

        string fields[4];
        stringstream ss(line);
        string field;
        int fieldCount = 0;

        while (getline(ss, field, '|') && fieldCount < 4) {
            size_t start = field.find_first_not_of(" \t\r\n");

            if (start == string::npos) {
                field = "";
            } else {
                size_t end = field.find_last_not_of(" \t\r\n");
                field = field.substr(start, end - start + 1);
            }

            fields[fieldCount] = field;
            fieldCount++;
        }

        if (fieldCount != 4 || getline(ss, field, '|')) {
            cout << "Warning: " << filename << " line " << lineNumber
                 << ": expected four fields." << endl;
            rejected++;
            continue;
        }

        string id = normalizeID(fields[0]);
        string name = fields[1];
        string building = fields[2];
        string category = fields[3];

        if (!isValidID(id) || name.empty() ||
            building.empty() || category.empty()) {
            cout << "Warning: " << filename << " line " << lineNumber
                 << ": invalid facility data." << endl;
            rejected++;
            continue;
        }

        string originalBuilding;

        if (!graph.getBuildingName(building, originalBuilding)) {
            cout << "Warning: " << filename << " line " << lineNumber
                 << ": building does not exist." << endl;
            rejected++;
            continue;
        }

        Facility facility(id, name, originalBuilding, category);

        if (!table.insert(facility)) {
            cout << "Warning: " << filename << " line " << lineNumber
                 << ": duplicate facility ID." << endl;
            rejected++;
            continue;
        }

        facilities.push_back(facility);
        accepted++;
    }

    cout << filename << " - Accepted: " << accepted
         << " | Rejected: " << rejected << endl;

    cout << "Hash Table Capacity: " << table.getCapacity() << endl;
    cout << "Hash Table Entries: " << table.getEntries() << endl;
    cout << "Hash Table Collisions: " << table.getCollisions() << endl;
}

void FacilityDatabase::displayFacilities() const {
    cout << "\nAll Facilities\n";

    if (facilities.empty()) {
        cout << "No facilities loaded." << endl;
        return;
    }

    for (int i = 0; i < facilities.size(); i++) {
        cout << "ID: " << facilities[i].getId()
             << " | Name: " << facilities[i].getName()
             << " | Building: " << facilities[i].getBuilding()
             << " | Category: " << facilities[i].getCategory()
             << endl;
    }
}

void FacilityDatabase::searchFacility(string id) const {
    id = normalizeID(id);

    if (!isValidID(id)) {
        cout << "Invalid facility ID. Use F followed by three digits." << endl;
        return;
    }

    const Facility* facility = table.search(id);

    if (facility == nullptr) {
        cout << "Facility not found." << endl;
        return;
    }

    cout << "\nFacility Found\n";
    cout << "ID: " << facility->getId() << endl;
    cout << "Name: " << facility->getName() << endl;
    cout << "Building: " << facility->getBuilding() << endl;
    cout << "Category: " << facility->getCategory() << endl;
}

int FacilityDatabase::getCapacity() const {
    return table.getCapacity();
}

int FacilityDatabase::getEntries() const {
    return table.getEntries();
}

int FacilityDatabase::getCollisions() const {
    return table.getCollisions();
}
