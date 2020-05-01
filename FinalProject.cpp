#include <cstdlib>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <vector>
#include <string>

//Given Miles per gallon
//Nevada Gas Price - 2.324
//MAX used for making arrays
#define MPG 40
#define NPG 2.324
#define MAX 100

const char *cities[5] = {"Reno", 
                        "Salt Lake City", 
                        "Las Vegas", 
                        "San Fransico", 
                        "Seattle"};    


class EdgeNode{
    public:
        int key;
        int weight;
        EdgeNode *next;
        EdgeNode(int);
        EdgeNode(int, int);
};

EdgeNode::EdgeNode(int key){
    this->key = key;
    this->weight = 0;
    this->next = NULL;
}

EdgeNode::EdgeNode(int key, int weight){
    this->key = key;
    this->weight = weight;
    this->next = NULL;
}
class Node{
public:
    int key;
    Node *next;
    Node(int);
};
Node::Node(int key){
    this->key = key;
    this->next = NULL;
}

class WeightedGraph{
private: 
    static const size_t vertexs = 5;

public:
    int adjMatrix[vertexs][vertexs];

    bool directed;
    Node **head;
    EdgeNode *edges[MAX];
    WeightedGraph(bool);

    int tsp(int tspPath[], int start);
    void printConnections();
    void printMatrix();
    void matrix();
    void addEdge(int x, int y, int weight, bool directed);
    int dijkstraPath(int end, int start);
};
WeightedGraph::WeightedGraph(bool directed){
    this->directed = directed;

    for(int i = 0; i < 9; i++){
        this->edges[i] = NULL;
    }
}

void WeightedGraph::addEdge(int x, int y, int weight, bool directed){


    if(x+1 > 0 && x < vertexs + 1 && y+1 > 0 && y <vertexs +1){
        EdgeNode *edge = new EdgeNode(y, weight);
        edge->next = this->edges[x];
        this->edges[x] = edge;

            if(!directed){
                addEdge(y, x, weight, true);
            }
    }
}

int WeightedGraph::tsp(int tspPath[], int start){
    std::vector<int> vertex;
    for(int i = 0; i < vertexs; i++){
        if (i != start)
            vertex.push_back(i);
    }
        int tempArr[vertexs];
        int minPath = INT_MAX;
        
        std::ofstream out;
        out.open("FinalProjectText.txt");
        out<< "OUTPUT OF ALL PATHS AND MILES:\n\n";

        do{
            int currPathWeight = 0;

            int temp = start;
            out<< cities[temp]<< " -> ";
            for (int i = 0; i <vertex.size()+1; i++){
                currPathWeight += adjMatrix[temp][vertex[i]];
                temp = vertex[i];
                tempArr[i] = temp;           
            }
            currPathWeight += adjMatrix[temp][start];

            for(int i = 0;i < vertexs-1;i++){
                if( i == vertexs-2)
                    out<< cities[tempArr[i]]<< " -> ";
                else
                    out<< cities[tempArr[i]] << " -> ";
            }
            out<< cities[temp];

            out<<  "\tMiles - "<< currPathWeight <<std::endl;

            minPath = std::min(minPath, currPathWeight);
            if(minPath == currPathWeight){
                for(int i = 0; i < vertexs-1;i++){
                    tspPath[i] = tempArr[i];
                }
            }
        }while(next_permutation(vertex.begin(), vertex.end()));        
   out.close();
return minPath;
}

void WeightedGraph::printMatrix(){
    std::cout << std::setw(18)<<" "<<"City x City Matrix by miles\n\n";
    std::cout << std::setw(20) << " " << std::setw(5) << "Reno"<< std::setw(5) << "SLC"
              << std::setw(7) << "LV" << std::setw(7) << "SF" << std::setw(10) << "Seattle" << std::endl;
    std::cout << "    " << std::setfill('-')<< std::setw(52)<<" \n"<<std::setfill(' ');
    for(int i = 0;i < vertexs; i++){
        std::cout << std::setw(16) <<cities[i];
        for(int j =0; j < vertexs;j++){
            std::cout<<" - "<< std::setw(4) << adjMatrix[j][i];
        }
        std::cout<< "\n";
    }
}
void WeightedGraph::matrix(){
    int tempNum, tracker = 0;
    int connection = 10;

    for(int i = 0; i < (5); i++){
        if(this->edges[i] != NULL){
                adjMatrix[tracker][i] = 0;
                connection -= i;
                EdgeNode *curr = this->edges[i];
                while(curr != NULL){
                    connection -= curr->key;
                    adjMatrix[curr->key][i] = curr->weight;
                    curr = curr->next;
                }
                if(connection != 0){
                tempNum = dijkstraPath(connection, i);
                adjMatrix[connection][i] = tempNum;
                }
        }
    connection = 10;
    tracker++;
    }    
}
void WeightedGraph::printConnections(){

    for(int i = 0; i < vertexs; i++){
        if(this->edges[i] != NULL){
            std::cout << std::setw(10) << cities[i] << " connects to: \n";
            EdgeNode *curr = this->edges[i];
            while(curr != NULL){
                std::cout <<std::setw(14) << cities[curr->key] << " distance - " << curr->weight << " miles"<< std::endl;
                curr = curr->next;
            }
            std::cout<<std::endl;
        }
    }
}

int WeightedGraph::dijkstraPath(int end, int start){

    bool mark[MAX];
    int distance[MAX];
    int parent[MAX];
    EdgeNode *curr;
    int currVertice, linkVertice, weight, minPath;

        for(int i = 0; i < (MAX); i ++){
            mark[i] = false;
            distance[i] = INT_MAX;
            parent[i] = -1;
        }

    distance[start] = 0;
    currVertice = start;

    while(mark[currVertice] == false){

        mark[currVertice] = true;
        curr = this->edges[currVertice];

        while(curr != NULL){

            linkVertice = curr->key;
            weight = curr->weight;

            if((distance[currVertice] + weight) < distance[linkVertice]){
                distance[linkVertice] = distance[currVertice] + weight;
                parent[linkVertice] = currVertice;
            }
            curr = curr->next;
        }

        //Changes current vertice to vertice with shortest distance.
        minPath = INT_MAX;
        for(int i = 0; i < (MAX); i ++){
            if(!mark[i] && (distance[i] < minPath)){
                currVertice = i;
                minPath = distance[i];
            }
        }
    }

return distance[end];
  
}
void tspPrint(int tspPath[], int miles, int vertexs){

    std::cout << "\n\nMinimial cost path: " << cities[0] <<" -> ";
    for(int i =0; i < vertexs-1; i++){
        if(i == vertexs-2)
            std::cout << cities[tspPath[i]] << " -> " << cities[0];
        else{
            std::cout << cities[tspPath[i]] << " -> ";
        }

    }
    std::cout << "\nMiles: " << miles;
    std::cout << "\nGallons of gas (40 mpg): " << miles/MPG;
    std::cout << "\nCost using Nevada average per gallon (2.324): " << (miles/MPG)*NPG<<std::endl;

    std::ofstream out;
    out.open ("FinalProjectText.txt", std::ios::out | std::ios::app);
        
        out << "\n\nMinimial cost path: " << cities[0] <<" -> ";
        for(int i =0; i < vertexs-1; i++){
            if(i == vertexs-2)
                out << cities[tspPath[i]] << " -> " << cities[0];
            else{
                out << cities[tspPath[i]] << " -> ";
            }

        }
        out << "\nMiles: " << miles;
        out << "\nGallons of gas (40 mpg): " << miles/MPG;
        out << "\nCost using Nevada average per gallon (2.324): " << (miles/MPG)*NPG<<std::endl;

    out.close();

}

int main(){

WeightedGraph *work = new WeightedGraph(false);

// 0 - Reno, 1 - Salt Lake City, 2 - Las Vegas, 3 - San Fran, 4 - Seattle 
work->addEdge(0, 1, 518, false);
work->addEdge(0, 2, 444, false);
work->addEdge(0, 3, 218, false);
work->addEdge(0, 4, 704, false);
work->addEdge(1, 4, 841, false);
work->addEdge(2, 3, 571, false);
work->addEdge(2, 1, 420, false);
work->addEdge(3, 4, 808, false);


work->printConnections();
work->matrix();
work->printMatrix();
// 0 - Reno
int tspPath[5];
int tspMiles = work->tsp(tspPath, 0);
tspPrint(tspPath, tspMiles, 5);

}