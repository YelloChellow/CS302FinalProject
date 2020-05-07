#include <cstdlib>
#include <string>

#ifndef _NODE_
#define _NODE_

// Node Class, will be used to for Adjancey List
// Not yet used in implementation, will address.
// Needs Work, should track a head and whatever.
class Node{
public:
    int key;
    
    Node *next;
    Node(int);
};

#include "Node.cpp"
#endif