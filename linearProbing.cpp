#include <iostream>
using namespace std;

// Constants for table size
const int SIZE = 10;

int hashFunction(int key) {
    return key % SIZE;
}

// Linear Probing Insert with Replacement
void insertLinear(int key, int arr[SIZE]) {
    int index = hashFunction(key);
    int i = 0;
    while (i < SIZE) {
        int newIndex = (index + i) % SIZE;
        if (arr[newIndex] == -1) {  // Empty slot found, insert the key
            arr[newIndex] = key;
            cout << "Inserted " << key << " successfully using Linear Probing." << endl;
            return;
        } else if (arr[newIndex] == key) {  // If the key is already there, replace it
            arr[newIndex] = key;
            cout << "Key " << key << " already exists. Replaced with the new value using Linear Probing." << endl;
            return;
        }
        i++;
    }
    cout << "Table is full. Cannot insert using Linear Probing." << endl;
}

// Quadratic Probing Insert with Replacement
// void insertQuadratic(int key, int arr[SIZE]) {
//     int index = hashFunction(key);
//     int i = 0;
//     while (i < SIZE) {
//         int newIndex = (index + i * i) % SIZE;
//         if (arr[newIndex] == -1) {  // Empty slot found, insert the key
//             arr[newIndex] = key;
//             cout << "Inserted " << key << " successfully using Quadratic Probing." << endl;
//             return;
//         } else if (arr[newIndex] == key) {  // If the key is already there, replace it
//             arr[newIndex] = key;
//             cout << "Key " << key << " already exists. Replaced with the new value using Quadratic Probing." << endl;
//             return;
//         }
//         i++;
//     }
//     cout << "Table is full. Cannot insert using Quadratic Probing." << endl;
// }

// Without Replacement Insert (No replacement allowed)
void insertWithoutReplacement(int key, int arr[SIZE]) {
    int index = hashFunction(key);
    if (arr[index] == -1) {
        arr[index] = key;
        cout << "Inserted " << key << " successfully without replacement." << endl;
    } else {
        cout << "Collision occurred. Skipping " << key << " without replacement." << endl;
    }
}

// Search Function
int search(int key, int arr[SIZE]) {
    int index = hashFunction(key);
    int i = 0;
    while (i < SIZE) {
        int newIndex = (index + i) % SIZE;
        if (arr[newIndex] == key) {
            cout << key << " found at index: " << newIndex << endl;
            return newIndex;
        } else if (arr[newIndex] == -1) {
            cout << key << " not found!" << endl;
            return -1;
        }
        i++;
    }
    cout << key << " not found!" << endl;
    return -1;
}

// Delete Function
void deleteKey(int key, int arr[SIZE]) {
    int index = search(key, arr);
    if (index != -1) {
        arr[index] = -1;
        cout << "Element " << key << " deleted successfully!" << endl;
    } else {
        cout << "Element " << key << " not found in the hash table!" << endl;
    }
}

// Display Function
void display(int arr[SIZE]) {
    cout << "The hash table is: ";
    for (int i = 0; i < SIZE; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Load Factor Calculation
float loadFactor(int arr[SIZE]) {
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        if (arr[i] != -1) {
            count++;
        }
    }
    return (float)count / SIZE;
}

// Main Menu Driven Program
int main() {
    int arr[SIZE];

    // Initialize hash table with -1 indicating empty slots
    fill(begin(arr), end(arr), -1);

    int method = 0;
    int choice;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Set Hashing Method\n";
        cout << "2. Insert\n";
        cout << "3. Display\n";
        cout << "4. Search\n";
        cout << "5. Delete\n";
        cout << "6. Load Factor\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Set Hashing Method
                cout << "Choose Hashing Method:\n";
                cout << "1. Linear Probing with replacement\n";
                // cout << "2. Quadratic Probing\n";
                cout << "2. Without Replacement\n";
                cout << "Enter your choice: ";
                cin >> method;
                break;

            case 2: {
                // Insert based on chosen method
                int key;
                cout << "Enter the key to insert: ";
                cin >> key;

                if (method == 1) {
                    insertLinear(key, arr);
                } 
                // else if (method == 2) {
                //     insertQuadratic(key, arr);
                // }
                 else if (method == 2) {
                    insertWithoutReplacement(key, arr);
                } else {
                    cout << "Invalid method selected!" << endl;
                }
                break;
            }

            case 3:
                // Display hash table
                display(arr);
                break;

            case 4: {
                // Search in the hash table
                int key;
                cout << "Enter the key to search: ";
                cin >> key;
                search(key, arr);
                break;
            }

            case 5: {
                // Delete from hash table
                int key;
                cout << "Enter the key to delete: ";
                cin >> key;
                deleteKey(key, arr);
                break;
            }

            case 6:
                // Load factor
                cout << "Load factor: " << loadFactor(arr) << endl;
                break;

            case 7:
                cout << "Exiting program..." << endl;
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
