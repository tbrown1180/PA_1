#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

static const int MAX_SPACES = 40;

// -------------------------------
// Data class (NOT a struct)
// -------------------------------
class MonopolySpace {
public:
    string propertyName;
    string propertyColor;
    int value;
    int rent;

    //rewrote constructor into this format (2/25)
    //constructor
    MonopolySpace() : propertyName (""),  propertyColor (""), value (0),  rent (0){
    }
    //defined the overloaded constructor (2/25)
    //overloaded constructor
    MonopolySpace(string propertyName, string propertyColor, int value, int rent) : propertyName(propertyName), propertyColor(propertyColor), value(value), rent(rent) {
    }
    bool isEqual(MonopolySpace other) {
        /* TODO: Define isEqual here (compare by name is fine if you enforce uniqueness) */
        // wrote if statemen to check the properties of another space (2/25)
        //checks if all are equal to another
        if (propertyName == other.propertyName && propertyColor == other.propertyColor && value == other.value && rent == other.rent) {
            return true;
        }
        return false;
    }
    void print() {
        /* TODO: Define print here */
        // Example style
        // (2/27) uncommented the cout for the print
        cout << propertyName << " | " << propertyColor << " | $" << value << " | Rent " << rent;
        }
};

// -------------------------------
// Template Node class (NOT a struct)
// -------------------------------
template <typename T>
class Node {
public:
T data;
Node<T>* nextNode;
Node(T value) {
data = value;
nextNode = nullptr;
}
};
// -------------------------------
// Template Circular Linked List class
// Spring 2026 version: traversable board
// -------------------------------
template <typename T>
class CircularLinkedList {
private:
Node<T>* headNode;
Node<T>* tailNode;
// player cursor for traversal-based gameplay
Node<T>* playerNode;
int nodeCount;
int passGoCount;
public:
CircularLinkedList() {
headNode = nullptr;
tailNode = nullptr;
playerNode = nullptr;
nodeCount = 0;
passGoCount = 0;
}
// -------------------------------
// Board Construction Policy (Reminder)
// -------------------------------
// Spaces are added during board construction BEFORE gameplay.
// You choose how to construct the board:
// - hardcode spaces, read from file, or generate programmatically
// The only non-negotiable requirement:
// - enforce MAX_SPACES
// - maintain circular integrity
// -------------------------------
// -------------------------------
// Core A: Add a Space with Capacity Enforcement
// -------------------------------
bool addSpace(T value) {
// TODO:
// - If nodeCount == MAX_SPACES return false (do not corrupt list)
// - Create new node
// - If empty list: head=tail=player=new, new->next=head
// - Else: tail->next=new, tail=new, tail->next=head
// - nodeCount++

    //(2/27) did all the to do above to check max spaces and if the list is empty
    //checks node count
    if (nodeCount == MAX_SPACES) {
        return false;
    }

    //creates new node
    Node<T> *newNode = new Node<T>(value);

    // if the list is empty sets new node to head tail and player
    if (nodeCount == 0) {
        headNode = newNode;
        tailNode = newNode;
        playerNode = newNode;

        //points back to head to make circular
        newNode->nextNode = headNode;
    }
    //else tail will point back to head to make list circular
    else {
        tailNode->nextNode = newNode;
        tailNode = newNode;
        tailNode->nextNode = headNode;
    }
    nodeCount++;
    return true;  //(2/28) forgot to return true when it executes properly

}
// -------------------------------
// Core B: Add Multiple Spaces at Once
// -------------------------------

// (2/28) worked on core B to add multiple spaces
// (2/28) couldn't get multiple spaces to be added will try and fix tomorrow
// (3/6) added an added integer to count how many spaces where added and changed my loop to call addSpace since the logic was already there
// (3/7) simplified my for loop to just check max spaces
int addMany(vector<T> values) {

    int added = 0;

    for (int i = 0; i < MAX_SPACES; i++) {

        //gets whatever i is equal to from the vector then calls addSpace to add a space at that spot
        if (addSpace(values[i])) {
            added++;
        }
    }

    cout <<"Spaces add: "<< added << endl;
    return added;

    // TODO:
    // - Add sequentially until full
    // - Stop exactly when you reach MAX_SPACES
    // - Return number successfully added
    // - Do not corrupt pointers if capacity is exceeded
    //cout << "addMany unwritten" << endl;
}
// -------------------------------
// Core C: Traversal-Based Player Movement
// -------------------------------

// (2/28) worked on core C to move player and check passing go
// (2/28) passing go works for now while only one node in list
void movePlayer(int steps) {

    //checks if board is empty and if it is it exits the function using return
    if (playerNode == nullptr || nodeCount == 0) {
        return;
    }

    for (int i = 0; i < steps; i++) {
        //for each iteration it checks if player is about to pass go
        //player = tail because it checks when its about to go back to the head node
        if (playerNode == tailNode) {
            passGoCount++;
        }

        //moving player node forward one
        playerNode = playerNode->nextNode;
    }

// TODO:
// - Move playerNode forward 'steps' times, node-by-node
// - Wrap naturally because list is circular
// - Detect and track passing GO:
// increment passGoCount when a move crosses from tail back to head
// - Must handle empty list safely
//cout << "movePlayer unwritten" << endl;
}
int getPassGoCount() {
return passGoCount;
}
// -------------------------------
// Core D: Controlled Board Display
// ------------------------------

//(3/6) got data of player node to print
void printFromPlayer(int count) {
// TODO:
// - Print exactly 'count' nodes starting from playerNode
// - Must not infinite loop
// - Must handle empty list
// - Output must be deterministic and readable
//cout << "printFromPlayer unwritten" << endl;

    //sets current to where the player node is
    Node<T> *current = playerNode;


    for (int i = 0; i < count; i++) {
        current->data.print();   //prints the data of the node the player is on
        cout << endl;

        //moves to the next node
        current = current->nextNode;
    }
}
// Optional helper: print full board once (one full cycle)

//(3/6)got the print to work showing the whole board
void printBoardOnce() {
// TODO:
// - Traverse exactly one full cycle and print each node
//cout << "printBoardOnce unwritten" << endl;

    //sets current to head
    Node<T> *current = headNode;

    do {
        current->data.print();  //prints the space of current node
        cout << endl;

        current = current->nextNode;  //moves to the next node
    }
    while (current != headNode);  //loops while current isn't on the head node
}
// -------------------------------
// Advanced Option A (Level 1): removeByName
// -------------------------------
bool removeByName(string name) {
// TODO:
// - Delete FIRST matching node
// - Must handle:
// - deleting head
// - deleting tail
// - deleting the only-node list
// - Maintain circular link tail->next=head
// - If playerNode points to deleted node, move playerNode to a safe node
// - nodeCount--
cout << "removeByName unwritten" << endl;
return false;
}
// -------------------------------
// Advanced Option A (Level 1): findByColor
// -------------------------------
vector<string> findByColor(string color) {
// TODO:
// - Traverse ring exactly once
// - Collect matching names in vector<string>
// - Return matches
cout << "findByColor unwritten" << endl;
vector<string> matches;
return matches;
}
// -------------------------------
// Advanced Option B (Level 2): Mirror the Board (Circular Reversal)
// -------------------------------

// (3/7) worked on mirroring the board for my advanced option
void mirrorBoard() {
// TODO:
// - Reverse the direction of the circular list by reversing next pointers
// - Preserve circular structure
// - Correctly handle empty list and single-node list
// - Player cursor must remain on the same logical space after reversal

    //handles empty and single node list
    if (headNode == nullptr || headNode->nextNode == headNode) {
        return;
    }

    Node<T> *previous = headNode;      // previous points to the node before the current node
    Node<T> *current = headNode->nextNode;   // current is the node being processed at that time
    Node<T> *temp;      // used as temp storage to save where the node originally pointed to

    while (current != headNode) {
        temp = current->nextNode;       // saves the next node
        current->nextNode = previous;   // reverses the pointer to the node before
        previous = current;             // moves previous to the next node
        current = temp;                 // moves current to the next node
    }

    current->nextNode = previous;
    headNode = previous;        // makes the last node the head

cout <<endl<< "Advanced Option B: mirrorBoard" << endl;
}
// -------------------------------
// Edge-case helper: countSpaces O(n)
// -------------------------------
// (3/8) worked on counting spaces without using node count
int countSpaces() {
// TODO:
// - Must be O(n), traverse exactly once with correct stop condition
// - Do NOT rely on nodeCount for this method
//cout << "countSpaces unwritten" << endl;

    if (headNode == nullptr) {
        return 0;
    }

    int count = 0;
    Node<T> *current = headNode;

    //increases count as current moves through the list
    do {
        count++;
        current = current->nextNode;
    }
    while (current != headNode);

    cout << endl << "The O(n) count: " << count << endl;

    return count;
}
// -------------------------------
// Cleanup
// -------------------------------

// (3/8) worked on deleting all nodes from the list
void clear() {
// TODO:
// - Safely delete all nodes
// - Tip: if tailNode exists, break the cycle first: tailNode->nextNode =nullptr
// - Then delete like a normal singly linked list
//cout << "clear unwritten" << endl;


    if (nodeCount == 0) {
        return;
    }

    tailNode->nextNode = nullptr;   // breaks the loop making it a singly linked list
    Node<T> *temp = headNode;

    while (nodeCount != 0) {
        headNode = headNode->nextNode;      // moves the head to the next node
        delete temp;                        // deletes temp
        temp = headNode;                    // temp becomes new head node
        nodeCount--;                        // makes node count smaller
    }

    headNode = nullptr;     // set to null so it doesn't point to deleted memory
    tailNode = nullptr;
   nodeCount = 0;
}
};
// -------------------------------
// Main: playable loop demo
// -------------------------------
int rollDice2to12() {
return (rand() % 6 + 1) + (rand() % 6 + 1);
}


int main() {
srand(static_cast<unsigned>(time(nullptr)));
CircularLinkedList<MonopolySpace> board;
// -------------------------------
// Board Construction Phase
// -------------------------------
// You decide how to build the board:
// - hardcode spaces, load from file, or generate spaces programmatically
// The only requirement: never exceed MAX_SPACES and keep the list circular.
//
// Example (hardcoded) usage:
vector<MonopolySpace> spaces;
spaces.push_back(MonopolySpace("GO","None",0,0));

// (3/6) hard coded new spaces and looked up all the space names to do so
// Brown
spaces.push_back(MonopolySpace("Mediterranean Ave","Brown",60,2));
spaces.push_back(MonopolySpace("Baltic Ave","Brown",60,4));

// Light Blue
spaces.push_back(MonopolySpace("Oriental Ave","Light Blue",100,6));
spaces.push_back(MonopolySpace("Vermont Ave","Light Blue",100,6));
spaces.push_back(MonopolySpace("Connecticut Ave","Light Blue",120,8));

// Pink
spaces.push_back(MonopolySpace("St. Charles Place","Pink",140,10));
spaces.push_back(MonopolySpace("States Ave","Pink",140,10));
spaces.push_back(MonopolySpace("Virginia Ave","Pink",160,12));

// Railroads
spaces.push_back(MonopolySpace("Reading Railroad","Railroad",200,25));
spaces.push_back(MonopolySpace("Pennsylvania Railroad","Railroad",200,25));
spaces.push_back(MonopolySpace("B. & O. Railroad","Railroad",200,25));
spaces.push_back(MonopolySpace("Short Line","Railroad",200,25));

// Orange
spaces.push_back(MonopolySpace("St. James Place","Orange",180,14));
spaces.push_back(MonopolySpace("Tennessee Ave","Orange",180,14));
spaces.push_back(MonopolySpace("New York Ave","Orange",200,16));

// Red
spaces.push_back(MonopolySpace("Kentucky Ave","Red",220,18));
spaces.push_back(MonopolySpace("Indiana Ave","Red",220,18));
spaces.push_back(MonopolySpace("Illinois Ave","Red",240,20));

// Yellow
spaces.push_back(MonopolySpace("Atlantic Ave","Yellow",260,22));
spaces.push_back(MonopolySpace("Ventnor Ave","Yellow",260,22));
spaces.push_back(MonopolySpace("Marvin Gardens","Yellow",280,24));

// Green
spaces.push_back(MonopolySpace("Pacific Ave","Green",300,26));
spaces.push_back(MonopolySpace("North Carolina Ave","Green",300,26));
spaces.push_back(MonopolySpace("Pennsylvania Ave","Green",320,28));

// Dark Blue
spaces.push_back(MonopolySpace("Park Place","Dark Blue",350,35));
spaces.push_back(MonopolySpace("Boardwalk","Dark Blue",400,50));

// Utilities
spaces.push_back(MonopolySpace("Electric Company","Utility",150,0));
spaces.push_back(MonopolySpace("Water Works","Utility",150,0));

// Chance / Community Chest / Taxes
spaces.push_back(MonopolySpace("Community Chest 1","None",0,0));
spaces.push_back(MonopolySpace("Community Chest 2","None",0,0));
spaces.push_back(MonopolySpace("Community Chest 3","None",0,0));
spaces.push_back(MonopolySpace("Chance 1","None",0,0));
spaces.push_back(MonopolySpace("Chance 2","None",0,0));
spaces.push_back(MonopolySpace("Chance 3","None",0,0));
spaces.push_back(MonopolySpace("Income Tax","None",200,0));
spaces.push_back(MonopolySpace("Luxury Tax","None",100,0));

//Jail / Free Parking / Go To Jail
spaces.push_back(MonopolySpace("Jail","None",0,0));
spaces.push_back(MonopolySpace("Free Parking","None",0,0));
spaces.push_back(MonopolySpace("Go To Jail","None",0,0));

board.addMany(spaces);
// NOTE: This starter calls addSpace once to show the intended API,
// but your final submission should build a meaningful board.
board.addSpace(MonopolySpace("GO", "None", 0, 0));
//(3/6) added a call to print board
board.printBoardOnce();
// -------------------------------
// Playable Traversal Loop
// -------------------------------
for (int turn = 1; turn <= 10; turn++) {
int roll = rollDice2to12();
cout << "\nTurn " << turn << " | Rolled: " << roll << endl;
board.movePlayer(roll);
cout << "Board view from player (next 5 spaces):" << endl;
board.printFromPlayer(5);
cout << "Times passed GO so far: " << board.getPassGoCount() << endl;
}
// -------------------------------
// Advanced Feature Demos (students choose path)
// -------------------------------
// Option A examples:
// board.removeByName("Baltic Avenue");
// vector<string> brownProps = board.findByColor("Brown");
//

board.countSpaces();        // calls countSpaces
// Option B example:
board.mirrorBoard();
board.printBoardOnce();     // called print board again to print the reversed board after pointers are reversed

board.clear();              // calls clear
board.printBoardOnce();     // called this again just to make sure nothing prints
return 0;
}