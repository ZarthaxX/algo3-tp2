#include "coloringScoreVerifier.h"

void ColoringScoreVerifier::areAllNodesColored(AdyacencyMatrix& graph, Coloring& responseColoring){

    int n = graph.size();

    if(n != responseColoring.size()){
        throw runtime_error(to_string(responseColoring.size()) + " nodes are colored but there are " + to_string(n) + " in total.");
    }
}

void ColoringScoreVerifier::areValidColors(AdyacencyMatrix& graph, Coloring& responseColoring){

    int n = graph.size();

    for(int color : responseColoring){
        if(!(0 <= color && color < n)){
            throw runtime_error("Color " + to_string(color) + " is not valid.");
        }
    }
}

void ColoringScoreVerifier::isValidColoring(AdyacencyMatrix& graph, Coloring& responseColoring){

    int n = graph.size();

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(graph[i][j] == true &&
                responseColoring[i] == responseColoring[j]){
                    throw runtime_error("Nodes " + to_string(i) + " and " + to_string(j) + " are adyacent and use the same color.");
            }
        }
    }
}

void ColoringScoreVerifier::isValidScore(AdyacencyMatrix& graph, Coloring& responseColoring, Score responseScore){

    int n = graph.size();

    Score score = 0;

    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(graph[i][j] == true &&
                responseColoring[i] == responseColoring[j]){
                    score++;
            }
        }
    }

    if(score != responseScore){
        throw std::runtime_error("Response score is " + to_string(responseScore) + " but should be " + to_string(score) + ".");
    }
}

void ColoringScoreVerifier::verify(AdyacencyMatrix& graphG, AdyacencyMatrix& graphH, pair<Score,Coloring> responseToVerify){

    Score responseScore = responseToVerify.first;
    Coloring& responseColoring = responseToVerify.second;

    int n = graphG.size();

    areAllNodesColored(graphG, responseColoring);
    areValidColors(graphG, responseColoring);
    isValidColoring(graphG, responseColoring);
    isValidScore(graphH,responseColoring,responseScore);

}
