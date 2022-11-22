#include "DFA.h"
#include "graph-sort.h"
#include <vector>
#include <set>
#include <iostream>

using namespace std;
using DFA::Graph;

int main( void ) {
    Graph G;
    int u, v;
    char l;
    while( cin >> u >> v >> l ) {
        if( !G.add_edge( u, v, l ) ) {
            cerr << "Warning: something wrong in data: " << u << ',' << v << ',' << l << endl;
        }
    }

    // Sort and compute the co-lex rank of nodes
    vector<int> ranks = doubling::sort_graph( G );
    for( int i = 0; i < ranks.size()/2; ++i ) {
        cout << ranks[2*i] << '\t' << ranks[2*i+1] << endl;
    }

    return 0;
}
