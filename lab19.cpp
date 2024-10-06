// COMSC-210 | lab 19 | Kent Kawashima
// IDE used: Visual Studio Code
#include <iostream>
#include <fstream> // for file input/output
#include <time.h>
#include <cstdlib>
#include <array>
using namespace std;

// struct
struct Node
{
    double rating;
    string comment;
    Node *next; // pointer to next node in LL
};

// class
class Movie
{
public:
    Movie(): ptrHead(nullptr){} //constructor 

    string getTitle() const { return movieTitle; }
    Node getHead() const { return *ptrHead; }

    void setTitle(string t) { movieTitle = t; }
    void setHead(Node *p) { ptrHead = p; }

private:
    string movieTitle; // title
    Node *ptrHead;     // pointer to head of linked list containing reviews
};

// function prototypes
void addHead(Node *&);
void averagePrintAll(Node *);
void assignAll(array<Movie, SIZE> &arrMovies);

// global
const int SIZE = 4; // subject to change

/************************************************
 * Function: Main
 ************************************************/
int main()
{

    srand(time(0)); // seed random

    array<Movie, SIZE> arrMovies = {}; //array declaration

    assignAll(arrMovies); 

    // Node *head = nullptr; 
}

void addHead(Node *&head)
{
    double r = -1;
    string buf;
    bool again;

    Node *temp = new Node;

    while (r < 0 || r > 5)
    {
        cout << "Enter review rating 0-5: ";
        cin >> r;
        if (r < 0 || r > 5)
            cout << "Please enter a valid rating (0-5, decimals okay)\n";
    }
    temp->rating = r;

    cin.ignore(100, '\n'); // clear input before getline
    cout << "Enter review comments: ";
    getline(cin, buf);
    temp->comment = buf;

    // assignment
    temp->next = head; // have new node point where head was pointing
    head = temp;       // have head point to next
}

void averagePrintAll(Node *head)
{
    double avg;
    int i = 0;

    while (head) // while head not nullptr
    {
        cout << "\t> Review #" << i + 1 << ": " << head->rating << ": " << head->comment << '\n'; // i+1 for formatting, starts at 1 in output
        avg += head->rating;
        head = head->next; // go to next element in linked list
        i++;               // increment
    }
    cout << "\t> Average: " << (avg / i) << '\n';
}

void assignAll(array<Movie, SIZE> &arrMovies) //pass by reference to reassign
{
    string buf;

    ifstream in("reviews.txt");
    if (!in.is_open())
        cout << "ERROR OPENING FILE\n";
    else
    {
        //set titles for each object
        for (int i = 0; i < SIZE; i++)
        {
            cout << "Enter a name for the title of movie #" << i << ": ";
            cin >> buf;
            arrMovies[i].setTitle(buf);
        }
    }
}
