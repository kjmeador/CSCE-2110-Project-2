#include "../include/DepartmentTree.h"

#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

DepartmentTree::DepartmentTree() {
    root = nullptr;
}

DepartmentTree::~DepartmentTree() {
    deleteTree(root);
}

string DepartmentTree::normalizeName(string name) const {
    size_t start = name.find_first_not_of(" \t\r\n");

    if (start == string::npos) {
        return "";
    }

    size_t end = name.find_last_not_of(" \t\r\n");
    name = name.substr(start, end - start + 1);

    for (int i = 0; i < name.length(); i++) {
        name[i] = tolower(static_cast<unsigned char>(name[i]));
    }

    return name;
}

DepartmentTree::Department* DepartmentTree::findDepartment(string name) const {
    if (root == nullptr) {
        return nullptr;
    }

    if (normalizeName(root->name) == normalizeName(name)) {
        return root;
    }

    for (int i = 0; i < root->children.size(); i++) {
        Department* found = root->children[i];

        if (normalizeName(found->name) == normalizeName(name)) {
            return found;
        }

        vector<Department*> stack;

        stack.push_back(found);

        while (!stack.empty()) {
            Department* current = stack.back();
            stack.pop_back();

            if (normalizeName(current->name) == normalizeName(name)) {
                return current;
            }

            for (int j = 0; j < current->children.size(); j++) {
                stack.push_back(current->children[j]);
            }
        }
    }

    return nullptr;
}

bool DepartmentTree::addDepartment(string name, string parentName) {
    size_t start = name.find_first_not_of(" \t\r\n");

    if (start == string::npos) {
        return false;
    }

    size_t end = name.find_last_not_of(" \t\r\n");
    name = name.substr(start, end - start + 1);

    if (normalizeName(name) == "" ||
        findDepartment(name) != nullptr) {
        return false;
    }

    if (root == nullptr) {
        if (normalizeName(parentName) != "none") {
            return false;
        }

        root = new Department;
        root->name = name;
        root->parent = nullptr;

        return true;
    }

    Department* parent = findDepartment(parentName);

    if (parent == nullptr) {
        return false;
    }

    Department* newDepartment = new Department;

    newDepartment->name = name;
    newDepartment->parent = parent;

    parent->children.push_back(newDepartment);

    return true;
}

void DepartmentTree::loadDepartments(string filename) {
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

        size_t separator = line.find('|');

        if (separator == string::npos ||
            line.find('|', separator + 1) != string::npos) {
            cout << "Warning: " << filename << " line " << lineNumber
                 << ": invalid department format." << endl;
            rejected++;
            continue;
        }

        string name = line.substr(0, separator);
        string parent = line.substr(separator + 1);

        if (addDepartment(name, parent)) {
            accepted++;
        } else {
            cout << "Warning: " << filename << " line " << lineNumber
                 << ": invalid department or parent." << endl;
            rejected++;
        }
    }

    cout << filename << " - Accepted: " << accepted
         << " | Rejected: " << rejected << endl;
}

void DepartmentTree::searchDepartment(string name) const {
    Department* department = findDepartment(name);

    if (department == nullptr) {
        cout << "Department not found." << endl;
        return;
    }

    cout << "Department found: " << department->name << endl;

    if (department->parent != nullptr) {
        cout << "Parent: " << department->parent->name << endl;
    } else {
        cout << "Parent: None (Root)" << endl;
    }

    cout << "Children: ";

    if (department->children.empty()) {
        cout << "None";
    } else {
        for (int i = 0; i < department->children.size(); i++) {
            cout << department->children[i]->name;

            if (i < department->children.size() - 1) {
                cout << ", ";
            }
        }
    }

    cout << endl;
}

void DepartmentTree::displayHierarchy(Department* department, int depth) const {
    if (department == nullptr) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        cout << "    ";
    }

    cout << department->name << endl;

    for (int i = 0; i < department->children.size(); i++) {
        displayHierarchy(department->children[i], depth + 1);
    }
}

void DepartmentTree::displayHierarchy() const {
    cout << "\nDepartment Hierarchy\n";

    if (root == nullptr) {
        cout << "No departments loaded." << endl;
        return;
    }

    displayHierarchy(root, 0);
}

void DepartmentTree::preorderTraversal(Department* department) const {
    if (department == nullptr) {
        return;
    }

    cout << department->name << endl;

    for (int i = 0; i < department->children.size(); i++) {
        preorderTraversal(department->children[i]);
    }
}

void DepartmentTree::preorderTraversal() const {
    cout << "\nPreorder Traversal\n";

    if (root == nullptr) {
        cout << "No departments loaded." << endl;
        return;
    }

    preorderTraversal(root);
}

void DepartmentTree::deleteTree(Department* department) {
    if (department == nullptr) {
        return;
    }

    for (int i = 0; i < department->children.size(); i++) {
        deleteTree(department->children[i]);
    }

    delete department;
}
