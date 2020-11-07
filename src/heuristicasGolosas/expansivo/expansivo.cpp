#include <iostream>
#include <vector>

#include "Expansivo.h"

using namespace std;

namespace Expansivo{

    pair<Score,Coloring> expansivo(AdyacencyMatrix& G, AdyacencyMatrix& H){

        return make_pair(-1,Coloring(G.size(),-1));
    }

}