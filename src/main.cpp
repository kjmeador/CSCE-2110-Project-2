#include <iostream>
#include <string>

#include "../include/FacilityDatabase.h"
#include "../include/CampusGraph.h"
#include "../include/DepartmentTree.h"

using namespace std;

int main(int argc, char* argv[]) {
    string dataFolder = "data";

    if (argc > 1) {
        dataFolder = argv[1];
    }

    if (!dataFolder.empty() &&
        dataFolder[dataFolder.length() - 1] != '/' &&
        dataFolder[dataFolder.length() - 1] != '\\') {
        dataFolder += "/";
    }

    string buildingsFile = dataFolder + "buildings.txt";
    string connectionsFile = dataFolder + "connections.txt";
    string facilitiesFile = dataFolder + "facilities.txt";
    string departmentsFile = dataFolder + "departments.txt";

    CampusGraph campusGraph;
    FacilityDatabase facilityDatabase;
    DepartmentTree departmentTree;

    cout << "======================================" << endl;
    cout << "   CAMPUS RESOURCE EXPLORATION SYSTEM" << endl;
    cout << "======================================" << endl;

    cout << "\nLoading campus data...\n" << endl;

    campusGraph.loadBuildings(buildingsFile);
    campusGraph.loadConnections(connectionsFile);
    facilityDatabase.loadFacilities(facilitiesFile, campusGraph);
    departmentTree.loadDepartments(departmentsFile);

    int choice;

    do {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "1. View All Facilities" << endl;
        cout << "2. Search Facility by ID" << endl;
        cout << "3. View Campus Graph" << endl;
        cout << "4. Display Graph Statistics" << endl;
        cout << "5. Find Reachable Buildings (BFS)" << endl;
        cout << "6. Add Department" << endl;
        cout << "7. Search Department" << endl;
        cout << "8. Display Department Hierarchy" << endl;
        cout << "9. Run Preorder Traversal" << endl;
        cout << "10. Exit" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cin.ignore(10000, '\n');

        string input;
        string parent;

        switch (choice) {
            case 1:
                facilityDatabase.displayFacilities();
                break;

            case 2:
                cout << "Enter facility ID: ";
                getline(cin, input);

                if (input.find_first_not_of(" \t\r\n") == string::npos) {
                    cout << "Facility ID cannot be blank." << endl;
                    break;
                }

                facilityDatabase.searchFacility(input);
                break;

            case 3:
                campusGraph.displayGraph();
                break;

            case 4:
                campusGraph.displayStats();
                cout << "\nHash Table Statistics" << endl;
                cout << "Capacity: " << facilityDatabase.getCapacity() << endl;
                cout << "Entries: " << facilityDatabase.getEntries() << endl;
                cout << "Collisions: " << facilityDatabase.getCollisions() << endl;
                break;

            case 5:
                cout << "Enter starting building: ";
                getline(cin, input);

                if (input.find_first_not_of(" \t\r\n") == string::npos) {
                    cout << "Building name cannot be blank." << endl;
                    break;
                }

                campusGraph.findReachable(input);
                break;

            case 6:
                cout << "Enter new department name: ";
                getline(cin, input);

                if (input.find_first_not_of(" \t\r\n") == string::npos) {
                    cout << "Department name cannot be blank." << endl;
                    break;
                }

                cout << "Enter parent department name: ";
                getline(cin, parent);

                if (parent.find_first_not_of(" \t\r\n") == string::npos) {
                    cout << "Parent name cannot be blank." << endl;
                    break;
                }

                if (departmentTree.addDepartment(input, parent)) {
                    cout << "Department added successfully." << endl;
                } else {
                    cout << "Could not add department. Check the name and parent." << endl;
                }
                break;

            case 7:
                cout << "Enter department name: ";
                getline(cin, input);

                if (input.find_first_not_of(" \t\r\n") == string::npos) {
                    cout << "Department name cannot be blank." << endl;
                    break;
                }

                departmentTree.searchDepartment(input);
                break;

            case 8:
                departmentTree.displayHierarchy();
                break;

            case 9:
                departmentTree.preorderTraversal();
                break;

            case 10:
                cout << "Exiting Campus Resource Exploration System." << endl;
                break;

            default:
                cout << "Invalid choice. Enter a number from 1 to 10." << endl;
        }

    } while (choice != 10);

    return 0;
}
