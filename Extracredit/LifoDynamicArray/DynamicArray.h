#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Node.h"

class DynamicArray{
  private:
    int length;
    Node* top;

  public:
    DynamicArray();
    void printValues();

    void push(int value);
    int pop();

    bool isEmpty();
};
#endif