// Name:-Arman M Shaikh
// Roll-No:-86
// Div :-B

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Record {
    int id;
    string name;
    int age;
};

void insertRecord(fstream &file, int pos, Record record) {
    file.seekp(pos * sizeof(Record), ios::beg);  // Move to the specified position
    file.write(reinterpret_cast<char*>(&record), sizeof(Record));  // Write the record
    cout << "Record inserted successfully at position " << pos << endl;
}

void deleteRecord(fstream &file, int pos) {
    Record blankRecord = {0, "", 0};  // Create a blank record to delete
    file.seekp(pos * sizeof(Record), ios::beg);  // Move to the specified position
    file.write(reinterpret_cast<char*>(&blankRecord), sizeof(Record));  // Overwrite with blank
    cout << "Record deleted successfully from position " << pos << endl;
}

void displayFileContents(fstream &file) {
    file.seekg(0, ios::beg);  // Move to the beginning of the file
    Record record;
    int position = 0;
    
    while (file.read(reinterpret_cast<char*>(&record), sizeof(Record))) {
        if (record.id != 0) {  // Skip blank records
            cout << "Position " << position << ": ID = " << record.id 
                 << ", Name = " << record.name << ", Age = " << record.age << endl;
        }
        position++;
    }
}

int main() {
    fstream file("records.dat", ios::in | ios::out | ios::binary | ios::trunc);

    if (!file) {
        cout << "File could not be created!" << endl;
        return 1;
    }

    // Insert a few records
    Record r1 = {1, "Arman", 20};
    Record r2 = {2, "Sohan", 20};
    Record r3 = {3, "Atharav",20};
    
    insertRecord(file, 0, r1);
    insertRecord(file, 1, r2);
    insertRecord(file, 2, r3);

    cout << "\nFile contents after insertion:" << endl;
    displayFileContents(file);

    // Delete a record
    deleteRecord(file, 1);  // Deleting Bob's record

    cout << "\nFile contents after deletion:" << endl;
    displayFileContents(file);

    file.close();
    return 0;
}
