#ifndef FACILITYDATABASE_H
#define FACILITYDATABASE_H

#include "Facility.h"
#include "HashTable.h"
#include "CampusGraph.h"

#include <vector>
#include <string>

using namespace std;

class FacilityDatabase {
private:
    vector<Facility> facilities;
    HashTable table;

    string normalizeID(string id) const;
    bool isValidID(string id) const;

public:
    void loadFacilities(string filename, const CampusGraph& graph);

    void displayFacilities() const;
    void searchFacility(string id) const;

    int getCapacity() const;
    int getEntries() const;
    int getCollisions() const;
};

#endif
