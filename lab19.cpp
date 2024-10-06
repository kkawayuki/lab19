// COMSC-210 | lab 19 | Kent Kawashima
// IDE used: Visual Studio Code
#include <iostream>
#include <fstream> // for file input/output
#include <time.h>
#include <cstdlib> 
using namespace std;

// struct
struct Node
{
    double rating;
    string comment;
    Node *next; // pointer to next node in LL
};

//class
class Movie
{
public:
    string getTitle() const {return movieTitle;}
    
private:
    string movieTitle; //title
    Node *ptrHead; //pointer to head of linked list containing reviews
};

// function prototypes
void nodeLoop(Node *&); // menu-driven program loop to assign nodes based on mode
void addHead(Node *&);
bool promptRepeat(); // checks if user wants to go again.
void averagePrintAll(Node *);

/************************************************
 * Function: Main
 ************************************************/
int main()
{
    
    srand(time(0)); //seed random 

    array<Movie, 4>arrMovies = {};

    Node *head = nullptr;
    nodeLoop(head); // get user choice and loop based on it
}


void nodeLoop(Node *&head) 
{
    do
    {
        addHead(head); 
    } 
    while (promptRepeat()); 

    averagePrintAll(head); // output all at end
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

bool promptRepeat()
{
    string buf;

    while (true)
    {
        cout << "Enter another review? Y/N: ";
        cin >> buf;
        if (tolower(buf[0]) == 'y')
        {
            return (true);
            break;
        }
        else if (tolower(buf[0]) == 'n')
        {
            return (false);
            break;
        }
        else
        {
            cout << "Please enter a valid response, (Y/N).\n";
        }
    }
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