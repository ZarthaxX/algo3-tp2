#pragma GCC optimize "Ofast,omit-frame-pointer,inline"
#pragma GCC option("arch=native", "tune=native", "no-zero-upper")

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <map>

#include "heuristicasGolosas/bruteforcer/bruteforcer.h"
#include "heuristicasGolosas/expansivo/expansivo.h"
#include "heuristicasGolosas/secuencial/secuencial.h"
#include "tabuSearch/tabuSearch.h"
#include "types.h"
#include "coloringScoreVerifier/coloringScoreVerifier.h"

using namespace std;


int getColoringScore(Graph& graph, Coloring& responseColoring){

    int n = graph.getNodeCount();

    Score score = 0;

    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if( graph.isAdyacent(i,j) &&
                responseColoring[i] == responseColoring[j]){
                    score++;
            }
        }
    }

    return score;
}


int main(int argc, char** argv)
{	
	map<string, string> algoritmos_implementados = {
		{"GE", "Heuristica golosa secuencial"}, 
		{"GS", "Heuristica golosa expansivo"},
		{"GB", "Heuristica golosa bruteforcer"},
		{"TS", "Tabu Search"}
    };

	if (argc < 2 || algoritmos_implementados.find(argv[1]) == algoritmos_implementados.end())
	{
		if(argc>=2)
			cerr << "Algoritmo no encontrado: " << argv[1] << endl;
			
		cerr << "Los algoritmos existentes son: " << endl;
		for (auto& alg_desc: algoritmos_implementados) 
			cerr << "\t- " << alg_desc.first << ": " << alg_desc.second << endl;
		return 0;
	}
    
	string algoritmo = argv[1];

    int n, mG, mH;
    
    cin >> n >> mG >> mH;

    Graph graphG(n);
    Graph graphH(n);

    for(int g = 0; g < 2; g++){

        Graph& graph = (g == 0) ? graphG : graphH;
        int m = (g == 0) ? mG : mH;

        for(int e = 0; e < m; e++){

            int i, j;
            cin >> i >> j;
            i--;j--;
            graph.addEdge(i,j);
        }
    }

    Coloring coloring;

    if(algoritmo == "GS"){
        coloring = Secuencial::secuencial(graphG,graphH);
    }else if(algoritmo == "GE"){
        coloring = Expansivo::expansivo(graphG,graphH);
    }else if(algoritmo == "GB"){
        coloring = Bruteforcer::bruteforcer(graphG,graphH);
    }else if(algoritmo == "TS"){
        coloring = TabuSearch::tabuSearch(graphG,graphH);
    }

    ColoringScoreVerifier::verify(graphG,graphH,coloring);

    cout << getColoringScore(graphH, coloring) << endl;

    for(int v : coloring){
        cout << v << " ";
    }
    cout << endl;

    return 0;
}