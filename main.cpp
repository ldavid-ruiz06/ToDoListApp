// To-Do List Software
// Created by: Luis David Ruiz Velázquez
// Started: Jan-6-2026
// Last update: Jan-7-2026


// main program where user can create and use the to-do lists

#include "todolist.hpp"
#include <cctype>
#include <unordered_set>
#include <vector>
using namespace std;

// screen prototypes
int startMenu();
int mainMenu();
int listView();
int taskView();

// helper prototypes
char getInput(unordered_set<char> valid_inputs);
int getId(int limit);


int main()
{
    // main vars
    int screen = 0; // current screen
    bool run = true; // the program is running
    vector<ToDoList> lists; // lists of to-do lists

    // while program is running
    while (run)
    {
        // check screen current value to display correct screen
        switch (screen)
        {
            case 0: // start screen
                screen = startMenu();
                break;
            case 1: // main menu
                screen = mainMenu();
                break;
            case 2: // list view
                screen = listView();
                break;
            case 3: // task view
                screen = taskView();
                break;
        }



    }



    return 0;
}


// screens functions
int startMenu()
{
    // display header and credits
    cout << "To-do List Software!" << endl;
    cout << "Created by: L. David Ruiz" << endl;
    cout << "Press [ENTER] to start..." << endl;

    // wait for user input before changing screens
    cin.get();
    cin.ignore(999, '\n');
    return 1;
}

int mainMenu(vector<ToDoList> &list)
{
    cout << "List View" << endl;

    // displayer message if there are no to-do lists
    if (list.size() == 0) cout << "There's no to-do lists to display..." << endl;
    
    // else, display all the to-do titles
    else 
    {
        for (int i = 0; i < list.size(); i++)
        {
            cout << (i + 1) << ") " << list[i].getName() << endl;
        }
    }

    // display commands
    cout << "[C] - Create to-do list" << endl;
    if (list.size() > 0) 
    {
        cout << "[V] - View to-do list" << endl;
        cout << "[D] - Delete to-do list" << endl;
    }

    // get command
    unordered_set<char> valid_commands = {'c'};
    if (list.size() > 0) 
    {
        valid_commands.insert('v');
        valid_commands.insert('d');
    }
    char command = getInput(valid_commands);

    // check command
    switch (command)
    {
        case 'c': // create to-do list
            
        case 'v': // view to-do list
        case 'z': // delete to-do list
    }

}





// helper functions
char getInput(unordered_set<char> valid_inputs)
{
    // input
    char input = '\0';

    do // get user input, and repeat until the char is one of the allowed one
    {
        cin >> input;
        input = tolower(input);
        if (valid_inputs.find(input) != valid_inputs.end()) break;
        else 
        {
            cout << "Invalid command" << endl;
            cin.ignore(999, '\n');
        }
    } while (true);
    
    return input;
}

int getIndex(int limit)
{
    int input = 0;

    do // get user input, and repeat until the char is one of the allowed one
    {
        cin >> input;
        if (input > 0 && input <= limit) break;
        else 
        {
            cout << "Invalid index" << endl;
            cin.ignore(999, '\n');
        }
    } while (true);
    
    return (input - 1);
}