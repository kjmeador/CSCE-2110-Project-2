CAMPUS RESOURCE EXPLORATION SYSTEM
Project 2 - Milestone 1

PURPOSE
This program allows users to explore campus facilities, buildings,
connections, and department organization.

DATA STRUCTURES
1. Custom Hash Table
   Stores facilities using facility IDs as keys.
   Uses a custom hash function and separate chaining.

2. Campus Graph
   Represents buildings and their connections using an adjacency list.
   Uses Breadth-First Search (BFS) to find reachable buildings.

3. Department Tree
   Represents the university's department hierarchy.
   Supports adding, searching, displaying, and preorder traversal.

PROJECT STRUCTURE
Project2/
    include/
    src/
    data/
    testdata/
    README.txt
    CONTRIBUTIONS.txt
    design_document.txt
    test_results.txt
    .gitignore

COMPILATION
Open a terminal in the Project2 folder and run:

g++ -std=c++17 -Wall -Wextra -I include src/main.cpp src/Facility.cpp src/HashTable.cpp src/FacilityDatabase.cpp src/CampusGraph.cpp src/DepartmentTree.cpp -o campus

RUNNING

Windows PowerShell:
.\campus.exe

Optional test data directory:
.\campus.exe testdata

Linux:
./campus

Optional test data directory:
./campus testdata

MENU OPTIONS
1. View All Facilities
2. Search Facility by ID
3. View Campus Graph
4. Display Graph Statistics
5. Find Reachable Buildings (BFS)
6. Add Department
7. Search Department
8. Display Department Hierarchy
9. Run Preorder Traversal
10. Exit
