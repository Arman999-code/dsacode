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
int key;
bool Search(Node*root){
    if(root==nullptr){
        return false;
    }
    if(root->data=key){
        return true;

    }
    if(key<root->data){
        return Search(root->left);
    }
    if(key > root->data){
        return Search(root->right);
    }
};
int main(){
    Node*root=new Node(50);
    root->left= new Node(30);
    root->right = new Node(70);
    root->left->left= new Node(20);
    root->left->right= new Node(40);
    root->right->left= new Node(60);
    root->right->right= new Node(80);
    cout<<"Enter the key to find:";
    cin>>key;
    // Search(root);
    // cout<<"key is found:"<<key<<endl;
    if(Search(root)){
        cout<<"key is not found";
    }
    else{
        cout<<"key is found";
    }
    // if(Search(root)){
    //     cout<<"Key is found:"<< key <<endl;
    // }
    // else{
    //     cout<<"Key is not found:"<< key <<endl;
    // }
    return 0;
}
