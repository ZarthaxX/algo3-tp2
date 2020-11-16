#include <iostream>
#include <vector>
#include <algorithm>
#include "../../types.h"
#include "secuencial.h"

using namespace std;

int main(){
        Graph G = Graph(3);
        G.addEdge(0,1);
        G.addEdge(0,2);
        Graph H = Graph(3);
        H.addEdge(0,1);
        H.addEdge(1,2);

        Coloring coloreo = Secuencial::secuencial(G,H);

        
        for(int i = 0;i < coloreo.size();i++){
            cout << coloreo[i] << endl;
        };

        
}