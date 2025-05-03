// Name:-Arman M Shaikh
// Roll-no:-86
// Div:-B

#include <iostream>
#include <vector>
#include <queue>  // for priority_queue

using namespace std;

int main() {
    int n;
    
    // Step 1: Take input for number of students
    cout << "Enter number of students: ";
    cin >> n;

    vector<int> marks(n);
    
    cout << "Enter marks of " << n << " students:\n";
    
    // Step 2: Read marks from user
    for(int i = 0; i < n; i++) {
        cout << "Student " << i + 1 << ": ";
        cin >> marks[i];
    }

    // Step 3: Create max heap for finding maximum marks
    priority_queue<int> maxHeap;

    // Step 4: Create min heap for finding minimum marks using greater<int>
    priority_queue<int, vector<int>, greater<int>> minHeap;

    // Step 5: Insert all marks into both heaps
    for(int i = 0; i < n; i++) {
        maxHeap.push(marks[i]); // for maximum
        minHeap.push(marks[i]); // for minimum
    }

    // Step 6: Top of max heap is maximum, top of min heap is minimum
    int maxMarks = maxHeap.top();
    int minMarks = minHeap.top();

    // Step 7: Display the result
    cout << "\nMaximum Marks: " << maxMarks << endl;
    cout << "Minimum Marks: " << minMarks << endl;

    return 0;
}
