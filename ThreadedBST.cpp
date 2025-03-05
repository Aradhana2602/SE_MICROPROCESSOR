#include <iostream>
using namespace std;

// Node structure for Threaded Binary Search Tree
struct Node {
    int data;
    Node *left, *right;
    bool isThreaded; // True if right pointer is a thread

    Node(int value) {
        data = value;
        left = right = nullptr;
        isThreaded = false;
    }
};

// Class for Threaded Binary Search Tree
class ThreadedBST {
private:
    Node* root;

    // Insert a new node into BST
    Node* insertBST(Node* root, int key) {
        if (!root) return new Node(key);
        if (key < root->data) 
            root->left = insertBST(root->left, key);
        else 
            root->right = insertBST(root->right, key);
        return root;
    }

    // Convert BST to Inorder Threaded BST
    void convertToThreaded(Node* root, Node*& prev) {
        if (!root) return;

        // Recursively process left subtree
        convertToThreaded(root->left, prev);

        // Process current node
        if (prev && !prev->right) {
            prev->right = root;
            prev->isThreaded = true;
        }
        prev = root;

        // Recursively process right subtree
        convertToThreaded(root->right, prev);
    }

    // Inorder traversal of Threaded BST
    void inorderTraversal(Node* root) {
        if (!root) return;

        // Move to leftmost node
        Node* current = root;
        while (current->left) 
            current = current->left;

        // Traverse using threads
        while (current) {
            cout << current->data << " ";
            if (current->isThreaded)
                current = current->right; // Move via thread
            else {
                current = current->right;
                while (current && current->left)
                    current = current->left;
            }
        }
        cout << endl;
    }

    // Preorder traversal of Threaded BST
    void preorderTraversal(Node* root) {
        if (!root) return;

        Node* current = root;
        while (current) {
            cout << current->data << " ";

            if (current->left) 
                current = current->left; // Move to left child
            else if (current->isThreaded)
                current = current->right; // Move via thread
            else {
                current = current->right;
                while (current && current->left)
                    current = current->left;
            }
        }
        cout << endl;
    }

public:
    ThreadedBST() { root = nullptr; }

    // Insert a new node
    void insert(int key) { root = insertBST(root, key); }

    // Convert BST into Threaded BST
    void convertToThreaded() {
        Node* prev = nullptr;
        convertToThreaded(root, prev);
    }

    // Inorder Traversal
    void inorder() { inorderTraversal(root); }

    // Preorder Traversal
    void preorder() { preorderTraversal(root); }
};

// Driver Code
int main() {
    ThreadedBST tbst;
    int n, value;

    cout << "Enter the number of nodes in the tree: ";
    cin >> n;

    cout << "Enter the node values: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        tbst.insert(value);
    }

    // Convert to Threaded BST
    tbst.convertToThreaded();

    cout << "\nInorder Traversal: ";
    tbst.inorder();

    cout << "Preorder Traversal: ";
    tbst.preorder();

    return 0;
}
