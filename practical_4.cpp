#include<iostream>
using namespace std;
struct Node{
    int data;
    Node*left;
    Node*right;
    Node(int val){
        data=val;
        right=nullptr;
        left=nullptr;

    }
};
Node* insert(Node*root,int val){
    if(root=nullptr){
        return new Node(val);
    }
    if(val<root->data){
        root->left=insert(root->left,val);

    }
    else if(val>root->data){
        root->right=insert(root->right,val);
    }
    return root;
}

bool search(Node*root,int key){
    if(!root){
        return false;
    }
    if(key==root->data){
        return true;
    }
    else if(key<root->data){
        return search(root->left,key);
    }
    else if(key>root->data){
        return search(root->right,key);
    }

};
Node* findMin(Node* root) {
    while (root && root->left)
        root = root->left;
    return root;
}


Node* deleteNode(Node*root,int key){
    if(root==nullptr){
        return root;
    }
    if(key<root->data){
        root->left=deleteNode(root->left,key);
    }
    else if(key>root->data){
        root->right=deleteNode(root->right,key);
    }

    else {
        // Node with one or no child
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

// Main function to demonstrate operations
int main() {
Node* root = nullptr;
int choice, value;

do {
    cout << "\nBinary Tree Operations:\n";
    cout << "1. Insert\n2. Search\n3. Delete\n4. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "Enter value to insert: ";
        cin >> value;
        root = insert(root, value);
        cout << value << " inserted.\n";
        break;
    case 2:
        cout << "Enter value to search: ";
        cin >> value;
        if (search(root, value))
            cout << value << " found in the tree.\n";
        else
            cout << value << " not found.\n";
        break;
    case 3:
        cout << "Enter value to delete: ";
        cin >> value;
        root = deleteNode(root, value);
        cout << value << " deleted (if it existed).\n";
        break;
    case 4:
        cout << "Exiting.\n";
        break;
    default:
        cout << "Invalid choice.\n";
    }

} while (choice != 4);

return 0;
}