
#include "../include/HashTable.h"
#include <cctype>
using namespace std;

HashTable::HashTable() {
    table.resize(INITIAL_CAPACITY);
    entries = 0;
    collisions = 0;
}

string HashTable::normalizeID(string id) const {
    size_t start = id.find_first_not_of(" \t\n\r\f\v");

    if (start == string::npos) {
        return "";
    }

    size_t end = id.find_last_not_of(" \t\n\r\f\v");
    id = id.substr(start, end - start + 1);

    for (int i = 0; i < id.length(); i++) {
        id[i] = toupper(static_cast<unsigned char>(id[i]));
    }

    return id;
}

int HashTable::hashFunction(string id) const {
    unsigned long long hash = 0;

    for (int i = 0; i < id.length(); i++) {
        hash = (hash * 31 + static_cast<unsigned char>(id[i])) % table.size();
    }

    return static_cast<int>(hash);
}

bool HashTable::insert(Facility facility) {
    string id = normalizeID(facility.getId());
    int index = hashFunction(id);

    for (int i = 0; i < table[index].size(); i++) {
        if (table[index][i].getId() == id) {
            return false;
        }
    }

    if (!table[index].empty()) {
        collisions++;
    }

    Facility normalizedFacility(
        id,
        facility.getName(),
        facility.getBuilding(),
        facility.getCategory()
    );

    table[index].push_back(normalizedFacility);
    entries++;

    return true;
}

const Facility* HashTable::search(string id) const {
    id = normalizeID(id);
    int index = hashFunction(id);

    for (int i = 0; i < table[index].size(); i++) {
        if (table[index][i].getId() == id) {
            return &table[index][i];
        }
    }

    return nullptr;
}

int HashTable::getCapacity() const {
    return table.size();
}

int HashTable::getEntries() const {
    return entries;
}

int HashTable::getCollisions() const {
    return collisions;
}
