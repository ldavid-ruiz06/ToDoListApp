#include "todolist.hpp"
using namespace std;

int main()
{
    ToDoList A;
    A.addTask("Task1", 0, "Description 1");
    A.addTask("Task2", 2);
    A.addTask("Task3", 1);
    A.addTask("Task4", 0);
    A.removeTask(0);
    A.markComplete(0);
    A.markComplete(2);
    A.viewList();
    A.viewTask(0);
    A.viewTask(1);

    return 0;
}