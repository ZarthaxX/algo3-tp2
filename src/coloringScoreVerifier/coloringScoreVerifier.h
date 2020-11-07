#pragma once

#include <iostream>
#include <vector>
#include <string>

#ifdef __linux__ 
    #include "../types.h"
#else
    #include "..\types.h"
#endif

using namespace std;

class ColoringScoreVerifier{

    private:

    ColoringScoreVerifier(){}

    static void areAllNodesColored(AdyacencyMatrix& graph, Coloring& coloring);
    static void areValidColors(AdyacencyMatrix& graph, Coloring& coloring);
    static void isValidColoring(AdyacencyMatrix& graph, Coloring& coloring);
    static void isValidScore(AdyacencyMatrix& graph, Coloring& coloring, Score responseScore);

    public:

    static void verify(AdyacencyMatrix& graphG, AdyacencyMatrix& graphH, pair<Score,Coloring> responseToVerify);

};
