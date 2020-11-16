#include <iostream>
#include <vector>

#include "bruteforcer.h"

using namespace std;

namespace Bruteforcer{
    const int INF_INT = 2000000000;

    bool isColorValid(Graph& G,Coloring& coloring,Node node, Color nodeColor){
        
        for(Node adyNode : G.adyacents(node)){
            if(coloring[adyNode]==nodeColor)
                return false;
        }
        return true;
    }

    pair<float,int> heuristicScore(Graph& G, Graph& H, Coloring& coloring,Node node, Color nodeColor){
        int n = G.getNodeCount();
        
        int impactGain=0;
        int impactLoss=0;

        int neighboursH=0;

        for(Node adyNodeH : H.adyacents(node)){
            if(!G.isAdyacent(node,adyNodeH)){
                if(coloring[adyNodeH]==nodeColor){
                    impactGain++;
                }else if(coloring[adyNodeH]!=-1){
                    impactLoss++;
                }
                neighboursH++;
            }
        }

        for(Node adyNodeG : G.adyacents(node)){
            if(coloring[adyNodeG]==-1){
                if(!isColorValid(G,coloring,adyNodeG,nodeColor))
                    continue;

                for(Node adyNodeH : H.adyacents(adyNodeG)){
                    if(adyNodeH==node)
                        continue;
                    if(!G.isAdyacent(adyNodeG,adyNodeH) && coloring[adyNodeH]==nodeColor){
                        impactLoss++;
                    }
                }
            }
        }

        return make_pair(impactGain-impactLoss, neighboursH);
    }

    pair<Node,Color> bestNodeColorHeuristic(Graph& G, Graph& H, Coloring& coloring){
        int n = G.getNodeCount();

        Node bestNode=-1;
        Color bestNodeColor=-1;
        pair<float,int> bestScore(-INF_INT,-INF_INT); //INF

        for(Node node=0; node < n; node++){
            if(coloring[node]==-1){
                for(Color color=0; color < n; color++){
                    if(!isColorValid(G,coloring,node,color))
                        continue;
                    
                    pair<float,int> score = heuristicScore(G,H,coloring,node,color);

                    if(score>bestScore){
                        bestScore=score;
                        bestNode=node;
                        bestNodeColor=color;
                    }
                }
            }
        }

        return make_pair(bestNode,bestNodeColor);
    }

    Coloring bruteforcer(Graph& G, Graph& H){
        int n = G.getNodeCount();

        Coloring coloring(n,-1);

        int coloredNodes = 0;

        while(coloredNodes < n){
            pair<Node,Color> bestNodeColor = bestNodeColorHeuristic(G,H,coloring);
            coloring[bestNodeColor.first] = bestNodeColor.second;
            coloredNodes++;
        }

        return coloring;
    }

}
