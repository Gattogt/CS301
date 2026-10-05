/*
Author: Kiona Peni
date: 9/29/26
desc: this is a prototype for our task manager, I don't know how to connect
the front end with the backend
but I'm going to levae that into the trust hands of my team members
*/

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

static int idCounter = 0;
static int assignmentnum = 0;
char letter;

// maybe we need a total points and the amount of points they actually got
// int assignmenttotalpoints
// int assigmentscoredpoints
struct Assignment
{
    int difficulty; // 0 is easy, 1 is medium, 2 is hard
    bool completed;
    int AssignmentNumber;
    string AssignmentName;
    int AssignmentScoredPoints;
    int AssignmentValue; // this is the total points the assignment is worth
    string dueDate;
    char assignmentGrade;
    Assignment *next;
    string assignmentType; // "test" "assignment" "final exam"
};

class StudentType
{
public:
    int id;
    string firstName;
    string lastName;
    Assignment *assignments;

    ~StudentType()
    {
        // Assignment* temp = assignments;
        Assignment *predloc = NULL;
        while (assignments != NULL)
        {
            predloc = assignments;
            assignments = assignments->next;
            delete predloc;
        }
    }

    StudentType(string firstName, string lastName)
    {
        id = ++idCounter * 100;
        this->firstName = firstName;
        this->lastName = lastName;
        this->assignments = NULL;
    }

    void Add_Task(string name, int points, string dueDate)
    {
        Assignment *new_assignment = new Assignment();
        new_assignment->completed = false;
        new_assignment->AssignmentNumber = assignmentnum++;
        new_assignment->AssignmentName = name;
        new_assignment->AssignmentValue = points;
        new_assignment->dueDate = dueDate; // "9/30/26"
        if (this->assignments == NULL)
        {
            this->assignments = new_assignment;
        }
        else
        {
            Assignment *temp;
            temp = this->assignments->next;
            this->assignments->next = new_assignment;
            new_assignment->next = temp;
        }
    }

    void Remove_Task(string name)
    {
        bool found = false;
        Assignment *predAssignment = NULL;
        Assignment *search = this->assignments;

        while (search != NULL && !found) // search list for assignment
        {
            if (search->AssignmentName == name)
            {
                found = true;
                break;
            }
            predAssignment = search;
            search = search->next;
        }

        if (!found) // if not found then say we didn't find it
        {
            cout << "Task does not exist" << endl // debugging line making sure we know if an item is deleted
                 << endl;
        }
        else if (predAssignment == NULL) // if found then check if we removeing first item
        {
            this->assignments = search->next;
            delete search;
            cout << "Successfully Deleted" << endl // debugging line making sure we know if an item is deleted
                 << endl;
        }
        else
        {
            predAssignment->next = search->next;
            delete search;
            cout << "Successfully Deleted" << endl // debugging line making sure we know if an item is deleted
                 << endl;
        }
    }

    // ADDME: Edit_Task
    // parameter: assignment name anything else the user would want to edit

    void Mark_As_Complete(string name)
    {

        bool found = false;
        Assignment *predAssignment = NULL;
        Assignment *search = this->assignments;

        while (search != NULL && !found) // search list for assignment
        {
            if (search->AssignmentName == name)
            {
                found = true;
                break;
            }
            predAssignment = search;
            search = search->next;
        }

        if (found)
        {
            search->completed = true;
        }
    }

    void Display_Task() // for debugging purposes while we do not actually have front end to test with
    {
        Assignment *location = this->assignments;
        if (location == NULL)
        {
            cout << "You currently have no tasks";
        }
        else
        {
            while (location != NULL)
            {
                cout << location->AssignmentName << ":" << endl;
                if (location->completed)
                {
                    cout << "COMPLETE";
                    cout << location->AssignmentScoredPoints << "/" << location->AssignmentValue << endl;
                    cout << "Due By " << location->dueDate << endl;
                }
                else
                {
                    cout << "NOT COMPLTE";
                    cout << "?/" << location->AssignmentValue << endl;
                    cout << "Due by " << location->dueDate << endl;
                }
                cout << endl;
                location = location->next;
            }
        }
    }
};

int main()
{
    StudentType *user = new StudentType("Kiona", "Peni");

    user->Add_Task("Homework 5", 10, "10/1/2026");
    user->Add_Task("Lab 2", 10, "9/17/2026");
    user->Add_Task("Test 1", 100, "11/1/2026");
    user->Display_Task();

    user->Remove_Task("Lab 1");
    user->Remove_Task("Lab 2");
    user->Display_Task();

    return 0;
}