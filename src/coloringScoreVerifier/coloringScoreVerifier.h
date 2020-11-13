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

    static void areAllNodesColored(Graph& graph, Coloring& coloring);
    static void areValidColors(Graph& graph, Coloring& coloring);
    static void isValidColoring(Graph& graph, Coloring& coloring);

    public:

    static void verify(Graph& graphG, Graph& graphH, Coloring responseToVerify);

};
