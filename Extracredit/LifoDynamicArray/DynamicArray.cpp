#include <iostream>
#include "Node.h"
#include "DynamicArray.h"
using namespace std;

    DynamicArray::DynamicArray(){
      Node* newNode = new Node(-1);
      this->top = newNode;
      length = 1;
    }
    void DynamicArray::printValues(){
      Node* node = this->top->next;
      while (node != nullptr)
      {
        cout << "Node#: " << node->value << "\n";
        node = node->next;
        // if(node->next == nullptr){
        //   cout << "Node#: " << node->value << "\n";
        // }
      }
    }
    void DynamicArray::push(int value){
      Node* newNode = new Node(value);
      newNode->next = this->top->next;
      this->top->next = newNode;
      this->length = length + 1;
    }
    int DynamicArray::pop(){
      int returnValue = top->next->value;
      this->top->next = this->top->next->next;
      this->length = length - 1;
      return returnValue;
    }
    bool DynamicArray::isEmpty(){
      if(top->next == nullptr){
        cout << "this array is empty \n";
        return true;
      }
      cout << "candy \n";
      return false;
    }

