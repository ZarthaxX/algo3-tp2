#include "types.h"

Graph::Graph(int n){
    _matrix = AdyacencyMatrix(n, vector<bool>(n,false));
    _listOfAdyacents = vector<vector<int>>(n,vector<int>());
}

void Graph::addEdge(int node1,int node2){
    _matrix[node1][node2] = true;
    _matrix[node2][node1] = true;
    _listOfAdyacents[node1].push_back(node2);
    _listOfAdyacents[node2].push_back(node1); 
}

bool Graph::isAdyacent(int node1, int node2) const{
    return _matrix[node1][node2];
}

const vector<int>& Graph::adyacents(int node) const{
    return _listOfAdyacents[node];
}