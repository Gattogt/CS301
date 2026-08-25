#include "Linked_List.h"
#include "Node.h"

LinkedList::LinkedList()
{
    this->head = new Node(nullptr, -1);
    this->tail = head;
    this->size = 0;
}

void LinkedList::insert_front(int value)
{
    Node *node = new Node(nullptr, value);
    if (size == 0)
    {
        this->tail = node;
    }
    node->set_next(head->get_next());
    this->head->set_next(node);
    size++;
}

void LinkedList::remove_front()
{
    Node *node = this->head->get_next();
    this->head->set_next(node->get_next());
    node->set_next(nullptr);
    size--;
}

Node *LinkedList::get_front()
{
    return this->head->get_next();
}

void LinkedList::insert_back(int value)
{
    Node *node = new Node(nullptr, value);
    this->tail->set_next(node);
    this->tail = node;
    size++;
}

Node *LinkedList::get_back()
{
    return this->tail;
}

int LinkedList::get_size()
{
    return this->size;
}
