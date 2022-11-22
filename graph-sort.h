#ifndef __FF83A94B_GRAPH_SORT_H__
#define __FF83A94B_GRAPH_SORT_H__
#include "DFA.h"
#include "graph-sort--util.h"

typedef char label_t;
namespace propagation {
    std::vector<int> sort_graph( const DFA::Graph& G );
}

namespace doubling {
    std::vector<int> sort_graph( const DFA::Graph& G );
}

#endif

