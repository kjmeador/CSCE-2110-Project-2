#include "../include/HashTable.h"
#include <cctype>
using namespace std;

HashTable::HashTable() {
    table.resize(INITIAL_CAPACITY); // Initialize the hashtable with the initial capacity
    entries = 0; // Initialize the number of entries to 0
    collisions = 0; // Initialize the number of collisions to 0
}

string HashTable::normalizeID(string id) const {
    size_t start = id.find_first_not_of(" \t\n\r\f\v"); // Find the first non-whitespace character

    if (start == string::npos) {
        return ""; // Return an empty string if the ID is all whitespace
    }

    size_t end = id.find_last_not_of(" \t\n\r\f\v"); // Find the last non-whitespace character
    id = id.substr(start, end - start + 1); // Extract the substring without leading/trailing whitespace

    for (int i = 0; i < id.length(); i++) {
        id[i] = toupper(static_cast<unsigned char>(id[i])); // Convert each character to uppercase
    }

    return id; // Return the normalized ID
}

int HashTable::hashFunction(string id) const {
    unsigned long long hash = 0;

    for (int i = 0; i < id.length(); i++) {
        hash = hash * 31 + id[i] % table.size(); // Compute the hash value using a polynomial rolling hash function
    }

    return hash;
}

bool HashTable::insert(Facility facility) {
    string id = normalizeID(facility.getId()); // Normalize the ID of the Facility object
    int index = hashFunction(id); // Compute the index for the normalized ID

    for (int i = 0; i < table[index].size(); i++) {
        if (table[index][i].getId() == id) {
            return false; // Return false if the ID already exists in the hashtable
        }
    }

    if (!table[index].empty()) {
        collisions++; // Increment the collision count if there is already an entry at the computed index
    }

    Facility normalizedFacility(
        id,
        facility.getName(),
        facility.getBuilding(),
        facility.getCategory()
    );

    table[index].push_back(normalizedFacility); // Insert the normalized Facility object into the hashtable
    entries++; // Increment the entry count

    return true; // Return true to indicate successful insertion
}  

const Facility* HashTable::search(string id) const {
    id = normalizeID(id); // Normalize the ID to search for
    int index = hashFunction(id); // Compute the index for the normalized ID

    for (int i = 0; i < table[index].size(); i++) {
        if (table[index][i].getId() == id) {
            return &table[index][i]; // Return a pointer to the Facility object if found
        }
    }

    return nullptr; // Return nullptr if the Facility object is not found
}

int HashTable::getCapacity() const {
    return table.size(); // Return the current capacity of the hashtable
}

int HashTable::getEntries() const {
    return entries; // Return the number of entries in the hashtable
}

int HashTable::getCollisions() const {
    return collisions; // Return the number of collisions in the hashtable
}
