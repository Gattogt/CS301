#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int idCounter = 0;
char letter;

struct Assignment{
  int AssignmentNumber;
  int AssignmentValue;
  char assignmentGrade;
  Assignment *next;
};

class StudentType
{
  public:
    int id;
    int finalStudentGrade;
    int finalProgramingAssigmentGrades;
    int finalTestGrades;
    int finalExamGrades;
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

class SemesterProgram{
  public:
  int programingAssignments;
  int tests;
  int finalExam;
  int programingAssignmentsPercentage;
  int testsPercentage;
  int finalExamPercentage;
  int studentLength;
  StudentType* headStudent;

  SemesterProgram(int pa, int ts, int fe, int paP, int tsP, int feP){
    programingAssignments = pa;
    tests = ts;
    finalExam = fe;
    programingAssignmentsPercentage = paP;
    testsPercentage = tsP;
    finalExamPercentage = feP;
    studentLength = 0;
    headStudent = NULL;
  }
  void ShowProgramingAssigments(int studentId, char type){
    StudentType* temp = headStudent;
    if(type == 'P'){
      cout << "Programing Assignments: \n";
      while (temp != NULL)
      {
        if(temp->id == studentId){
          Assignment* tempAssignment = temp->headProgramingAssigment;
          while(tempAssignment != NULL){
            cout << "Assignment#" << tempAssignment->AssignmentNumber << ": " << tempAssignment->AssignmentValue << endl;
            tempAssignment = tempAssignment->next;
          }
        }
        temp = temp->next;
      }
      cout << "No assignments for this section";
    }
    if(type == 'T'){
      cout << "Test Assignments: \n";
      while (temp != NULL)
      {
        if(temp->id == studentId){
          Assignment* tempAssignment = temp->headTest;
          while(tempAssignment != NULL){
            cout << "Test#" << tempAssignment->AssignmentNumber << ": " << tempAssignment->AssignmentValue << endl;
            tempAssignment = tempAssignment->next;
          }
        }
        temp = temp->next;
      }
      cout << "No assignments for this section";
    }
    if(type == 'F'){
      cout << "Final Test: \n";
      while (temp != NULL)
      {
        if(temp->id == studentId){
          Assignment* tempAssignment = temp->headFinalExam;
          while(tempAssignment != NULL){
            cout << "Test#" << tempAssignment->AssignmentNumber << ": " << tempAssignment->AssignmentValue << endl;
            tempAssignment = tempAssignment->next;
          }
        }
        temp = temp->next;
      }
      cout << "No assignments for this section";
    }
  }
  void ShowGrades(){
    StudentType* temp = headStudent;
    while(temp != NULL){
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
  void CalculateAndSetStudentFinalGrade(int id){
    StudentType* temp = headStudent;
    while(temp != NULL){
      if(temp->id == id)
        temp->finalStudentGrade = (temp->finalExamGrades + temp->finalTestGrades + temp->finalProgramingAssigmentGrades);
      temp = temp->next;
    }
  }
  bool isEmpty(){
    return studentLength == 0;
  }

  void AddStudent(string first, string last){
    StudentType* location = headStudent;
    StudentType* preLoc = NULL;
    while(location != NULL && first.compare(location->firstName) > 0){
      preLoc = location;
      location = location->next;
    }
    StudentType* newStudent = new StudentType(first, last);
    if (preLoc == NULL){
      newStudent->next = headStudent;
      headStudent = newStudent;
    }else{
      newStudent->next = location;
      preLoc->next = newStudent;
    }
    studentLength++;
    // set all assigments into link lists
    int temp = 0;
    while(temp < programingAssignments){
      Assignment* newAssigment = new Assignment;
      newAssigment->AssignmentNumber = temp + 1;
      newAssigment->next = newStudent->headProgramingAssigment;
      newStudent->headProgramingAssigment = newAssigment;
      temp++;
    }
    temp = 0;
    while(temp < tests){
      Assignment* newTest = new Assignment;
      newTest->AssignmentNumber = temp + 1;
      newTest->next = newStudent->headTest;
      newStudent->headTest = newTest;
      temp++;
    }
    temp = 0;
    while(temp < finalExam){
      Assignment* newFinalExam = new Assignment;
      newFinalExam->AssignmentNumber = temp + 1;
      newFinalExam->next = newStudent->headFinalExam;
      newStudent->headFinalExam = newFinalExam;
      temp++;
    }
  }
  void printStudents(){
    StudentType* temp = headStudent;
    while(temp != NULL){
      cout << "First Name: " << temp->firstName << " Last Name: " << temp->lastName << " Id: " << temp->id << endl;
      temp = temp->next;
     } 
   }
   void searchByIdAndUpdateAssignment(int id, int assignNumb, int points){
     StudentType* tempStudent = headStudent;
     bool found = false;
     while (tempStudent != NULL && !found)
     {
      if(id == tempStudent->id){
        Assignment* tempAssignment = tempStudent->headProgramingAssigment;
        while(tempAssignment != NULL){
          if(tempAssignment->AssignmentNumber == assignNumb){
            tempAssignment->AssignmentValue = points;
            tempStudent->finalProgramingAssigmentGrades += points;

            break;
          }
          tempAssignment = tempAssignment->next;
        }
        found = true;
      }
      tempStudent = tempStudent->next;
     }
   }
   void searchByIdAndUpdateTest(int id, int assignNumb, int points){
     StudentType* tempStudent = headStudent;
     bool found = false;
     while (tempStudent != NULL && !found)
     {
      if(id == tempStudent->id){
        Assignment* tempTest = tempStudent->headTest;
        while(tempTest != NULL){
          if(tempTest->AssignmentNumber == assignNumb){
            tempTest->AssignmentValue = points;
            tempStudent->finalTestGrades += points;
            break;
          }
          tempTest = tempTest->next;
        }
        found = true;
      }
      tempStudent = tempStudent->next;
     }
   }
   void searchByIdAndUpdateFinalExam(int id, int assignNumb, int points){
     StudentType* tempStudent = headStudent;
     bool found = false;
     while (tempStudent != NULL && !found)
     {
      if(id == tempStudent->id){
        Assignment* tempFinalExam = tempStudent->headFinalExam;
        while(tempFinalExam != NULL){
          if(tempFinalExam->AssignmentNumber == assignNumb){
            tempFinalExam->AssignmentValue = points;
            tempStudent->finalExamGrades += points;
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

int main(){
  SemesterProgram* semester;
  cout << "Welcome to the Instructor Book Version 1.0" << endl;
  string message = "Please choose one of the following:\Enter N to set up a new semester.\Enter A to add a new student.\Enter P to record programming assignment grade for all students.\Enter T to record test grade for all students.\Enter F to record Final exam grade for all students.\nEnter C to change a grade for a particular student.\nEnter G to Calculate final grade.\nEnter Output the grade data, ordered alphabetically by name (last name/first name) or by student number (in increasing order).\nEnter Q to Quit";
  while (true)
  {
    cout << message<<": ";
    cin >> letter;
    if(letter == 'S'){
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
    }
    if(letter == 'A'){
      string firstName;
      string lastName;
      cout << "Please enter student name (at most 20 character): ";
      cin >> firstName;
      cout << "Please enter student name (at most 20 character): ";
      cin >> lastName;
      semester->AddStudent(firstName, lastName);
    }
    if(letter == 'P'){
      int AssigmentNumber;
      int points;
      int studentId;
      cout << "Welcome to the programing assignment options: " << endl;
      cout << "Please indicate which programing assignment would you like to record" << endl;
      cin >> AssigmentNumber;
      if(AssigmentNumber>=0 && AssigmentNumber<=semester->programingAssignments){
        cout << "This is the list of current students:  " <<endl;
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
    if(letter == 'T'){
      int testNumber;
      int points;
      int studentId;
      cout << "Welcome to the test assignment options: " << endl;
      cout << "Please indicate which test assignment would you like to record" << endl;
      cin >> testNumber;
      if(testNumber>=0 && testNumber<=semester->tests){
        cout << "This is the list of current students:  " <<endl;
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
    if(letter == 'F'){
      int finalExamNumber;
      int points;
      int studentId;
      cout << "Welcome to the fina exam options: " << endl;
      cout << "Please indicate which final exam would you like to record" << endl;
      cin >> finalExamNumber;
      if(finalExamNumber>=0 && finalExamNumber<=semester->finalExam){
        cout << "This is the list of current students:  " <<endl;
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
    if(letter == 'C'){
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
      if(type == 'P'){
        int assigmnentNumber;
        cout << "Please indicate which programing assigment number would you like to change: ";
        cin >> assigmnentNumber;
        semester->searchByIdAndUpdateAssignment(studentId, assigmnentNumber, newGrade);
      }
      if(type == 'T'){
        int assigmnentNumber;
        cout << "Please indicate which test number you would you like to change: ";
        cin >> assigmnentNumber;
        semester->searchByIdAndUpdateTest(studentId, assigmnentNumber, newGrade);
      }
      if(type == 'F'){
        int assigmnentNumber;
        cout << "Please indicate the final exam number that you would like to change: ";
        cin >> assigmnentNumber;
        semester->searchByIdAndUpdateFinalExam(studentId, assigmnentNumber, newGrade);
      }
    }
    if(letter == 'G'){
      int studentId;
      cout << "Please enter the student id for which you would like to calculate final grade: ";
      cin >> studentId;
      semester->CalculateAndSetStudentFinalGrade(studentId);
    }
    if(letter == 'O'){
      cout << "This are the student grades: ";
      semester->ShowGrades();
    }
    if(letter = 'Q'){
      // SAVE THE CONTENT INTO A FILE.
      // DESTROY ALL NODES.
      break;
    }
  }
}