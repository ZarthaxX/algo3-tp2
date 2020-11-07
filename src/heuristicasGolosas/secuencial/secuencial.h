#pragma once

#include <iostream>
#include <vector>

#include "../../types.h"

using namespace std;

namespace Secuencial{
    pair<Score,Coloring> secuencial(AdyacencyMatrix& G, AdyacencyMatrix& H);
}