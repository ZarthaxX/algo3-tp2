#include <iostream>
#include <vector>
#include <queue>

#include "expansivo.h"

using namespace std;

namespace Expansivo{

    /*
        mientras haya nodos sin pintar:

    seleccionar nodo con mayor cantidad de vecinos sin pintar y que no haya sido pintado del grafo H

    correr un bfs en el grafo 2 desde este que pinte a todos los nodos que pueda con un color nuevo sin generar conflictos en el grafo 1
    */

    Node getNextNode(Graph& G,Graph& H,Coloring& coloring){
        
        Node bestNode = -1;
        int bestNodeNeighbourCount = -1;

        for(Node n = 0;n < G.getNodeCount();n++){
            if(coloring[n] == NO_COLOR){
                int nodeNeighbourCount = 0;
                
                for(Node adyNodeH : H.adyacents(n)){
                    if(!G.isAdyacent(n,adyNodeH) &&
                       coloring[adyNodeH] == NO_COLOR){
                        nodeNeighbourCount++;
                    }
                }

                if(nodeNeighbourCount > bestNodeNeighbourCount){
                    bestNode = n;
                    bestNodeNeighbourCount = nodeNeighbourCount;
                }
            }
        }

        return bestNode;
    }

    int BFS(Graph& G,Graph& H,Coloring& coloring,Node node,Color color){
        int coloredNodes = 0;

        vector<bool> seenNodes(G.getNodeCount(),false);
        queue<Node> nodes;
        coloring[node] = color;
        coloredNodes++;
        nodes.push(node);

        while(nodes.size() > 0){
            Node actualNode = nodes.front();

            for(Node adyNodeH : H.adyacents(actualNode)){
                if(coloring[adyNodeH] == NO_COLOR &&
                   colorIsValid(G,coloring,adyNodeH,color)){
                    coloring[adyNodeH] = color;
                    coloredNodes++;
                    nodes.push(adyNodeH);
                }
            }

            nodes.pop();
        }

        return coloredNodes;
    }

    Coloring expansivo(Graph& G, Graph& H){
        int n = G.getNodeCount();

        int coloredNodes = 0;
        int colorsUsed = 0;
        Coloring coloring(n,NO_COLOR);

        while(coloredNodes < n){
            Node node = getNextNode(G,H,coloring);
            coloredNodes += BFS(G,H,coloring,node,colorsUsed);
            colorsUsed++;
        }

        return coloring;
    }

}
