#include "types.h"

Graph::Graph(int n){
    _matrix = AdyacencyMatrix(n, vector<bool>(n,false));
    _listOfAdyacents = vector<vector<int>>(n,vector<int>());
}

int Graph::getNodeCount() const{
    return _matrix.size();
}

void Graph::addEdge(Node node1,Node node2){
    _matrix[node1][node2] = true;
    _matrix[node2][node1] = true;
    _listOfAdyacents[node1].push_back(node2);
    _listOfAdyacents[node2].push_back(node1); 
}

bool Graph::isAdyacent(Node node1, Node node2) const{
    return _matrix[node1][node2];
}

const vector<int>& Graph::adyacents(Node node) const{
    return _listOfAdyacents[node];
}

//Funciones auxiliares

bool colorIsValid(Graph& G,Coloring& colors,Node node,int c){
    bool validColor = true;
    for(auto it = G.adyacents(node).begin(); it != G.adyacents(node).end(); ++it){
        validColor = validColor && (colors[*it] != c);
    }
    return validColor;
};