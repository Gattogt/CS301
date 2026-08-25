#ifndef NUMBER_BUCKET_H
#define NUMBER_BUCKET_H
#include "Linked_List.h"

class Number_Bucket
{
private:
    LinkedList *bucket;
    int size;

public:
    Number_Bucket();
    //~Number_Bucket();
    void push(int value);
    int pop();
    bool isEmpty();
    int get_size();
};

#endif