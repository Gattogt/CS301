#ifndef NODE_H
#define NODE_H

class Node
{
private:
    Node *next;
    int value;

public:
    Node(Node *next, int value);
    ~Node();
    void set_next(Node *next);
    void set_value(int value);
    Node *get_next();
    int get_value();
};

#endif