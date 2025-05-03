#include<iostream>
using namespace std;
struct Node{
    int data;
    Node* left;
    Node* right;
    bool rightThread;
    Node(int val){
        data =val;
        left=right=nullptr;
        rightThread=false;
    }


};

Node* insert(Node* root, int key){
    Node* newNode= new Node(key);
    if(!root){
        return newNode;
    }
    Node* parent=nullptr;
    Node* curr= root;

    while(curr){
        parent=curr;
        if(key<curr->data){
            if(!curr->left)break;
            
            curr=curr->left; 
        }
        else{
            if(curr->rightThread) break;
            if(!curr->right) break;
            curr=curr->right;
        }
    }
    if(key<parent->data){
        parent->left=newNode;
        newNode->right=parent;
        newNode ->rightThread=true;
    }else{
        newNode->right=parent->right;
        newNode->rightThread=true;
        parent->right=newNode;
        parent->rightThread=false;
    }
    return root;
}

Node* leftmost(Node* node){
    while(node &&node->left){
        node=node->left;
    }
    return node;

}
void inorder(Node* root){
    Node* curr=leftmost(root);
    while(curr){
        cout<<curr->data<<" ";
        if(curr->rightThread){
            curr=curr->right;

        }
        else{
            curr=leftmost(curr->right);
        }
        
    }
    cout<<endl;
}
int main(){
    Node* root=nullptr;
    root=insert(root,20);
    root=insert(root,10);
    root=insert(root,30);
    root=insert(root,5);
    root=insert(root,15);
    root=insert(root,25);
    root=insert(root,35);
    cout<<"Inorder Traversal:";

    inorder(root);

    return 0;
}