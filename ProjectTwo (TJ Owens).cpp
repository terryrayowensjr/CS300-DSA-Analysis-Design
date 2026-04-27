#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure for course
struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

// Node structure for BST
struct Node {
    Course course;
    Node* left;
    Node* right;

    // Constructor for node
    Node(Course c) {
        course = c;
        left = nullptr;
        right = nullptr;
    }
};

// BST Class
class BinarySearchTree {

private:
    Node* root; //Root Node

    // Recursive function for inserting a course into the BST
    Node* insert(Node* node, Course course) {

        // If current position is empty, create a new node
        if (node == nullptr) {
            return new Node(course);
        }

        // Compare course numbers to figure out placement
        if (course.courseNumber < node->course.courseNumber) {
            node->left = insert(node->left, course);

        } else {
            node->right = insert(node->right, course);
        }
        return node;
    }

    // Recursive function for printing tree in order
    void inOrder(Node* node) {

        //If node is null, stop recursion
        if (node == nullptr) return;

        inOrder(node->left);
        cout << node->course.courseNumber << ", "
             << node->course.name << endl;

        inOrder(node->right);
    }

    // Recursive function to search for a course
    Course* search(Node* node, string courseNumber) {

        // If node is null, course does not exist
        if (node == nullptr) return nullptr;

        // If course number matches, return pointer to course
        if (node->course.courseNumber == courseNumber) {
            return &(node->course);
        }

        // Decide to search left or right subtree
        if (courseNumber < node->course.courseNumber) {
            return search(node->left, courseNumber);
        }
        else {
            return search(node->right, courseNumber);
        }
    }

public:
    // Constructor that creates empty tree
    BinarySearchTree() {
        root = nullptr;
    }

    // Function to insert a course
    void Insert(Course course) {
        root = insert(root, course);
    }

    // Function to print courses in order
    void InOrder() {
        inOrder(root);
    }

    // Function to search for a course
    Course* Search(string courseNumber) {
        return search(root, courseNumber);
    }
};

BinarySearchTree bst;

// Function to display menu for program
void displayMenu() {
    cout << endl;
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
    cout << endl;
    cout << "What would you like to do? ";
}

// Reads the file and loads data into the BST
void loadDataStructure(string fileName) {

    ifstream file(fileName);
    string line;

    // while loop to read file
    while (getline(file, line)) {

        stringstream ss(line);  // Convert line into a stream for parsing
        string token;           // Temporary variable to hold each value

        Course course;

        // Get First value
        getline(ss, token, ',');
        course.courseNumber = token;

        // Get secon value
        getline(ss, token, ',');
        course.name = token;

        // Get Prerequisites
        while (getline(ss, token, ',')) {
            if (!token.empty()) {
                course.prerequisites.push_back(token);
            }
        }

        // Insert course into BST
        bst.Insert(course);
    }

    cout << "Course List Loaded" << endl;
}

// Prints all courses in sorted order
void printCourseList() {
    bst.InOrder();
}

// Prints a specific course and its prerequisites
void printCourse(string courseNumber) {

    // Search BST for the course
    Course* course = bst.Search(courseNumber);

    // If course exists, print details
    if (course != nullptr) {

        // Print course number and name
        cout << course->courseNumber << ", " << course->name << endl;

        cout << "Prerequisites: ";
        // For loop for prerequisites
        for (int i = 0; i < course->prerequisites.size(); i++) {
            cout << course->prerequisites[i];
            if (i < course->prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

// Main Function
int main() {

    int choice = 0;
    string fileName;
    string courseNumber;

    // While loop to run menu for program
    while (choice != 9) {
        displayMenu();
        cin >> choice;

        switch (choice) { // Switch for menu

            case 1: // load file option
                cout << "Enter file name: ";
                cin.ignore();
                getline(cin,fileName);
                loadDataStructure(fileName);
                break;

            case 2: // display sorted list option
                cout << "Here is a sample schedule:" << endl;
                cout << endl;
                printCourseList();
                break;

            case 3: // search for course option
                cout << "What course do you want to know about? ";
                cin >> courseNumber;
                transform(courseNumber.begin(),
                          courseNumber.end(),
                          courseNumber.begin(), ::toupper);
                printCourse(courseNumber);
                break;

            case 9: // end program option
                cout << "Thank you for using the course planner!" << endl;
                break;

            default: // You had 4 options and you still got it wrong, do it again
                cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}