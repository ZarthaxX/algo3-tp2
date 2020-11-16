#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include "secuencial.h"

using namespace std;

namespace Secuencial{
    
    Coloring secuencial(Graph& G, Graph& H){

        // Paso 0 ) Ordenar los nodos de mayor a menor grado. DONE
        // Paso 1 ) Recorrer los nodos del grafo G.
        // Paso 2 ) Hay que colorear el nodo en la pos i. Para hacer esto, trato de elegir el color mas usado
        // en la vecindad del nodo H. 
        // Paso 3) Verifico si es valido. Es decir, si no existe ningun vecino en el grafo G con ese color.
        // Paso 4) De ser valido, lo coloco y termino. Sino vuelvo al paso 2) hasta agotar los colores usados en el grafo H.
        // Paso 5) De quedarme sin colores candidatos, eligo el min disponible que no fue usado en la vecindad de G y termino.


        Coloring coloreo = Coloring(G.getNodeCount(),NO_COLOR);
        vector<Node> nodos_a_recorrer = vector<Node>(G.getNodeCount(),-1);
        for(int i = 0;i < nodos_a_recorrer.size();++i){
            nodos_a_recorrer[i] = i;
        };
        sort(nodos_a_recorrer.begin(),nodos_a_recorrer.end(),[&G](Node& nodo1,Node& nodo2){return G.adyacents(nodo1).size() > G.adyacents(nodo2).size();} );
        for(int i = 0;i < nodos_a_recorrer.size();++i){
            Node nodo_actual = nodos_a_recorrer[i];

            // Diccionario de colores adyacentes a cantidad de apariciones en la vecindad de H.
            map<int, int> colores_adyacentes;

            // Ordena los colores mas usados en la vecindad de H del nodo actual.
            for(int j = 0;j < H.adyacents(nodo_actual).size();++j){
                if(colores_adyacentes.find(coloreo[H.adyacents(nodo_actual)[j]]) != colores_adyacentes.end()){
                    colores_adyacentes[coloreo[H.adyacents(nodo_actual)[j]]]++;
                } else {
                    colores_adyacentes[coloreo[H.adyacents(nodo_actual)[j]]] = 1;
                }
            };
            vector<pair<int, int> > vector_colores_adyacentes;
            copy(colores_adyacentes.begin(), colores_adyacentes.end(), back_inserter(vector_colores_adyacentes));
            
            sort(vector_colores_adyacentes.begin(),vector_colores_adyacentes.end(),[](pair<int,int>& color1,pair<int,int>& color2){return color1.second > color2.second;});
            
            // Recorro los colores candidatos de mayor a menor
            for(auto it = vector_colores_adyacentes.begin(); it != vector_colores_adyacentes.end(); ++it){
                if(it->first != NO_COLOR){
                    bool canColor = colorIsValid(G,coloreo,nodo_actual,it->first);
                    if(canColor){
                        coloreo[nodo_actual] = it->first;
                        break;
                    }
                }       
            }

            // Si llegamos aca: termine de recorrer la lista de colores o es vacia.
            
            if(coloreo[nodo_actual] == NO_COLOR){
                int color = 0;
                while(!colorIsValid(G,coloreo,nodo_actual,color)){color++;}
                coloreo[nodo_actual] = color;
            }
        }

        // Termine de recorrer todos los nodos.
    return coloreo;
    };
}