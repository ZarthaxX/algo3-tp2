#include <iostream>
#include <vector>

#include "Bruteforcer.h"

using namespace std;

namespace Bruteforcer{
const int INF_INT = 2000000000;

    bool isColorValid(Graph& G,Coloring& coloring,int node, int nodeColor){
        
        for(int adyNode : G.adyacents(node)){
            if(coloring[adyNode]==nodeColor)
                return false;
        }
        return true;
    }

    pair<int,int> heuristicScore(Graph& G, Graph& H, Coloring& coloring,int node, int nodeColor){
        int n = G.getNodeCount();
        
        int impactGain=0;
        int impactLoss=0;

        int neighboursH=0;

        for(int adyNodeH : H.adyacents(node)){
            if(!G.isAdyacent(node,adyNodeH)){
                if(coloring[adyNodeH]==nodeColor){
                    impactGain++;
                }else if(coloring[adyNodeH]!=-1){
                    impactLoss++;
                }
                neighboursH++;
            }
        }

        for(int adyNodeG : G.adyacents(node)){
            if(coloring[adyNodeG]==-1){
                if(!isColorValid(G,coloring,adyNodeG,nodeColor))
                    continue;

                for(int adyNodeH : H.adyacents(adyNodeG)){
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

    pair<int,int> bestNodeColorHeuristic(Graph& G, Graph& H, Coloring& coloring){
        int n = G.getNodeCount();

        int bestNode=-1;
        int bestNodeColor=-1;
        pair<int,int> bestScore(-INF_INT,-INF_INT); //INF

        for(int node=0; node < n; node++){
            if(coloring[node]==-1){
                for(int c=0;c<n;c++){
                    if(!isColorValid(G,coloring,node,c))
                        continue;
                    
                    pair<int,int> score = heuristicScore(G,H,coloring,node,c);

                    if(score>bestScore){
                        bestScore=score;
                        bestNode=node;
                        bestNodeColor=c;
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
            pair<int,int> bestNodeColor = bestNodeColorHeuristic(G,H,coloring);
            coloring[bestNodeColor.first] = bestNodeColor.second;
            coloredNodes++;
        }

        return coloring;
    }

}
