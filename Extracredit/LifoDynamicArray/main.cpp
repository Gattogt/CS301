#include "DynamicArray.h"
#include <iostream>
using namespace std;
int main()
{

  DynamicArray* array = new DynamicArray();
  array->push(5);
  array->push(60);
  array->push(65);
  array->push(86);
  array->push(1964);
  array->printValues();
  array->pop();
  array->pop();
  array->pop();
  array->pop();
  array->pop();
  array->printValues();
  cout << "\n"<< array->isEmpty();
}