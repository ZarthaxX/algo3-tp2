#pragma once

#include <iostream>
#include <vector>

#include "../types.h"

using namespace std;

namespace TabuSearch{
    pair<Score,Coloring> tabuSearch(AdyacencyMatrix& G, AdyacencyMatrix& H);
}