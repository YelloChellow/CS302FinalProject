#ifndef _EDGE_NODE_
#define _EDGE_NODE_

#include "EdgeNode.h"

// Constucter with (key) parameter
EdgeNode::EdgeNode(int key){
    this->key = key;
    this->weight = 0;
    this->label = "N/A";
    this->next = NULL;    // Sets next null location to NULL
}
// Constructor with (key, weight) parameter
EdgeNode::EdgeNode(int key, int weight){
    this->key = key;
    this->weight = weight;
    this->label = "N/A";
    this->next = NULL;    // Sets next location to NULL
}

// Constructor with (key, weight) parameter
EdgeNode::EdgeNode(int key, int weight, std::string L){
    this->key = key;
    this->weight = weight;
    this->label = L;
    this->next = NULL;    // Sets next location to NULL
}

#endif