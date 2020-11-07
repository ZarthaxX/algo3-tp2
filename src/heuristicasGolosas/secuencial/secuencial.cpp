#include <iostream>
#include <vector>

#include "Secuencial.h"

using namespace std;

namespace Secuencial{
    
    pair<Score,Coloring> secuencial(AdyacencyMatrix& G, AdyacencyMatrix& H){

        return make_pair(-1,Coloring(G.size(),-1));
    }
    
}