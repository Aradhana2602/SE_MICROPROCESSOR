#include <bits/stdc++.h>
using namespace std;

void insertion(int v, int arr[]) {
    int val = v%10;  
    int i = 0;
    while(i < 10) {
        int change = (val + i * i) % 10;  
        if (arr[change] == -1) {  
            arr[change] = v;
            cout << "Successfully inserted the value "<< endl;
            return;
        }
        i++;
    }
    cout<<"Table is full"<<endl;  
}

void display(int arr[]) {
    for(int i=0;i<10;i++){
        cout<<"For i="<<i<<" value is: "<<arr[i]<<endl;
    }
}


double calculate(int arr[]) {
    int count = 0;
    for(int i=0;i<10;i++) {
        if(arr[i] != -1 && arr[i] != -2){
            count++;
        }
    }
    return (double)count;
}

void deletion(int n, int arr[]) {
    int comp=0;
    int val=n%10;
    int i=0;
    while(i<10) {
        comp++;
        int change = (val+i*i)%10;
        if(arr[change]==n){  
            arr[change]=-2;  
            cout<<"Successfully deleted the value "<<endl;
            cout<<"No. of comparisons are: "<<comp<<endl;
            return;
        }
        if(arr[change]==-1){  
            cout << "Value not found" << endl;
            cout << "No. of comparisons are: " << comp << endl;
            return;
        }
        i++;
    }
    cout<<"Value not found"<<endl;
}

void search(int n, int arr[]) {
    int comp=0;
    int val=n%10;
    int i = 0;
    while (i < 10) {
        comp++;
        int change = (val+i*i)%10;
        if(arr[change]==n) {  
            cout<<"Value found at location: "<<change<<endl;
            cout<<"No. of comparisons are: "<<comp<<endl;
            return;
        }else if(arr[change]==-1){  
            cout<<"Value is not present in table"<<endl;
            cout<<"No. of comparisons are: "<< comp<<endl;
            return;
        }
        i++;
    }
    cout<<"Value is not present in table"<<endl;
}

int main(){
    int arr[10];
    for(int i=0;i<10;i++){
        arr[i]=-1;
    }

    int menu;

    while (menu != 6) {
        cout << "Enter your choice (1->Insert  2->Display  3->Deletion  4->Search  5->Load factor 6->Exit): ";
        cin >> menu;
        if(menu==1){
            int n;
            cout<<"Enter value you want to enter: ";
            cin>>n;
            insertion(n, arr);
        }else if(menu==2){
            cout<<"Displaying the Hash table" << endl;
            display(arr);
        }else if(menu==3){
            int v;
            cout<<"Enter value you want to delete: ";
            cin>>v;
            deletion(v, arr);
        }else if(menu==4){
            int v;
            cout<<"Enter value you want to search: ";
            cin>>v;
            search(v, arr);
        }else if(menu==5){
            double lf=calculate(arr)/10.0;
            cout<<"Load Factor is: "<<lf<< endl;
        }else if(menu==6){
            cout<<"Successfully exited from program"<< endl;
        }else{
            cout<<"Enter valid option: ";
        }
    }

}



//Quadratic probing

#include <iostream>
#include <vector>
using namespace std;

int hashFunction(int key) {
    return key % 10;
}

void insert(int key, int arr[10][2]) {
    int index = hashFunction(key);
    if (arr[index][0] == -1) {
        arr[index][0] = key;
        cout << "Inserted "<< key <<" successfully" << endl;
    } else {
        int j = index + 1;
        while (j != index) {
            if (arr[j][0] == -1) {
                arr[j][0] = key;
                cout << "Inserted "<<key<<" successfully" << endl;
                if (hashFunction(key) == hashFunction(arr[index][0])) {
                    arr[index][1] = j;
                    cout << "Chain column updated" << endl;
                }
                return;
            }
            j = (j + 1) % 10;
        }
    }
}

int search(int key, int arr[10][2]) {
    int cnt = 0;
    int i = 0;
    int val = key % 10;
    while (i < 10) {
        cnt++;
        if (arr[val][0] == key) {
            cout << key <<"found at index: " << val << endl;
            cout << "Number of comparisons: " << cnt << endl;
            return val;
        } else if (hashFunction(key) == val) {
            if (arr[val][1] == -1) {
                cout <<key << " not found!" << endl;
                return -1;
            } else if (arr[val][0] == -1) {
                cout << key <<" not found!" << endl;
                return -1;
            } else {
                val = arr[val][1];
            }
        } else if (hashFunction(key) != val) {
            int j = val + 1;
            while (j != val) {
                cnt++;
                if (arr[j][0] == key) {
                    cout << key <<" found at index: " << j << endl;
                    cout << "Number of comparisons: " << cnt << endl;
                    return j;
                }
                j = (j + 1) % 10;
            }
        }
        i++;
    }
    return -1;
}

float load_factor(int arr[10][2]) {
    int elements = 0;
    for (int i = 0; i < 10; i++) {
        if (arr[i][0] != -1) {
            elements++;
        }
    }
    return static_cast<float>(elements) / 10;
}

void display(int arr[10][2]) {
    cout << "The hash table is: " << endl;
    for (int i = 0; i < 10; i++) {
        cout << arr[i][0] << " ";
    }
    cout << endl;
}

void delete_key(int key, int arr[10][2]) {
    int index = search(key, arr);
    
    if (index != -1) {
        arr[index][0] = -1;
        arr[index][1] = -1; 
        cout << "Element " << key << " deleted successfully!" << endl;
    } else {
        cout << "Element " << key << " not found in the hash table!" << endl;
    }
}


int main() {
    int arr[10][2];
    for (int i = 0; i < 10; i++) {
        arr[i][0] = -1;
        arr[i][1] = -1;
    }

    insert(25, arr);
    insert(35, arr);
    insert(45, arr);
    display(arr);

    search(35, arr);
    search(50, arr);

    cout << "Load factor: " << load_factor(arr) << endl;

    return 0;
}


//chaining without replacement 


#include <iostream>
#include <vector>
using namespace std;

int hashFunction(int key) {
    return key % 10;
}

void insert(int key, int arr[10][2]) {
    int index = hashFunction(key);
    if (arr[index][0] == -1) {
        arr[index][0] = key;
        cout << "Inserted "<< key <<" successfully" << endl;
    } else {
        int j = index + 1;
        while (j != index) {
            if (arr[j][0] == -1) {
                arr[j][0] = key;
                cout << "Inserted "<<key<<" successfully" << endl;
                if (hashFunction(key) == hashFunction(arr[index][0])) {
                    arr[index][1] = j;
                    cout << "Chain column updated" << endl;
                }
                return;
            }
            j = (j + 1) % 10;
        }
    }
}

int search(int key, int arr[10][2]) {
    int cnt = 0;
    int i = 0;
    int val = key % 10;
    while (i < 10) {
        cnt++;
        if (arr[val][0] == key) {
            cout << key <<"found at index: " << val << endl;
            cout << "Number of comparisons: " << cnt << endl;
            return val;
        } else if (hashFunction(key) == val) {
            if (arr[val][1] == -1) {
                cout <<key << " not found!" << endl;
                return -1;
            } else if (arr[val][0] == -1) {
                cout << key <<" not found!" << endl;
                return -1;
            } else {
                val = arr[val][1];
            }
        } else if (hashFunction(key) != val) {
            int j = val + 1;
            while (j != val) {
                cnt++;
                if (arr[j][0] == key) {
                    cout << key <<" found at index: " << j << endl;
                    cout << "Number of comparisons: " << cnt << endl;
                    return j;
                }
                j = (j + 1) % 10;
            }
        }
        i++;
    }
    return -1;
}

float load_factor(int arr[10][2]) {
    int elements = 0;
    for (int i = 0; i < 10; i++) {
        if (arr[i][0] != -1) {
            elements++;
        }
    }
    return static_cast<float>(elements) / 10;
}

void display(int arr[10][2]) {
    cout << "The hash table is: " << endl;
    for (int i = 0; i < 10; i++) {
        cout << arr[i][0] << " ";
    }
    cout << endl;
}

void delete_key(int key, int arr[10][2]) {
    int index = search(key, arr);
    
    if (index != -1) {
        arr[index][0] = -1;
        arr[index][1] = -1; 
        cout << "Element " << key << " deleted successfully!" << endl;
    } else {
        cout << "Element " << key << " not found in the hash table!" << endl;
    }
}


int main() {
    int arr[10][2];
    for (int i = 0; i < 10; i++) {
        arr[i][0] = -1;
        arr[i][1] = -1;
    }

    insert(25, arr);
    insert(35, arr);
    insert(45, arr);
    display(arr);

    search(35, arr);
    search(50, arr);

    cout << "Load factor: " << load_factor(arr) << endl;

    return 0;
}

//separate chaining

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
