/*
Author: Kiona Peni
date: 9/29/26
desc: this is a prototype for our task manager, I don't know how to connect
the front end with the backend
but I'm going to leave that into the trusty hands of my team members
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

static int idCounter = 0;
static int assignmentnum = 0;
char letter;

const string FILENAME = "task.csv";

// maybe we need a total points and the amount of points they actually got
// int assignmenttotalpoints
// int assigmentscoredpoints
struct Assignment
{

    string AssignmentName;
    int difficulty; // 0 is easy, 1 is medium, 2 is hard
    bool completed;
    int AssignmentNumber;
    string dueDate;
    Assignment *next;

    // commenting out grade related stuff for now because I'm not sure we need to keep track of all of this

    // int AssignmentScoredPoints;
    // int AssignmentValue; // this is the total points the assignment is worth
    // char assignmentGrade;
    // string assignmentType; // "test" "assignment" "final exam"
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

    void Update_Tasks_With_CSV()
    {
        std::ifstream file(FILENAME);

        string line;
        string task;
        string tempDifficulty;
        string dueDate;
        string temp_completed;

        int difficulty;
        bool completed;
        // First check if the file even opened successfully
        if (!file.is_open())
        {
            std::cout << "File could not be opened." << std::endl;
            return;
        }

        // Peek at the first character
        if (file.peek() == std::ifstream::traits_type::eof())
        {
            return;
        }
        else
        {
            while (getline(file, line))
            {
                stringstream ss(line);

                getline(ss, task, ',');
                getline(ss, tempDifficulty, ',');
                getline(ss, dueDate, ',');
                getline(ss, temp_completed);

                difficulty = stoi(tempDifficulty);
                istringstream(temp_completed) >> boolalpha >> completed;

                Assignment *new_assignment = new Assignment();
                new_assignment->completed = completed;
                new_assignment->AssignmentNumber = assignmentnum++;
                new_assignment->AssignmentName = task;
                new_assignment->difficulty = difficulty;
                new_assignment->dueDate = dueDate; // "9/30/26"
                if (this->assignments == NULL)
                {
                    this->assignments = new_assignment;
                }
                else // insert in the front, it's not an ordered list for now so it's ok
                {
                    new_assignment->next = this->assignments;
                    this->assignments = new_assignment;
                }
            }
        }

        file.close();
    }

    /*
    Helper function to turn number difficulty into string for printing
    */
    string difficulty_to_string(int difficulty)
    {
        switch (difficulty)
        {
        case 1:
            return "easy";

        case 2:
            return "medium";

        case 3:
            return "hard";
        default:
            cout << "error: invalid difficulty" << endl;
            return "-1";
        }
    }

    int difficulty_to_int(string difficulty)
    {
        if (difficulty == "easy")
        {
            return 1;
        }
        else if (difficulty == "medium")
        {
            return 2;
        }
        else if (difficulty == "hard")
        {
            return 3;
        }
        else
        {
            cout << "error: invalid difficulty" << endl;
            return -1;
        }
    }

    void Add_Task(string name, int difficulty, string dueDate)
    {
        fstream file(FILENAME, ios::app);
        if (!file.is_open())
        {
            cout << "error, file couldn't open" << endl;
            return;
        }
        else
        {
            file << name << "," << difficulty << "," << dueDate << "," << false << "\n";
        }
        file.close();

        Assignment *new_assignment = new Assignment();
        new_assignment->completed = false;
        new_assignment->AssignmentNumber = assignmentnum++;
        new_assignment->AssignmentName = name;
        new_assignment->difficulty = difficulty;
        new_assignment->dueDate = dueDate; // "9/30/26"
        if (this->assignments == NULL)
        {
            this->assignments = new_assignment;
        }
        else // insert in the front, it's not an ordered list for now so it's ok
        {
            new_assignment->next = this->assignments;
            this->assignments = new_assignment;
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

        fstream file(FILENAME, ios::out | ios::trunc);
        if (!file.is_open())
        {
            cout << "error, file couldn't open" << endl;
            return;
        }
        else
        {
            Assignment *task = this->assignments;
            while (task != NULL)
            {
                file << task->AssignmentName << "," << task->difficulty << "," << task->dueDate << ",";
                if (task->completed)
                {
                    file << "true" << "\n";
                }
                else
                {
                    file << "false" << "\n";
                }
                task = task->next;
            }
        }
        file.close();
    }

    Assignment *Find_Task(string name)
    {
        bool found = false;
        Assignment *predAssignment = NULL;
        Assignment *search = this->assignments;

        while (search != NULL && !found) // search list for assignment
        {
            if (search->AssignmentName == name)
            {
                found = true;
                return search;
            }
            predAssignment = search;
            search = search->next;
        }
        return NULL;
    }
    // ADDME: Edit_Task
    // parameter: assignment name anything else the user would want to edit

    void Edit_Task(Assignment *task, string newName = "", int difficulty = -1, string dueDate = "")
    {
        if (task != NULL)
        {
            if (newName != "")
            {
                task->AssignmentName = newName;
            }
            if (difficulty != -1)
            {
                task->difficulty = difficulty;
            }
            if (dueDate != "")
            {
                task->dueDate = dueDate;
            }
        }
        else
        {
            cout << "Task could not be edited as the task does not exist" << endl;
            return;
        }

        fstream file(FILENAME, ios::out | ios::trunc);
        if (!file.is_open())
        {
            cout << "error, file couldn't open" << endl;
            return;
        }
        else
        {
            Assignment *task = this->assignments;
            while (task != NULL)
            {
                file << task->AssignmentName << "," << task->difficulty << "," << task->dueDate << ",";
                if (task->completed)
                {
                    file << "true" << "\n";
                }
                else
                {
                    file << "false" << "\n";
                }
                task = task->next;
            }
        }
        file.close();
    }

    void Mark_As_Complete(string name)
    {
        if (this->assignments != NULL)
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

        fstream file(FILENAME, ios::out | ios::trunc);
        if (!file.is_open())
        {
            cout << "error, file couldn't open" << endl;
            return;
        }
        else
        {
            Assignment *task = this->assignments;
            while (task != NULL)
            {
                file << task->AssignmentName << "," << task->difficulty << "," << task->dueDate << ",";
                if (task->completed)
                {
                    file << "true" << "\n";
                }
                else
                {
                    file << "false" << "\n";
                }
                task = task->next;
            }
        }
        file.close();
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
            cout << endl;
            while (location != NULL)
            {
                cout << location->AssignmentName << ":" << endl;
                if (location->completed)
                {
                    cout << "COMPLETE" << endl;
                    cout << "Difficulty: " << this->difficulty_to_string(location->difficulty) << endl;
                    cout << "Due By " << location->dueDate << endl;
                }
                else
                {
                    cout << "NOT COMPLTE" << endl;
                    cout << "Difficulty: " << this->difficulty_to_string(location->difficulty) << endl;
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
    user->Update_Tasks_With_CSV();

    cout << "Hello Welcome to our Student Task Manager" << endl;
    cout << "Our task manager allows you to add, remove, and edit tasks!" << endl;
    cout << "Then when you complete your tasks you can mark them as complete!!" << endl;

    string action = "";
    string task;
    string difficulty;
    int difficulty_num;
    string dueDate;
    Assignment *task_to_edit;

    while (action != "exit")
    {

        if (action != "exit")
        {
            user->Display_Task();
        }

        cout << "if you would like to add a task enter 'a'" << endl;
        cout << "if you would like to remove a task enter 'r'" << endl;
        cout << "if you would like to edit a task enter 'e'" << endl;
        cout << "if you would like to mark a task as complete enter 'c'" << endl;
        cout << "if you would liek to exit the program enter 'exit'" << endl;

        getline(cin, action);

        if (action == "a")
        {
            cout << "You are adding a task!" << endl;
            cout << "if you don't want to do that enter '-1', otherwise please enter the name of your task" << endl;
            getline(cin, task);
            if (task == "-1")
            {
                continue;
            }
            cout << "Now enter a difficulty for this task ('easy'/'medium'/'hard')" << endl;
            getline(cin, difficulty);
            while (difficulty != "easy" && difficulty != "medium" && difficulty != "hard")
            {
                cout << "that's not a valid difficulty please enter either 'easy', 'medium', or 'hard'" << endl;
                getline(cin, difficulty);
            }
            cout << "Now please enter a due date for your task like this 'MM/DD/YYYY'" << endl;
            getline(cin, dueDate);

            // for this I'm just trusting the uesr inputs it how I would like them to
            // it really doesn't matter because we aren't sorting anyway

            user->Add_Task(task, user->difficulty_to_int(difficulty), dueDate);
        }

        else if (action == "r")
        {
            cout << "You are removing a task" << endl;
            cout << "if you don't want to do that enter '-1', otherwise please enter the name of the task you would like to remove" << endl;
            getline(cin, task);

            if (task == "-1")
            {
                continue;
            }

            user->Remove_Task(task);
        }

        else if (action == "e")
        {
            cout << "You are editing a task!" << endl;
            cout << "if you don't want to do that enter '-1', otherwise enter the name of the tast you would like to edit" << endl;
            getline(cin, task);

            if (task == "-1")
            {
                continue;
            }

            task_to_edit = user->Find_Task(task);

            cout << "please enter the new name of your task, if you don't want to edit press enter" << endl;
            getline(cin, task);
            if (task == "-1")
            {
                continue;
            }
            cout << "Now enter a new difficulty for this task ('easy'/'medium'/'hard'), , if you don't want to edit press enter" << endl;
            getline(cin, difficulty);
            while (difficulty != "" && difficulty != "easy" && difficulty != "medium" && difficulty != "hard")
            {
                cout << "that's not a valid difficulty please enter either 'easy', 'medium', or 'hard'" << endl;
                getline(cin, difficulty);
            }
            if (difficulty == "")
            {
                difficulty_num = -1;
            }
            else
            {
                difficulty_num = user->difficulty_to_int(difficulty);
            }
            cout << "Now please enter a due date for your task like this 'MM/DD/YYYY', if you don't want to edit press enter" << endl;
            getline(cin, dueDate);

            user->Edit_Task(task_to_edit, task, difficulty_num, dueDate);
        }

        else if (action == "c")
        {
            cout << "You are marking a task as complete, CONGRADULATIONS!!" << endl;
            cout << "if you do not want to do that enter -1, otherwise enter the name of the task you would like to mark as complete" << endl;
            if (task == "-1")
            {
                continue;
            }
            getline(cin, task);

            user->Mark_As_Complete(task);
        }

        else if (action == "exit")
        {
            cout << "Goodbye, thank you for using our task manager" << endl;
        }

        else
        {
            cout << "unfortunately that is an invalid command please try again T_T" << endl;
        }
    }

    return 0;
}