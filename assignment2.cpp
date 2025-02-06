
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int Table_size = 13;

class Node {
public:
    string word;
    string meaning;
    Node *next;

    Node(string w, string m) {
        word = w;
        meaning = m;
        next = nullptr;
    }
};

int hashFunction(string word) {
    int hashValue = 0;
    int length = word.length();
    for (int i = 0; i < length; i++) {
        char ch = word[length - i - 1];
        hashValue += int(ch) * pow(10, i);
    }
    return hashValue % Table_size;
}

void insert(Node *hashTable[], string word, string meaning) {
    int index = hashFunction(word);
    Node *newNode = new Node(word, meaning);
    if (hashTable[index] == nullptr) {
        hashTable[index] = newNode;
    } else {
        newNode->next = hashTable[index];
        hashTable[index] = newNode;
    }
}

string search(Node *hashTable[], string word) {
    int index = hashFunction(word);
    Node *temp = hashTable[index];
    while (temp != nullptr) {
        if (temp->word == word) {
            return temp->meaning;
        }
        temp = temp->next;
    }
    return "Word not found";
}

void deleteWord(Node *hashTable[], string word) {
    int index = hashFunction(word);
    Node *temp = hashTable[index];
    Node *prev = nullptr;
    while (temp != nullptr) {
        if (temp->word == word) {
            if (prev == nullptr) {
                hashTable[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;
            cout << "Word '" << word << "' deleted." << endl;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Word not found!" << endl;
}

void display(Node *hashTable[]) {
    bool isEmpty = true;
    for (int i = 0; i < Table_size; i++) {
        cout << "Bucket " << i << ": ";
        Node *temp = hashTable[i];
        if (temp == nullptr) {
            cout << "Empty";
        } else {
            isEmpty = false;
            while (temp != nullptr) {
                cout << temp->word << ": " << temp->meaning << " -> ";
                temp = temp->next;
            }
            cout << "NULL";
        }
        cout << endl;
    }
    if (isEmpty) {
        cout << "The dictionary is empty!" << endl;
    }
}

int main() {
    Node *hashTable[Table_size] = {nullptr};
    insert(hashTable, "AIT", "Army Institute of technology, Pune.");
    insert(hashTable, "TIA", "Can be name of a girl.");
    insert(hashTable, "apple", "A fruit that is typically red or green.");
    insert(hashTable, "banana", "A long yellow fruit.");
    insert(hashTable, "grape", "A small, round, purple or green fruit.");
    insert(hashTable, "mango", "A tropical fruit with a sweet taste.");

    cout << "Meaning of 'AIT': " << search(hashTable, "AIT") << endl;
    cout << "Meaning of 'apple': " << search(hashTable, "apple") << endl;
    cout << "Meaning of 'grape': " << search(hashTable, "grape") << endl;
    cout << "Meaning of 'orange': " << search(hashTable, "orange") << endl;

    cout << "\nDictionary Contents:" << endl;
    display(hashTable);

    deleteWord(hashTable, "banana");

    cout << "\nDictionary after deletion:" << endl;
    display(hashTable);

    return 0;
}
