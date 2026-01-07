#include "todolist.hpp"
#include <unordered_set>
#include <cctype>
using namespace std;

// prototypes
// screens
int startMenu();
int mainMenu(int size);
int createScreen(vector<ToDoList> &list);
int viewScreen(vector<ToDoList> &list);

// helper functions
char getInput(unordered_set<char> valid_inputs);

int main()
{
    // program variables
    bool run = true;
    unsigned int screen = 0;
    char input = ' ';

    // vector of to do list
    vector<ToDoList> lists;

    cout << "Welcome to To Do List App" << endl;
    cout << "Created by: L. David Ruiz" << endl << endl;

    do
    {
        switch (screen){
            case 0: // start screen
                screen = startMenu();
                break;
            case 1: // main menu
                screen = mainMenu(lists.size());
                break;
            case 2: // create list
                screen = createScreen(lists);
                break;
            case 3: // view lists
                break;
            case 4: // delete list
                break;
        }

    // print a line for each screen update
    cout << endl;
        
    } while (run);

    return 0;
}

// functions
// screens
int startMenu() // first screen
{
    // print header
    cout << "Press SPACE then ENTER to start" << endl;
    char input = '\0';
    cin >> input;
    
    return 1;
}

int mainMenu(int size) // main screen
{
    // display basic commands
    cout << "Commands: " << endl;
    cout << "[C] - Create new to-do list" << endl;
    
    // if there is at least one list created, show other commands
    if (size != 0)
    {
        cout << "[V] - View to-do lists" << endl;
        cout << "[D] - Delete to-do list" << endl;
    }

    // close the program
    cout << "[Z] - Close program" << endl;

    
    unordered_set<char> valid_inputs = {'c', 'z'};
    if (size != 0) 
    {
        valid_inputs.insert('v');
        valid_inputs.insert('d');
    }
    char input = getInput(valid_inputs);
    
    switch (input)
    {
        case 'c': // create to-do List
            return 2;            
            break;
        case 'v': // view lists
            return 3;
            break;
        case 'd': // delete list
            return 3;
            break;
        case 'z': // close program
            return 0;
            break;
        
    }
    return 1;
}

int createScreen(vector<ToDoList> &list) // create a to-do list
{
    cout << "Name of list: ";
    string name;
    cin >> name;
    ToDoList t(name);
    list.push_back(t);
    cout << name << " list created." << endl;

    return 1;
}

int viewScreen(vector<ToDoList> &list) // view available
{
    // header 
    cout << "Lists: " << endl;
    cout << "----------" << endl;
    
    // print lists titles
    for(int i = 0; i < list.size(); i++)
    {
        cout << (i + 1) << ") " << list[i].getName() << endl;
    }

    // print commands
    cout << "[V] - View list" << endl;
    cout << "[Z] - Go back" <<endl;

    unordered_set<char> valid_inputs = {'v', 'z'};
    char input = getInput(valid_inputs);

    switch (input)
    {
        case 'v': // view list
            cout << "ID of list to view: ";
            


            return 3;
            break;
        case 'z':
            return 1;
            break;
    }
    
    return 3;
}


// helper functions
// functions to get and validate inputs given a set of valid chars
char getInput(unordered_set<char> valid_inputs)
{
    char input = '\0'; // user input

    do
    {
        cin >> input;
        input = tolower(input);

        if (valid_inputs.find(input) != valid_inputs.end()) break;
        else
        {
            cout << "Invalid input." << endl;
        }
        
        cin.ignore();

    } while (true);

    return input;
}

int getInput(int limit)
{
    int input = 0;

    do
    {
        cin >> input;
        if (input < 0 || input >= limit)
        {
            cout << "Invalid input. Try again." << endl;
        }else return input;
    }while (true);
}