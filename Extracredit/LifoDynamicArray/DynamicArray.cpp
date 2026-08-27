#include <iostream>
using namespace std;
class Node{
  public:
    int value;
    Node* next;

    Node(int value){
      this->value = value;
      this->next = nullptr;
    }
};
class DynamicArray{
  private:
    int length;
    Node* top;
    Node* bottom;

  public:
    DynamicArray(int value){
      Node* newNode = new Node(value);
      this->top = newNode;
      length = 1;
    }
    void printValues(){
      while(top->next != nullptr){
        cout << "Node#: " << top->value << "\n";
        top = top->next;
        if(top->next == nullptr){
          cout << "Node#: " << top->value << "\n";
        }
      }
    }
    void push(int value){
      Node* newNode = new Node(value);
      newNode->next = this->top->next;
      top->next = newNode;
      this->length = length + 1;
    }
    int pop(){
      int returnValue = top->value;
      Node* popedNode = new Node(returnValue);
      this->top = this->top->next;
      this->length = length - 1;
      if(popedNode->next == nullptr){
        top->next = nullptr;
      }
      return returnValue;
    }
    bool isEmpty(){
      if(top->next == nullptr){
        return true;
      }
      return false;
    }
};
int main(){

  DynamicArray* array = new DynamicArray(4);
  array->push(5);
  array->push(60);
  array->push(65);
  array->push(86);
  array->push(1964);
  array->printValues();
  array->pop();
  array->printValues();
}