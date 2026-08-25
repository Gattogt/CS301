#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "Node.h"

class LinkedList
{
private:
    Node *head;
    Node *tail;
    int size;

public:
    LinkedList();
    ~LinkedList();
    void insert_front(int value);
    void remove_front();
    Node *get_front();
    void insert_back(int value);
    Node *get_back();
    int get_size();
};

#endif