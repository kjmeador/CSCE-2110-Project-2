#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <string>
#include <vector>
using namespace std;

class CampusGraph {
private:
    struct Building {
        string name;
        vector<int> neighbors; // Indices of neighboring buildings in the graph
    };

    vector<Building> buildings; // Vector to store all buildings in the graph

    int findBuilding(string name) const; // Helper function to find the index of a building by its name
    string normalizeName(string name) const; // Normalize the building name by converting it to lowercase and removing whitespace

public:
    void loadBuildings(string filename); // Load buildings and their connections from a file
    void loadConnections(string filename); // Load connections between buildings from a file

    void displayGraph() const; // Display the graph of buildings and their connections
    void displayStats() const; // Display statistics about the graph, such as the number of buildings and connections

    void findReachable(string startName) const;  // Finds reachable buildings using BFS.
};

#endif
