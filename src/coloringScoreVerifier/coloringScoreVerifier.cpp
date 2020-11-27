#include "coloringScoreVerifier.h"

void ColoringScoreVerifier::areAllNodesColored(Graph& graph, Coloring& responseColoring){

    int n = graph.getNodeCount();

    if(n != responseColoring.size()){
        throw runtime_error(to_string(responseColoring.size()) + " nodes are colored but there are " + to_string(n) + " in total.");
    }
}

void ColoringScoreVerifier::areValidColors(Graph& graph, Coloring& responseColoring){

    int n = graph.getNodeCount();

    for(int color : responseColoring){
        if(!(0 <= color && color < n)){
            throw runtime_error("Color " + to_string(color) + " is not valid.");
        }
    }
}

void ColoringScoreVerifier::isValidColoring(Graph& graph, Coloring& responseColoring){

    int n = graph.getNodeCount();

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if( graph.isAdyacent(i,j) &&
                responseColoring[i] == responseColoring[j]){
                    throw runtime_error("Nodes " + to_string(i) + " and " + to_string(j) + " are adyacent and use the same color.");
            }
        }
    }
}

void ColoringScoreVerifier::verify(Graph& graphG, Graph& graphH, Coloring responseToVerify){

    Coloring& responseColoring = responseToVerify;

    int n = graphG.getNodeCount();
    //cerr<<"Response: ";for(Color c : responseColoring)cerr << c << " ";cerr<<endl;
    areAllNodesColored(graphG, responseColoring);
    areValidColors(graphG, responseColoring);
    isValidColoring(graphG, responseColoring);
}
