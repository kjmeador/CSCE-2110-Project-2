// DepartmentTree.h
// Defines the university department hierarchy.

#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H

#include <string>
#include <vector>
using namespace std;

class DepartmentTree {
private:
    struct Department {
        string name;
        Department* parent;
        vector<Department*> children;
    };

    Department* root;

    // Finds a department by name.
    Department* findDepartment(string name) const;

    // Normalizes names for comparison.
    string normalizeName(string name) const;

    // Displays the hierarchy recursively.
    void displayHierarchy(Department* department, int depth) const;

    // Performs preorder traversal.
    void preorderTraversal(Department* department) const;

    // Frees dynamically allocated nodes.
    void deleteTree(Department* department);

public:
    DepartmentTree();
    ~DepartmentTree();

    // Loads departments from a file.
    void loadDepartments(string filename);

    // Adds a department under an existing parent.
    bool addDepartment(string name, string parentName);

    // Searches for a department.
    void searchDepartment(string name) const;

    // Displays the department hierarchy.
    void displayHierarchy() const;

    // Displays preorder traversal.
    void preorderTraversal() const;
};

#endif
