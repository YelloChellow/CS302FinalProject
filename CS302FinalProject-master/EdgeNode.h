
#ifndef _EDGE_NODE
#define _EDGE_NODE

#include "Node.h"

// MAX is for default array sizes
#define MAX 100

// EdgeNode Class will connect node to node
// Stores key(ex: 0, 1, 2, 3)
// Stores Weight(mileage)
// Needs getters and setters
class EdgeNode{
    public:
        int key;
        int weight;
        std::string label;
        // For creating nodes, next being the next node in line.
        EdgeNode *next;
        // Constructors for EdgeNodes.
        EdgeNode(int);  // EdgeNode(key)
        EdgeNode(int, int);  // EdgeNode(key, weight)
        EdgeNode(int, int, std::string);  // EdgeNode(key, weight)
	//getters
	int getKey();
	int getWeight();
	std::string getLabel();
	//setters
	void setKey(int newkey);
	void setWeight(int newweight);
	void setLabel(std::string newlabel);
};
#include "EdgeNode.cpp"
#endif