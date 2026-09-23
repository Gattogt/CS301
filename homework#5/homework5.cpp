#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int idCounter = 0;
char letter;

// maybe we need a total points and the amount of points they actually got
// int assignmenttotalpoints
// int assigmentscoredpoints
struct Assignment
{
  int AssignmentNumber;
  int AssignmentScoredPoints;
  int AssignmentValue; // this is the total points the assignment is worth
  char assignmentGrade;
  Assignment *next;
};

class StudentType
{
public:
  int id;
  int finalStudentGrade;              // percentage
  int finalProgramingAssigmentGrades; // points
  int finalTestGrades;                // points
  int finalExamGrades;                // points
  string firstName;
  string lastName;
  Assignment *headProgramingAssigment;
  Assignment *headTest;
  Assignment *headFinalExam;
  StudentType *next;

  StudentType(string firstName, string lastName)
  {
    id = ++idCounter * 100;
    next = NULL;
    this->firstName = firstName;
    this->lastName = lastName;
    finalStudentGrade = 0;
    finalProgramingAssigmentGrades = 0;
    finalTestGrades = 0;
    finalExamGrades = 0;
  }
};

// NEED A WAY TO ADD ASSIGNEMNTS TO THE SEMESTER PROGRAM
// CURRENTLY WE ONLY ASK FOR HOW MANY ASSIGNMENTS PER CATEGORY
// AND THE WEIGHT OF THOSE CATEGORIES
// ADDME: AddAssignemt() - a function that adds an assignment to every students list
class SemesterProgram
{
public:
  int programingAssignments;
  int tests;
  int finalExam;
  int programingAssignmentsTotal;
  int testsTotal;
  int finalExamTotal;
  int programingAssignmentsPercentage;
  int testsPercentage;
  int finalExamPercentage;
  int studentLength;
  StudentType *headStudent;

  SemesterProgram(int pa, int ts, int fe, int paP, int tsP, int feP)
  {
    programingAssignments = pa;
    tests = ts;
    finalExam = fe;
    programingAssignmentsPercentage = paP;
    testsPercentage = tsP;
    finalExamPercentage = feP;
    studentLength = 0;
    headStudent = NULL;
  }
  void ShowProgramingAssigments(int studentId, char type)
  {
    StudentType *temp = headStudent;
    if (type == 'P')
    { // check if we are looking for programming assignments
      cout << "Programing Assignments: \n";
      // loop through students
      while (temp != NULL)
      {
        // see if we found student based of the id that was passed through the funtion
        if (temp->id == studentId)
        {
          // if found then start from the head of the list of assignments
          Assignment *tempAssignment = temp->headProgramingAssigment;
          // loop through list of assignments until there are no more
          // output assignment # and the amount of points they got
          while (tempAssignment != NULL)
          {
            cout << "Assignment#" << tempAssignment->AssignmentNumber << ": " << tempAssignment->AssignmentValue << endl;
            tempAssignment = tempAssignment->next;
          }
          // again maybe break out of the loop but not too important
        }

        temp = temp->next;
      }
      cout << "No assignments for this section";
      // maybe I'm wrong but I'm pretty sure that even if there are assignments
      // this statement will print anyway, because it loops through the students
      // and no matter what after the you finish looping through the students
      // maybe check at the beginning like if this->programming assignments == 0 {print the statement}
      // else then do all of this
    }
    if (type == 'T')
    { // check if we are looking for test assignments
      cout << "Test Assignments: \n";
      // loop through list of students
      while (temp != NULL)
      {
        if (temp->id == studentId)
        { // if student matches id then output their tests
          Assignment *tempAssignment = temp->headTest;
          // loop through list of tests
          while (tempAssignment != NULL)
          {
            cout << "Test#" << tempAssignment->AssignmentNumber << ": " << tempAssignment->AssignmentValue << endl;
            tempAssignment = tempAssignment->next;
          }
        }
        temp = temp->next;
      }
      cout << "No assignments for this section";
      // same as previous
    }
    if (type == 'F')
    { // same as previous logic but for final exam
      cout << "Final Test: \n";
      while (temp != NULL)
      {
        if (temp->id == studentId)
        {
          Assignment *tempAssignment = temp->headFinalExam;
          while (tempAssignment != NULL)
          {
            cout << "Test#" << tempAssignment->AssignmentNumber << ": " << tempAssignment->AssignmentValue << endl;
            tempAssignment = tempAssignment->next;
          }
        }
        temp = temp->next;
      }
      cout << "No assignments for this section";
    }
  }
  void ShowGrades()
  {
    StudentType *temp = headStudent;
    while (temp != NULL)
    {
      cout << "First Name: " << temp->firstName << " Last Name: " << temp->lastName << " Id: " << temp->id << endl;
      ShowProgramingAssigments(temp->id, 'P');
      cout << '\n';
      ShowProgramingAssigments(temp->id, 'T');
      cout << '\n';
      ShowProgramingAssigments(temp->id, 'F');
      cout << '\n';
      temp = temp->next;
    }
  }
  // some of the math is missing currently we are adding up all of the points
  void CalculateAndSetStudentFinalGrade(int id)
  {
    StudentType *temp = headStudent;
    while (temp != NULL)
    {
      if (temp->id == id)
        temp->finalStudentGrade = ((float(temp->finalExamGrades) / float(this->finalExamTotal)) * finalExamPercentage + (float(temp->finalTestGrades) / float(this->testsTotal)) * testsPercentage + (float(temp->finalProgramingAssigmentGrades) / float(this->programingAssignmentsPercentage) * programingAssignmentsPercentage));

      // maybe break out of loop if this happens, not too significant though
      temp = temp->next;
    }
  }
  bool isEmpty()
  {
    return studentLength == 0;
  }

  void AddStudent(string first, string last)
  {
    StudentType *location = headStudent;
    StudentType *preLoc = NULL;
    while (location != NULL && first.compare(location->firstName) > 0)
    {
      preLoc = location;
      location = location->next;
    }
    StudentType *newStudent = new StudentType(first, last);
    if (preLoc == NULL)
    {
      newStudent->next = headStudent;
      headStudent = newStudent;
    }
    else
    {
      newStudent->next = location;
      preLoc->next = newStudent;
    }
    studentLength++;
    // set all assigments into link lists
    int temp = 0;
    while (temp < programingAssignments)
    {
      Assignment *newAssigment = new Assignment;
      newAssigment->AssignmentNumber = temp + 1;
      newAssigment->next = newStudent->headProgramingAssigment;
      newStudent->headProgramingAssigment = newAssigment;
      temp++;
    }
    temp = 0;
    while (temp < tests)
    {
      Assignment *newTest = new Assignment;
      newTest->AssignmentNumber = temp + 1;
      newTest->next = newStudent->headTest;
      newStudent->headTest = newTest;
      temp++;
    }
    temp = 0;
    while (temp < finalExam)
    {
      Assignment *newFinalExam = new Assignment;
      newFinalExam->AssignmentNumber = temp + 1;
      newFinalExam->next = newStudent->headFinalExam;
      newStudent->headFinalExam = newFinalExam;
      temp++;
    }
  }
  void printStudents()
  {
    StudentType *temp = headStudent;
    while (temp != NULL)
    {
      cout << "First Name: " << temp->firstName << " Last Name: " << temp->lastName << " Id: " << temp->id << endl;
      temp = temp->next;
    }
  }
  void searchByIdAndUpdateAssignment(int id, int assignNumb, int points)
  {
    StudentType *tempStudent = headStudent;
    bool found = false;
    while (tempStudent != NULL && !found)
    {
      if (id == tempStudent->id)
      {
        Assignment *tempAssignment = tempStudent->headProgramingAssigment;
        while (tempAssignment != NULL)
        {
          if (tempAssignment->AssignmentNumber == assignNumb)
          {
            tempAssignment->AssignmentScoredPoints = points;
            tempStudent->finalProgramingAssigmentGrades = 0;
            Assignment *tempAssignment = tempStudent->headProgramingAssigment; // go through all of the tests and add the scored tests together
            while (tempAssignment != NULL)
            {
              tempStudent->finalTestGrades += tempAssignment->AssignmentScoredPoints; // add up all of the test grades
            }

            break;
          }
          tempAssignment = tempAssignment->next;
        }
        found = true;
      }
      tempStudent = tempStudent->next;
    }
  }
  void searchByIdAndUpdateTest(int id, int assignNumb, int points)
  {
    StudentType *tempStudent = headStudent;
    bool found = false;
    while (tempStudent != NULL && !found)
    {
      if (id == tempStudent->id)
      {
        Assignment *tempTest = tempStudent->headTest;
        while (tempTest != NULL)
        {
          if (tempTest->AssignmentNumber == assignNumb)
          {
            tempTest->AssignmentScoredPoints = points;
            tempStudent->finalTestGrades = 0;             // reset the test grades
            Assignment *tempTest = tempStudent->headTest; // go through all of the tests and add the scored tests together
            while (tempTest != NULL)
            {
              tempStudent->finalTestGrades += tempTest->AssignmentScoredPoints; // add up all of the test grades
            }
            break;
          }
          tempTest = tempTest->next;
        }
        found = true;
      }
      tempStudent = tempStudent->next;
    }
  }
  void searchByIdAndUpdateFinalExam(int id, int assignNumb, int points)
  {
    StudentType *tempStudent = headStudent;
    bool found = false;
    while (tempStudent != NULL && !found)
    {
      if (id == tempStudent->id)
      {
        Assignment *tempFinalExam = tempStudent->headFinalExam;
        while (tempFinalExam != NULL)
        {
          if (tempFinalExam->AssignmentNumber == assignNumb)
          {
            tempFinalExam->AssignmentScoredPoints = points;
            tempStudent->finalExamGrades = points;
            break;
          }
          tempFinalExam = tempFinalExam->next;
        }
        found = true;
      }
      tempStudent = tempStudent->next;
    }
  }
};

int main()
{
  SemesterProgram *semester;
  cout << "Welcome to the Instructor Book Version 1.0" << endl;
  string message = "Please choose one of the following:\Enter N to set up a new semester.\Enter A to add a new student.\Enter P to record programming assignment grade for all students.\Enter T to record test grade for all students.\Enter F to record Final exam grade for all students.\nEnter C to change a grade for a particular student.\nEnter G to Calculate final grade.\nEnter Output the grade data, ordered alphabetically by name (last name/first name) or by student number (in increasing order).\nEnter Q to Quit";
  while (true)
  {
    cout << message << ": ";
    cin >> letter;
    if (letter == 'S')
    {
      int programingAssiments;
      int test;
      int finalEx;
      int programingAssimentsP;
      int testP;
      int finalExP;
      cout << "Please enter a # of programing Assignments for this semester: Range: (0-6)";
      cin >> programingAssiments;
      cout << "\nPlease enter a # of tests for this semester: Range: (0-4) ";
      cin >> test;
      cout << "Please enter a # of final exams for this semester: Range: (0-1)";
      cin >> finalEx;
      cout << "Please enter an iterger to represent the percentage that programing Assignments will account for this semester : ";
      cin >> programingAssimentsP;
      cout << "Please enter an iterger to represent the percentage that programing Assignments will account for this semester : ";
      cin >> testP;
      cout << "Please enter an iterger to represent the percentage that programing Assignments will account for this semester : ";
      cin >> finalExP;

      semester = new SemesterProgram(programingAssiments, test, finalEx, programingAssimentsP, testP, finalExP);
      int temp;
      int tempTotal;
      for (int i = 0; i < programingAssiments; i++)
      {
        cout << "Please enter how many points assignment " << i + 1 << " is ";
        cin >> temp;
        tempTotal += temp;
      }
      semester->programingAssignmentsTotal = tempTotal;

      for (int i = 0; i < test; i++)
      {
        cout << "Please enter how many points test " << i + 1 << " is ";
        cin >> temp;
        tempTotal += temp;
      }
      semester->testsTotal = tempTotal;

      for (int i = 0; i < test; i++)
      {
        cout << "Please enter how many points Final Exam " << i + 1 << " is ";
        cin >> temp;
        tempTotal += temp;
      }
      semester->finalExamTotal = tempTotal;
    }
    if (letter == 'A')
    {
      string firstName;
      string lastName;
      cout << "Please enter student name (at most 20 character): ";
      cin >> firstName;
      cout << "Please enter student name (at most 20 character): ";
      cin >> lastName;
      semester->AddStudent(firstName, lastName);
    }
    if (letter == 'P')
    {
      int AssigmentNumber;
      int points;
      int studentId;
      cout << "Welcome to the programing assignment options: " << endl;
      cout << "Please indicate which programing assignment would you like to record" << endl;
      cin >> AssigmentNumber;
      if (AssigmentNumber >= 0 && AssigmentNumber <= semester->programingAssignments)
      {
        cout << "This is the list of current students:  " << endl;
        semester->printStudents();
        cout << "Please input the id of the student for which you would like to input a grade: ";
        cin >> studentId;
        cout << "Please input the grade points: ";
        cin >> points;
        semester->searchByIdAndUpdateAssignment(studentId, AssigmentNumber, points);
      }
      else
        cout << "The input: " << AssigmentNumber << "is invalid for the range of programing assignments";
    }
    if (letter == 'T')
    {
      int testNumber;
      int points;
      int studentId;
      cout << "Welcome to the test assignment options: " << endl;
      cout << "Please indicate which test assignment would you like to record" << endl;
      cin >> testNumber;
      if (testNumber >= 0 && testNumber <= semester->tests)
      {
        cout << "This is the list of current students:  " << endl;
        semester->printStudents();
        cout << "Please input the id of the student for which you would like to input a grade: ";
        cin >> studentId;
        cout << "Please input the grade points: ";
        cin >> points;
        semester->searchByIdAndUpdateTest(studentId, testNumber, points);
      }
      else
        cout << "The input: " << testNumber << "is invalid for the range of tests for this semester";
    }
    if (letter == 'F')
    {
      int finalExamNumber;
      int points;
      int studentId;
      cout << "Welcome to the fina exam options: " << endl;
      cout << "Please indicate which final exam would you like to record" << endl;
      cin >> finalExamNumber;
      if (finalExamNumber >= 0 && finalExamNumber <= semester->finalExam)
      {
        cout << "This is the list of current students:  " << endl;
        semester->printStudents();
        cout << "Please input the id of the student for which you would like to input a grade: ";
        cin >> studentId;
        cout << "Please input the grade points: ";
        cin >> points;
        semester->searchByIdAndUpdateFinalExam(studentId, finalExamNumber, points);
      }
      else
        cout << "The input: " << finalExamNumber << "is invalid for the range of final exams";
    }
    if (letter == 'C')
    {
      int studentId;
      int newGrade;
      char type;
      cout << "You are about to change a grade;" << endl;
      cout << "Please introduce the student id: ";
      cin >> studentId;
      cout << "Please introduce the new grade: ";
      cin >> newGrade;
      cout << "Please indicate the type of grade you would like to change: P for programing assignment, T for test and F for final exam: ";
      cin >> type;
      if (type == 'P')
      {
        int assigmnentNumber;
        cout << "Please indicate which programing assigment number would you like to change: ";
        cin >> assigmnentNumber;
        semester->searchByIdAndUpdateAssignment(studentId, assigmnentNumber, newGrade);
      }
      if (type == 'T')
      {
        int assigmnentNumber;
        cout << "Please indicate which test number you would you like to change: ";
        cin >> assigmnentNumber;
        semester->searchByIdAndUpdateTest(studentId, assigmnentNumber, newGrade);
      }
      if (type == 'F')
      {
        int assigmnentNumber;
        cout << "Please indicate the final exam number that you would like to change: ";
        cin >> assigmnentNumber;
        semester->searchByIdAndUpdateFinalExam(studentId, assigmnentNumber, newGrade);
      }
    }
    if (letter == 'G')
    {
      int studentId;
      cout << "Please enter the student id for which you would like to calculate final grade: ";
      cin >> studentId;
      semester->CalculateAndSetStudentFinalGrade(studentId);
    }
    if (letter == 'O')
    {
      cout << "This are the student grades: ";
      semester->ShowGrades();
    }
    if (letter = 'Q')
    {
      // SAVE THE CONTENT INTO A FILE.
      // DESTROY ALL NODES.
      break;
    }
  }
}