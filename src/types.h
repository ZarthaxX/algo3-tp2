#pragma once

#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<bool>> AdyacencyMatrix;
typedef int Score;
typedef vector<int> Coloring;
typedef int Node;
typedef int Color;

class Graph{
    public:
        Graph(int n);
        int getNodeCount() const;
        void addEdge(int node1,int node2);
        bool isAdyacent(int node1,int node2) const;
        const vector<int>& adyacents(int node) const;
    private:
        AdyacencyMatrix _matrix;
        vector<vector<int>> _listOfAdyacents;
};


