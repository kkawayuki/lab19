// COMSC-210 | lab 19 | Kent Kawashima
// IDE used: Visual Studio Code
#include <iostream>
#include <fstream> // for file input/output
#include <time.h>
#include <cstdlib>
#include <array>
#include <iomanip>
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
    Node *&modifyHead() { return ptrHead; }

    void setTitle(string t) { movieTitle = t; }
    void setHead(Node *p) { ptrHead = p; }

private:
    string movieTitle; // title
    Node *ptrHead;     // pointer to head of linked list containing reviews
};

// global
const int SIZE = 4, COMMENTS = 3; // subject to change

// function prototypes
void addHead(Node *&);
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
}

void addHead(Node *&head)
{
    static int lines = 0;
    string buf;
    ifstream in("reviews.txt");
    Node *temp = new Node;

    if (!in.good())
        cout << "ERROR OPENING FILE\n";
    else
    {
        temp->rating = ((rand() % 41) / 10.0) + 1; // division by 10.0 for implicit double conversion

        // assign comment to inputfile
        for (int i = 0; i < lines; i++)
            in.ignore(100,'\n');
            
        getline(in, temp->comment);
         

        // assignment
        temp->next = head; // have new node point where head was pointing
        head = temp;       // have head point to next

        lines++; // increment static so number of lines to ignore is remembered
    }
    // in.close(); //maybe have do at end
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
    for (int i = 0; i < SIZE; i++) // for each object
    {
        arrMovies[i].setHead(nullptr); // set each head's starting point as nullptr
        for (int j = 0; j < COMMENTS; j++)
        {
            addHead(arrMovies[i].modifyHead());
        }
    }
}

void printAll(array<Movie, SIZE> arrMovies) // titles only for now
{
    Node *current = new Node; // pointer for iteration

    cout << '\n'; // formatting

    for (int i = 0; i < SIZE; i++)
    {
        cout << "Name of Movie #" << i + 1 << ": " << arrMovies[i].getTitle() << '\n';

        current = arrMovies[i].getHead();
        for (int j = 0; j < COMMENTS; j++)
        {
            if (current)
            {
                cout << "Rating: " << fixed << setprecision(1) << current->rating << "\n"; // fixed ensures whole numbers also show .0
                cout << "Comment: " << current->comment << '\n';
            }
            current = current->next;
        }
        cout << '\n'; // formatting
    }
}
