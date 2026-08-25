#include <iostream>
#include "Number_Bucket.h"

using namespace std;
/*
class Number_bucket{
  private:
    int arr[];

  public:
    Number_bucket(int size){

    }
    ~Number_bucket(){

    }
    void push(int number){

    }
    int pop(){
      return 0;
    }
    bool isEmpty(){

    }
    int getSize(){
      return 0;
    }
};
*/
int main()
{

  Number_Bucket *bucket = new Number_Bucket();

  bucket->push(5);
  bucket->push(3);
  bucket->push(2);

  cout << bucket->pop() << endl;

  delete bucket;

  return 0;
}