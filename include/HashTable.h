#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Facility.h"
#include <vector>
using namespace std;

class HashTable {
private:
    static const int INITIAL_CAPACITY = 11; // Initial capacity of the hashtable

    vector<vector<Facility>> table; // Vector of vectors to store Facility objects
    int entries; // Number of entries in the hashtable
    int collisions; // Number of collisions in the hashtable

    string normalizeID(string id) const; // Normalize the ID by converting it to lowercase and removing whitespace
    int hashFunction(string id) const; // Hash function to compute the index for a given ID

public:
    HashTable();

    bool insert(Facility facility); // Insert a Facility object into the 
    const Facility* search(string id) const; // Search for a Facility object by its ID

    int getCapacity() const; // Get the current capacity of the hashtable
    int getEntries() const; // Get the number of entries in the hashtable
    int getCollisions() const; // Get the number of collisions in the hashtable
};

#endif
