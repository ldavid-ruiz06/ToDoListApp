// Reference with the struct and all the main functions
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;


struct Task
{
    // attributes
    string name = ""; // name of task
    string description = ""; // short description for the task
    unsigned int priority = 0;
    bool is_done = false;

    // methods
    // constructor 
    Task(string taskName, string taskDescription, unsigned int taskPriority)
    {
        name = taskName;
        description = taskDescription;
        priority = taskPriority;
    }

    Task(string taskName, unsigned int taskPriority)
    {
        name = taskName;
        priority = taskPriority;
    }

    // copy constructor
    Task(const Task &t)
    {
        name = t.name;
        description = t.description;
        priority = t.priority;
        is_done = t.is_done;
    }

    // copy assignment
    Task &operator=(const Task &t)
    {
        name = t.name;
        description = t.description;
        priority = t.priority;
        is_done = t.is_done;
        return *this;
    }
};

class ToDoList
{
    public:
    // constructor: Create an empty To Do List 
    // and assign a name to it. If no name is 
    // given, just name it 'My List'
    ToDoList(string name = "My List") { list_name = name; }

    // view To Do List
    void viewList() const
    {
        // print list name
        cout << list_name << endl;
        cout << "--------------------" << endl;

        // for each task, print it's name, and its completion
        for(int i = 0; i < size; i++)
        {
            cout << (i + 1) << ") " << task_list[i].name << ": ";
            if (task_list[i].is_done) cout << "C";
            else cout << "X";
            cout << endl;
        }
        cout << endl;
    }
        
    // add task
    void addTask(string name, unsigned int priority = 0, string description = "")
    {
        // create task and add it to the list
        Task new_task(name, description, priority);
        task_list.push_back(new_task);
        size++;
        
    // find its place in the heap
        // get id of added task
        int current = size - 1;
        // compare priority with the previous one
        // if cur > prev, swap positions
        while(current > 0 && task_list[current].priority > task_list[current - 1].priority)
        {
            swap(task_list[current], task_list[current - 1]);
        }
    }

    // remove task
    void removeTask(unsigned int id)
    {
        // check if id is valid index
        if (id > size-1) throw invalid_argument("Invalid index number.");

        task_list.erase(task_list.begin() + id);
        size--;
    }

    // mark task as completed
    void markComplete(unsigned int id) 
    {
        // if id is valid, change is_done to true
        if (id > size-1) throw invalid_argument("Invalid index number.");
        task_list[id].is_done = true; 
    }

    // view task detail
    void viewTask(unsigned int id)
    {
        // check if id is valid
        if (id > size-1) throw invalid_argument("Invalid index number.");

        // get task and print it's details
        Task t = task_list[id];

        cout << t.name << endl << "Description: ";
        if (t.description != "") cout << t.description << endl;
        else cout << "None" << endl;
        cout << "Priority: " << t.priority << endl;
        cout << "Status: ";
        if (t.is_done) cout << "Completed" << endl;
        else cout << "To do" << endl;
        cout << endl;
    }
    
    private:
    // attributes
    unsigned int size = 0;
    vector<Task> task_list; // for the sake of understanding, we are using a (max)heapmap with priority
    string list_name;

    // helper methods
    void swap(Task &A, Task &B)
    {
        Task temp = A;
        A = B;
        B = temp;
    }
    
    
};
