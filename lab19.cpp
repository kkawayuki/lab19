// COMSC-210 | lab 19 | Kent Kawashima
// IDE used: Visual Studio Code
#include <iostream>
#include <fstream> // input
#include <time.h> //rand
#include <cstdlib>
#include <array>
#include <iomanip> //setprecision
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

    //setter
    void setTitle(string t) { movieTitle = t; }
    void setHead(Node *p) { ptrHead = p; }

    //getter 
    string getTitle() const { return movieTitle; }
    Node *getHead() { return ptrHead; } 

    //for when functions need to modify head pointer
    Node *&modifyHead() { return ptrHead; }  

private:
    string movieTitle; // title
    Node *ptrHead;     // pointer to head of linked list containing rating/reviews
};

// global
const int SIZE = 4, COMMENTS = 3; // can be modified to change the 1) number of movies, 2) comments/ratings per movie

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

/************************************************
 * Function: Uses file input and a reference-passed
 * pointer to the head of a Movie class's linked
 * list head to generate a new head for that linked
 * list, moving the others accordingly.
 * 
 * Note: there's probably a much more efficient way
 * to remember where in the text file you are than 
 * using a static line counter to increment and ignore
 * file input (lines 93/94.)
 * 
 * Parameters: *&head, pointer to head, passed by reference
 * so it can be altered without the need of passing the
 * object as a reference then changing the head pointer with
 * a getHead() method.
 * 
 * Return: NONE
 ************************************************/
void addHead(Node *&head)
{
    static int lines = 0;
    string buf;
    ifstream in("reviews.txt");
    Node *temp = new Node;

    if (!in.good()) //if cannot open text file
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

/************************************************
 * Function: Assigns each Movie object in an array
 * of Movies both a user-defined name, and fills their
 * linked lists and respective node fields with calls to
 * the addHead function.
 * 
 * Parameters: &arrMovies, the reference variable of 
 * the array of Movie objects.
 * 
 * Return: NONE
 ************************************************/
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

/************************************************
 * Function: Print out the formatted result of all 
 * assignmentfor the user to see cohesively. 
 * 
 * Parameters: arrMovies, pointer to the array 
 * of Movie objects, so that object methods can be
 * used to access specific fields.
 * 
 * Return: NONE
 ************************************************/
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
