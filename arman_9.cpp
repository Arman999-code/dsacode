// Name:-arman M Shaikh
// Roll-No:-86
// Div:-B
#include <iostream>
#include <string>
using namespace std;

// Node for AVL Tree
struct Node {
    string keyword, meaning;
    Node *left, *right;
    int height;
    Node(string key, string val) {
        keyword = key;
        meaning = val;
        left = right = NULL;
        height = 1;
    }
};

// Get height of the node
int height(Node* root) {
    return root ? root->height : 0;
}

// Get balance factor of the node
int getBalance(Node* root) {
    return root ? height(root->left) - height(root->right) : 0;
}

// Right rotate to balance the tree
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

// Left rotate to balance the tree
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

// Insert node into AVL Tree
Node* insert(Node* root, string key, string val) {
    if (!root) return new Node(key, val);
    if (key < root->keyword)
        root->left = insert(root->left, key, val);
    else if (key > root->keyword)
        root->right = insert(root->right, key, val);
    else return root; // duplicate not allowed

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // Left heavy situation
    if (balance > 1 && key < root->left->keyword)
        return rightRotate(root);

    // Right heavy situation
    if (balance < -1 && key > root->right->keyword)
        return leftRotate(root);

    // Left-right situation
    if (balance > 1 && key > root->left->keyword) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right-left situation
    if (balance < -1 && key < root->right->keyword) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// In-order traversal for Ascending order
void inOrder(Node* root) {
    if (!root) return;
    inOrder(root->left);
    cout << root->keyword << " : " << root->meaning << endl;
    inOrder(root->right);
}

// Reverse in-order traversal for Descending order
void reverseInOrder(Node* root) {
    if (!root) return;
    reverseInOrder(root->right);
    cout << root->keyword << " : " << root->meaning << endl;
    reverseInOrder(root->left);
}

// Search with comparison count
bool search(Node* root, string key, int& count) {
    if (!root) return false;
    count++;
    if (key == root->keyword)
        return true;
    else if (key < root->keyword)
        return search(root->left, key, count);
    else
        return search(root->right, key, count);
}

// Update meaning of a keyword
void update(Node* root, string key, string newMeaning) {
    if (!root) return;
    if (key == root->keyword)
        root->meaning = newMeaning;
    else if (key < root->keyword)
        update(root->left, key, newMeaning);
    else
        update(root->right, key, newMeaning);
}

// Find minimum node for deletion
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left) current = current->left;
    return current;
}

// Delete node
Node* deleteNode(Node* root, string key) {
    if (!root) return root;
    if (key < root->keyword)
        root->left = deleteNode(root->left, key);
    else if (key > root->keyword)
        root->right = deleteNode(root->right, key);
    else {
        // Node has only one child or no child
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            delete temp;
        } else {
            // Node with two children
            Node* temp = minValueNode(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->keyword);
        }
    }

    if (!root) return root;

    // Update height and balance the tree
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Balance the tree after deletion
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

// Main function with menu-driven interface
int main() {
    Node* root = NULL;
    int choice;
    string key, meaning;
    do {
        cout << "\n1.Insert 2.Delete 3.Update 4.Display Asc 5.Display Desc 6.Search 7.Exit\n";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter keyword and meaning: ";
                cin >> key >> meaning;
                root = insert(root, key, meaning);
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                cin >> key;
                root = deleteNode(root, key);
                break;
            case 3:
                cout << "Enter keyword to update and new meaning: ";
                cin >> key >> meaning;
                update(root, key, meaning);
                break;
            case 4:
                inOrder(root);
                break;
            case 5:
                reverseInOrder(root);
                break;
            case 6: {
                int comparisons = 0;
                cout << "Enter keyword to search: ";
                cin >> key;
                if (search(root, key, comparisons))
                    cout << "Found in " << comparisons << " comparisons.\n";
                else
                    cout << "Not found. Comparisons made: " << comparisons << "\n";
                break;
            }
        }
    } while (choice != 7);
    return 0;
}
