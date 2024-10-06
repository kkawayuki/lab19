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
    Movie() : ptrHead(nullptr) {} // constructor

    string getTitle() const { return movieTitle; }
    Node *getHead() { return ptrHead; } // return pointer

    void setTitle(string t) { movieTitle = t; }
    void setHead(Node *p) { ptrHead = p; }

private:
    string movieTitle; // title
    Node *ptrHead;     // pointer to head of linked list containing reviews
};

// global
const int SIZE = 4, COMMENTS = 3; // subject to change

// function prototypes
Node addHead(Node *&);
void averagePrintAll(Node *);
void assignAll(array<Movie, SIZE> &arrMovies);
void printAll(array<Movie, SIZE> arrMovies);

/************************************************
 * Function: Main
 ************************************************/
int main()
{

    srand(time(0)); // seed random

    array<Movie, SIZE> arrMovies = {}; // array declaration

    assignAll(arrMovies);
    printAll(arrMovies);
    // Node *head = nullptr;
}

Node addHead(Node *&head)
{
    string buf;
    ifstream in("reviews.txt");
    Node *temp = new Node;

    if (!in.is_open())
        cout << "ERROR OPENING FILE\n";
    else
    {

        temp->rating = rand()%5; //whole number?

        //assign comment to inputfile
        getline(in, buf);
        temp->comment = buf;

        // assignment
        temp->next = head; // have new node point where head was pointing
        head = temp;       // have head point to next
    }
    in.close();

    return(*temp); 
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

void assignAll(array<Movie, SIZE> &arrMovies) // pass by reference to reassign
{
    string buf;

    // set titles for each object
    for (int i = 0; i < SIZE; i++)
    {
        cout << "Enter a name for the title of movie #" << i + 1 << ": "; // i+1 so starts at 1 on userside

        getline(cin, buf);
        arrMovies[i].setTitle(buf);
    }

    // create linked list for each object
    for (int i = 0; i < SIZE; i++) //for each object
    {
        arrMovies[i].setHead(nullptr); //set each head's starting point as nullptr
        for(int j= 0; j < COMMENTS; j++)
        {
            addHead();
        }
    }
}

void printAll(array<Movie, SIZE> arrMovies)
{
    for (int i = 0; i < SIZE; i++)
    {
        cout << arrMovies[i].getTitle() << '\n'; //correctly working
    }
}