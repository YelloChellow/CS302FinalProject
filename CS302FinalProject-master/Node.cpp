#ifndef _NODE_
#define _NODE_

#include "Node.h"

// Node Constructor with (key) parameter
Node::Node(int key){
    this->key = key;
    this->next = NULL;
}
#endif