#include "Node.h"

Node::Node(Node *next = nullptr, int value = -1)
{
    this->next = next;
    this->value = value;
}

void Node::set_next(Node *next)
{
    this->next = next;
}

void Node::set_value(int value)
{
    this->value = value;
}

Node *Node::get_next()
{
    return this->next;
}

int Node::get_value()
{
    return this->value;
}
