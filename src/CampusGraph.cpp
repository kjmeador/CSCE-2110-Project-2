#include "../include/CampusGraph.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <queue>
using namespace std;

string CampusGraph::normalizeName(string name) const {
    size_t start = name.find_first_not_of(" \t\r\n\f\v"); // Find the first non-whitespace character

    if (start == string::npos) {
        return ""; // Return an empty string if the name is all whitespace
    }

    size_t end = name.find_last_not_of(" \t\r\n\f\v"); // Find the last non-whitespace character
    name = name.substr(start, end - start + 1); // Extract the substring without leading/trailing whitespace

    for (int i = 0; i < name.length(); i++) {
        name[i] = tolower(static_cast<unsigned char>(name[i]));
    }

    return name; // Return the normalized name
}

int CampusGraph::findBuilding(string name) const {
    string normalizedName = normalizeName(name); // Normalize the building name

    for (int i = 0; i < buildings.size(); i++) {
        if (normalizeName(buildings[i].name) == normalizedName) {
            return i; // Return the index of the building if found
        }
    }

    return -1; // Return -1 if the building is not found
}

void CampusGraph::loadBuildings(string filename) {
    ifstream file(filename);

    int accepted = 0;
    int rejected = 0;
    int lineNumber = 0;

    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        cout << filename << ": 0 accepted, 0 rejected" << endl;
        return;
    }

    string line;

    while (getline(file, line)) {
        lineNumber++;

        size_t start = line.find_first_not_of(" \t\r\n\f\v"); // Find the first non-whitespace character

        if (start == string::npos || line[start] == '#') {
            continue; // Skip empty lines and comments
        }

        size_t end = line.find_last_not_of(" \t\r\n\f\v"); // Find the last non-whitespace character
        string name = line.substr(start, end - start + 1); // Extract the building name without leading/trailing whitespace

        if(name.find('|') != string::npos) {
            cout << "Warning: " << filename << ", line " << lineNumber << ": Wrong field count." << endl;
            rejected++;
            continue; // Skip buildings with wrong field count
        }

        if (findBuilding(name) != -1) {
            cout << "Warning: " << filename << ", line " << lineNumber << ": Duplicate building name." << endl;
            rejected++;
            continue; // Skip duplicate buildings
        }
    
        Building newBuilding;
        newBuilding.name = name;
        buildings.push_back(newBuilding); // Add the new building to the graph
        accepted++;
    }

    cout << filename << ": " << accepted << " accepted, " << rejected << " rejected" << endl;

    file.close();
}

void CampusGraph::loadConnections(string filename) {
    ifstream file(filename);

    int accepted = 0;
    int rejected = 0;
    int lineNumber = 0;

    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        cout << filename << ": 0 accepted, 0 rejected." << endl;
        return;
    }

    string line;

    while (getline(file, line)) {
        lineNumber++;

        size_t start = line.find_first_not_of(" \t\r\n");

        // Ignore blank lines and comments.
        if (start == string::npos || line[start] == '#') {
            continue;
        }

        size_t separator = line.find('|');

        if (separator == string::npos ||
            line.find('|', separator + 1) != string::npos) {
            cout << "Warning: " << filename << " line "
                 << lineNumber << ": Wrong field count." << endl;
            rejected++;
            continue;
        }

        string buildingA = line.substr(0, separator);
        string buildingB = line.substr(separator + 1);

        buildingA = buildingA.substr(
            buildingA.find_first_not_of(" \t\r\n"),
            buildingA.find_last_not_of(" \t\r\n") -
            buildingA.find_first_not_of(" \t\r\n") + 1
        );

        buildingB = buildingB.substr(
            buildingB.find_first_not_of(" \t\r\n"),
            buildingB.find_last_not_of(" \t\r\n") -
            buildingB.find_first_not_of(" \t\r\n") + 1
        );

        if (buildingA.empty() || buildingB.empty()) {
            cout << "Warning: " << filename << " line "
                 << lineNumber << ": Empty building name." << endl;
            rejected++;
            continue;
        }

        int indexA = findBuilding(buildingA);
        int indexB = findBuilding(buildingB);

        if (indexA == -1 || indexB == -1) {
            cout << "Warning: " << filename << " line "
                 << lineNumber << ": Unknown building reference." << endl;
            rejected++;
            continue;
        }

        if (indexA == indexB) {
            cout << "Warning: " << filename << " line "
                 << lineNumber << ": Self-connection." << endl;
            rejected++;
            continue;
        }

        bool duplicate = false;

        for (int i = 0; i < buildings[indexA].neighbors.size(); i++) {
            if (buildings[indexA].neighbors[i] == indexB) {
                duplicate = true;
                break;
            }
        }

        if (duplicate) {
            cout << "Warning: " << filename << " line "
                 << lineNumber << ": Duplicate connection." << endl;
            rejected++;
            continue;
        }

        // Add the connection to both buildings.
        buildings[indexA].neighbors.push_back(indexB);
        buildings[indexB].neighbors.push_back(indexA);

        accepted++;
    }

    cout << filename << ": " << accepted << " accepted, "
         << rejected << " rejected." << endl;

    file.close();
}

// Displays every building and its neighbors.
void CampusGraph::displayGraph() const {
    if (buildings.empty()) {
        cout << "No buildings available." << endl;
        return;
    }

    cout << "\nCampus Graph\n";

    for (int i = 0; i < buildings.size(); i++) {
        cout << buildings[i].name << ": ";

        if (buildings[i].neighbors.empty()) {
            cout << "(no connections)";
        }
        else {
            for (int j = 0; j < buildings[i].neighbors.size(); j++) {
                cout << buildings[buildings[i].neighbors[j]].name;

                if (j < buildings[i].neighbors.size() - 1) {
                    cout << ", ";
                }
            }
        }

        cout << endl;
    }
}

// Displays total buildings, connections, and degrees.
void CampusGraph::displayStats() const {
    if (buildings.empty()) {
        cout << "No buildings available." << endl;
        return;
    }

    int totalConnections = 0;

    for (int i = 0; i < buildings.size(); i++) {
        totalConnections += buildings[i].neighbors.size();
    }

    totalConnections /= 2;

    cout << "\nGraph Statistics\n";
    cout << "Total buildings: " << buildings.size() << endl;
    cout << "Total connections: " << totalConnections << endl;

    for (int i = 0; i < buildings.size(); i++) {
        cout << buildings[i].name << " - Degree: "
             << buildings[i].neighbors.size() << endl;
    }
}

// Finds reachable buildings using Breadth-First Search.
void CampusGraph::findReachable(string startName) const {
    int startIndex = findBuilding(startName);

    // Check whether the starting building exists.
    if (startIndex == -1) {
        cout << "Error: Building not found." << endl;
        return;
    }

    vector<bool> visited(buildings.size(), false);
    vector<int> distance(buildings.size(), -1);
    queue<int> q;

    // Start BFS at the selected building.
    visited[startIndex] = true;
    distance[startIndex] = 0;
    q.push(startIndex);

    cout << "\nReachable Buildings from "
         << buildings[startIndex].name << ":\n";

    int reachableCount = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        cout << buildings[current].name
             << " - Distance: " << distance[current] << endl;

        reachableCount++;

        // Visit each unvisited neighbor.
        for (int i = 0; i < buildings[current].neighbors.size(); i++) {
            int neighbor = buildings[current].neighbors[i];

            if (!visited[neighbor]) {
                visited[neighbor] = true;
                distance[neighbor] = distance[current] + 1;
                q.push(neighbor);
            }
        }
    }

    cout << "\nTotal reachable buildings: "
         << reachableCount << " out of " << buildings.size() << endl;
}

// Checks whether a building exists and returns its original name.
bool CampusGraph::getBuildingName(
    string name, string& originalName) const {

    int index = findBuilding(name);

    if (index == -1) {
        return false;
    }

    originalName = buildings[index].name;
    return true;
}
