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
int mainMenu(vector<ToDoList> &list, int &view_id);
int listScreen(vector<ToDoList> &list, int &view_id);
int taskView(int id);

// functions prototypes
void createList(vector<ToDoList> &list);
void deleteList(vector<ToDoList> &list);
void viewList(vector<ToDoList> &list);
void createTask(ToDoList &list);
void deleteTask(ToDoList &list);
void completeTask(ToDoList &list);

// helper prototypes
char getInput(unordered_set<char> valid_inputs);
int getIndex(int limit);


int main()
{
    // main vars
    int screen = 0; // current screen
    bool run = true; // the program is running
    vector<ToDoList> lists; // lists of to-do lists
    int view_id = -1;

    // while program is running
    while (run)
    {
        cout << "---------------" << endl;
        // check screen current value to display correct screen
        switch (screen)
        {
            case 0: // start screen
            {
                screen = startMenu();
                break;
            }
            case 1: // main menu
            {
                screen = mainMenu(lists, view_id);
                break;
            }
            case 2: // list view
                screen = listScreen(lists, view_id);
                break;
            case 3: // task view
                //screen = taskView();
                break;
        }
        cout << "---------------" << endl;
        cout << endl;
        cout << "\x1B[2J" << endl;
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

int mainMenu(vector<ToDoList> &list, int &view_id)
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
    cout << endl << "Commands: " << endl;

    // display commands
    cout << "[C] - Create to-do list" << endl;
    if (list.size() > 0) 
    {
        cout << "[V] - View to-do list" << endl;
        cout << "[D] - Delete to-do list" << endl;
    }
    cout << endl;

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
        {
            createList(list);
            return 1;
            break;
        }
        case 'v': // view to-do list
        {
            // choose a valid id
            cout << "Id of list to view: ";
            int id = getIndex(list.size());
            cout << endl;
            if (id == -1) break;

            // display list of task (change to listScreen)
            view_id = id;
            return 2;
            break;
        }
        case 'd': // delete to-do list
        {
            deleteList(list);
            return 1;
            break;
        }
        default:
            return 1;
    }
    return 1;
}

int listScreen(vector<ToDoList> &list, int &view_id)
{   
    // display list of tasks
    if (list[view_id].numberTasks() > 0) list[view_id].viewList();
    else cout << list[view_id].getName() << endl << "No tasks to show..." << endl;

    // display commands
    cout << endl << "Commands: " << endl;
    cout << "[C] - Create new task" << endl;
    if (list[view_id].numberTasks() > 0)
    {
        cout << "[V] - View task" << endl;
        cout << "[X] - Mark task as completed" << endl;
        cout << "[D] - Delete task" << endl;
    }
    cout << "[B] - Go back" << endl;

    // get input
    unordered_set<char> valid_commands = {'c', 'b'};
    if (list[view_id].numberTasks() > 0) 
    {
        valid_commands.insert('v');
        valid_commands.insert('x');
        valid_commands.insert('d');
    }
    char command = getInput(valid_commands);

    // process command
    cout << endl;
    switch (command)
    {
        case 'c': // create task
        {
            createTask(list[view_id]);
            return 2;
            break;
        }
        case 'v': // view task
        {
            // choose a valid id
            // display list of task (change to listView)
            cout << "View task" << endl;
            return 2;
            break;
        }
        case 'd': // delete task
        {
            // choose a valid id
            // delete list
            deleteTask(list[view_id]);
            return 2;
            break;
        }
        case 'x': // mark task a complete
        {
            completeTask(list[view_id]);
            return 2;
            break;
        }
        case 'b': // go back
        {
            return 1;
            break;
        }
        default:
            return 1;
    }
    return 1;
}

// functions
void createList(vector<ToDoList> &list)
{
    string name = "";
    cout << "Name of the list: ";
    cin >> name;

    ToDoList t(name);
    list.push_back(t);
    cout << "List " << name << " successfully created!" << endl << endl;
}

void deleteList(vector<ToDoList> &list)
{
    cout << "Id of list to delete: ";
    // choose a valid id
    int id = getIndex(list.size());

    // if id is -1, cancel process
    cout << endl;
    if (id == -1) return;

    // delete list
    list.erase(list.begin() + id);
}

void createTask(ToDoList &list)
{   
    // get name of task
    cout << "Name of task: ";
    string name;
    cin >> name;

    // add task
    list.addTask(name);
}

void deleteTask(ToDoList &list)
{
    cout << "Id of task to delete: ";
    // choose a valid id
    int id = getIndex(list.numberTasks());

    // if id is -1, cancel process
    cout << endl;
    if (id == -1) return;

    // delete list
    list.removeTask(id);
}

void completeTask(ToDoList &list)
{
    cout << "Id of task to complete: ";
    // choose a valid id
    int id = getIndex(list.numberTasks());

    // if id is -1, cancel process
    cout << endl;
    if (id == -1) return;

    // delete list
    list.markComplete(id);
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
    cin.ignore(999, '\n');
    return input;
}

int getIndex(int limit)
{
    int input = 0;

    cin >> input;
    if (input > 0 && input <= limit) return (input - 1);
    else 
    {
        cout << "Invalid index" << endl;
        return -1;
    }
}