#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct Student{
    string name,roll_no,division,address;
};

void addStudent(){
    Student s;
    cout<<"Enter the roll_no:";
    cin>>s.roll_no;
    cin.ignore();

    cout<<"enter the name of student: ";
    getline(cin,s.name);

    cout<<"Enter the Division:";
    getline(cin,s.division);

    cout<<"Enter the address:";
    getline(cin,s.address);

    ofstream outfile("Epic.txt",ios::app);

    if(!outfile){
        cout<<"Error in file opening";
        return;
    }
    outfile<<s.roll_no<<","<<s.name<<","<<s.division<<","<<s.address<<"\n";
    cout<<"Student added Successfully\n ";
}
void deleteStudent(){
    string rollTOdelete;
    bool found=false;

    cout<<"Enter the roll no to delete:";
    cin>>rollTOdelete;

    ifstream infile("Epic.txt");
    ofstream tempfile("temp.txt");
    if(!infile||!tempfile){
        cout<<"Error in opening the file";
        return;
    }
    string line;
    while(getline(infile,line)){
        if(line.substr(0,line.find(','))!=rollTOdelete){
            tempfile<<line<<"\n";
        }else{
            found=true;

        }

    }
    infile.close();
    tempfile.close();

    remove("Epic.txt");
    rename("temp.txt","Epic.txt");
    if(found){
        cout<<"Student delete successfully \n";
    }
    else{
        cout<<"student Not Delete successfully \n";
    }

}
void display(){
    string rollTosearch;
    bool found=false;


    cout<<"Enter the roll to search:";
    cin>>rollTosearch;
    ifstream infile("Epic.txt");
    if(!infile){
        cout<<"Error in opening the file";
        return;
    }
    string line;
    while(getline(infile,line)){
        if(line.substr(0,line.find(',')) == rollTosearch){
            found=true;
            size_t pos1=line.find(',');
            size_t pos2=line.find(',', pos1 + 1);
            size_t pos3=line.find(',', pos2 + 1);
            cout<<"\n student found successfully \n";
            cout<<"Roll_no:"<<line.substr(0,pos1)<<"\n";
            cout<<"Name:"<<line.substr(pos1 + 1,pos2 - pos1 -1)<<"\n";
            cout<<"Division:"<<line.substr(pos2 + 1,pos3 - pos2 -1)<<"\n";
            cout<<"Address:"<<line.substr(pos3 + 1)<<"\n";
            break;
        }
       
    }
    infile.close();
    if(!found){
        cout<<"Student record not found \n";
    }
}

int main(){
    int choice;
    do{
        cout<<"----------student details--------------"<<endl;
        cout<<"1.Add student"<<endl;
        cout<<"2.delete Student"<<endl;
        cout<<"3.Display"<<endl;
        cout<<"4.Exit"<<endl;
        cin>>choice;

        switch(choice){
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                display();
            break;
            case 4:
                cout<<"Exiting";
                break;
            default:
                cout<<"Innvalid condition";
        }
    }while(choice!=4);
    // addStudent();
    return 0;
}