#include<iostream>
using namespace std;
struct Node{
    int data;
    Node*left;
    Node*right;
    Node(int val){
        data=val;
        left=right=nullptr;
    }
};
void preorder(Node*root){
    if(root==nullptr){
        return;
    }
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
};

void inorder(Node*root){
    if(root==nullptr){
        return;
    }
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
};

void postorder(Node*root){
    if(root==nullptr){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";

};

int main(){
    Node*root= new Node(50);
    root->left= new Node(30);
    root->right = new Node(70);
    root->left->left= new Node(20);
    root->left->right= new Node(40);
    root->right->left= new Node(60);
    root->right->right= new Node(80);

    cout<<"Inorder Traversal:";
    inorder(root);
    cout<<endl;

    cout<<"Preorder Traversal:";
    preorder(root);
    cout<<endl;

    cout<<"Postorder Traversal:";
    postorder(root);
    cout<<endl;

    return 0;


}