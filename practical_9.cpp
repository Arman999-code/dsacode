#include <iostream>
#include <string>
using namespace std;

struct Node {
    string keyword, meaning;
    Node *left = NULL, *right = NULL;
    int height = 1;
    Node(string k, string m) : keyword(k), meaning(m) {}
};

int height(Node* n) { return n ? n->height : 0; }
int balance(Node* n) { return n ? height(n->left) - height(n->right) : 0; }

Node* rightRotate(Node* y) {
    Node *x = y->left, *T2 = x->right;
    x->right = y; y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node* leftRotate(Node* x) {
    Node *y = x->right, *T2 = y->left;
    y->left = x; x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

Node* insert(Node* root, string key, string val) {
    if (!root) return new Node(key, val);
    if (key < root->keyword) root->left = insert(root->left, key, val);
    else if (key > root->keyword) root->right = insert(root->right, key, val);
    else return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int b = balance(root);

    if (b > 1 && key < root->left->keyword) return rightRotate(root);
    if (b < -1 && key > root->right->keyword) return leftRotate(root);
    if (b > 1 && key > root->left->keyword) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (b < -1 && key < root->right->keyword) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inOrder(Node* r) {
    if (!r) return;
    inOrder(r->left);
    cout << r->keyword << " : " << r->meaning << '\n';
    inOrder(r->right);
}

void reverseOrder(Node* r) {
    if (!r) return;
    reverseOrder(r->right);
    cout << r->keyword << " : " << r->meaning << '\n';
    reverseOrder(r->left);
}

bool search(Node* r, string key, int& count) {
    if (!r) return false;
    count++;
    if (key == r->keyword) return true;
    return key < r->keyword ? search(r->left, key, count) : search(r->right, key, count);
}

void update(Node* r, string key, string newMeaning) {
    if (!r) return;
    if (key == r->keyword) r->meaning = newMeaning;
    else if (key < r->keyword) update(r->left, key, newMeaning);
    else update(r->right, key, newMeaning);
}

Node* minNode(Node* n) {
    while (n->left) n = n->left;
    return n;
}

Node* deleteNode(Node* root, string key) {
    if (!root) return root;
    if (key < root->keyword) root->left = deleteNode(root->left, key);
    else if (key > root->keyword) root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        } else {
            Node* temp = minNode(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->keyword);
        }
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int b = balance(root);

    if (b > 1 && balance(root->left) >= 0) return rightRotate(root);
    if (b > 1 && balance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (b < -1 && balance(root->right) <= 0) return leftRotate(root);
    if (b < -1 && balance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int main() {
    Node* root = NULL;
    int ch;
    string key, val;

    while (true) {
        cout << "\n[1]Add [2]Del [3]Upd [4]Asc [5]Desc [6]Find [7]Exit: ";
        cin >> ch;
        if (ch == 1) {
            cout << "Keyword Meaning: ";
            cin >> key >> val;
            root = insert(root, key, val);
        } else if (ch == 2) {
            cout << "Keyword to delete: ";
            cin >> key;
            root = deleteNode(root, key);
        } else if (ch == 3) {
            cout << "Keyword NewMeaning: ";
            cin >> key >> val;
            update(root, key, val);
        } else if (ch == 4) {
            inOrder(root);
        } else if (ch == 5) {
            reverseOrder(root);
        } else if (ch == 6) {
            int cmp = 0;
            cout << "Keyword to find: ";
            cin >> key;
            if (search(root, key, cmp))
                cout << "Found in " << cmp << " comparisons.\n";
            else
                cout << "Not found. Comparisons: " << cmp << '\n';
        } else if (ch == 7) break;
    }
    return 0;
}
