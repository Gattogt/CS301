#include "Number_Bucket.h"
#include "Linked_List.h"
#include <iostream>

Number_Bucket::Number_Bucket()
{
    this->bucket = new LinkedList();
    this->size = 0;
}

Number_Bucket::~Number_Bucket()
{
    delete this->bucket;
    std::cout << "Bucket Successfully Deleted" << std::endl;
}

void Number_Bucket::push(int value)
{
    this->bucket->insert_front(value);
    size++;
}

int Number_Bucket::pop()
{
    int value = this->bucket->get_front()->get_value();
    this->bucket->remove_front();
    size--;
    return value;
}

bool Number_Bucket::isEmpty()
{
    if (size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Number_Bucket::get_size()
{
    return this->size;
}