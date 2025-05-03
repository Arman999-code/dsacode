#include<iostream>
using namespace std;
struct Node{
    int data;
    Node* left;
    Node* right;
    Node(int val){
        data=val;
        left=right=nullptr;

    }
};

Node* insert(Node* root,int val){
    if(root==nullptr){
        return new Node(val);
    }
    if(val<root->data){
        root->left=insert(root->left,val);

    }else if(val>root->data){
        root->right=insert(root->right,val);
    }
    return root;
}

bool search(Node* root,int key){
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

Node* findMin(Node* root){
    while(root && root->left){
        root=root->left;
    }
    return root;
};

Node* deleteNode(Node* root,int key){
    if(root==nullptr){
        return root;

    }
    if(key<root->data){
        root->left=deleteNode(root->left,key);
    }
    else if(key>root->data){
        root->right=deleteNode(root->right,key);
    }
    else{
        if(!root->left){
            Node*temp=root->right;
            delete root;
            return temp;
        }
        else if(!root->right){
            Node* temp= root->left;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
};

int main(){
    Node* root=nullptr;
    int choice,value;
    do{
        cout<<"Enter your choice"<<"\n";
        cout<<"1. insert"<<"\n";
        cout<<"2. Search"<<"\n";
        cout<<"3. Delete"<<"\n";
        cout<<"4. Exit"<<"\n";
        cin>>choice;

        switch(choice){
            case 1:
                cout<<"Enter the value to insert:";
                cin>>value;
                root = insert(root,value);
                cout<<value<<" "<<"Inserted successfully \n";
                break;

            case 2:
                cout<<"Enter the value to search:";
                cin>>value;
                if(search(root,value)){
                    cout<<"the value is found:"<<value<<"\n";
                }
                else{
                    cout<<"The value is not found:"<<value<<"\n";
                }
                break;

            case 3:
                cout<<"enter the value to delete:";
                cin>>value;
                root=deleteNode(root,value);
                cout<<"The value is Deleted successfully (if exists):"<<value<<"\n";
                break;

            case 4:
                cout<<"Exiting\n";
                break;
            default:
                cout<<"Invalid choice";
            

        }

    }
    while(choice!=4);
    return 0;
}