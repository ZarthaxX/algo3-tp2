#pragma GCC optimize "Ofast,omit-frame-pointer,inline"
#pragma GCC option("arch=native", "tune=native", "no-zero-upper")

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <chrono>
#include <set>

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
		{"GS", "Heuristica golosa secuencial"},
		{"GE", "Heuristica golosa expansivo"}, 
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
    int longitud_tabu = 0;
    string tipo_memoria = "none";
    int porcentaje_vecindad = 0;
    int iteraciones = 0;
    string goloso_inicial = "GE";
    
    if(algoritmo == "TS"){
        if(argc < 5){
            cerr << "Cantidad de argumentos invalido" << endl;
            return 0;
        }

        longitud_tabu = atoi(argv[2]);
        tipo_memoria = string(argv[3]);
        porcentaje_vecindad = atoi(argv[4]);
        iteraciones = atoi(argv[5]);
        if(argc>=7){
            goloso_inicial = argv[6];
        }
    }
    
    bool memoryOfSolutions = (tipo_memoria == "soluciones");
    
    int n, mG, mH;
    
    cin >> n >> mG >> mH;

    Graph graphG(n);
    Graph graphH(n);

    for(int g = 0; g < 2; g++){

        Graph& graph = (g == 0) ? graphG : graphH;
        int m = (g == 0) ? mG : mH;

        for(int e = 0; e < m; e++){

            Node i, j;
            cin >> i >> j;
            i--;j--;
            graph.addEdge(i,j);
        }
    }

    Coloring coloring;

	stopwatch.Start();
    long long tiempo_mejor_solucion = 0;
    if(algoritmo == "GS"){
        coloring = Secuencial::secuencial(graphG,graphH);
    }else if(algoritmo == "GE"){
        coloring = Expansivo::expansivo(graphG,graphH);
    }else if(algoritmo == "GB"){
        coloring = Bruteforcer::bruteforcer(graphG,graphH);
    }else if(algoritmo == "TS"){
        coloring = TabuSearch::tabuSearch(graphG,graphH,longitud_tabu,porcentaje_vecindad,memoryOfSolutions,iteraciones, goloso_inicial, tiempo_mejor_solucion);
    }

	auto totalTime = stopwatch.EllapsedMicroseconds();
    
    ColoringScoreVerifier::verify(graphG,graphH,coloring);

    clog <<  totalTime << " "
         << getColoringScore(graphH, coloring) << " "
         << set<int>(coloring.begin(), coloring.end()).size() << " "
         << longitud_tabu << " "
         << tipo_memoria << " "
         << porcentaje_vecindad << " "
         << tiempo_mejor_solucion << endl;

    for(Color v : coloring){
        clog << v << " ";
    }
    clog << endl;

    return 0;
}