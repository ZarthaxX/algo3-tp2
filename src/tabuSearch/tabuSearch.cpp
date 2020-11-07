#include <iostream>
#include <vector>

#include "tabuSearch.h"

using namespace std;

namespace TabuSearch{

    pair<Score,Coloring> tabuSearch(AdyacencyMatrix& G, AdyacencyMatrix& H){
        
        return make_pair(-1,Coloring(G.size(),-1));
    }

}