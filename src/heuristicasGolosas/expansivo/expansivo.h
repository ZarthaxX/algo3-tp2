#pragma once

#include <iostream>
#include <vector>
 
#include "../../types.h"

using namespace std;

namespace Expansivo{
    pair<Score,Coloring> expansivo(AdyacencyMatrix& G, AdyacencyMatrix& H);
}