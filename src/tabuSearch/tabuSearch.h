#pragma once

#include <iostream>
#include <vector>

#include "../types.h"

using namespace std;

namespace TabuSearch{
    Coloring tabuSearch(Graph& G, Graph& H);
}