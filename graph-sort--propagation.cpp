#include "DFA.h"
#include "graph-sort.h"
#include <vector>
#include <set>

using namespace std;
using DFA::Graph;

namespace doubling {
void init_rank( const Graph& G, vector<int>& Rank, vector<vector<int> >& Ptr );
}

namespace propagation {
    static void init_rank( const Graph& G, vector<int>& Rank, vector<vector<int> >& Ptr ) {
        // Note: each node of the graph is copied into two, each of which corresponds to minimum/maximum suffix.
        // i.e. Rank is the length-2V array storing the rank of min/max incoming labels.
        ::doubling::init_rank( G, Rank, Ptr );
    }

    static vector<int> propagate( const Graph& G, const vector<int>& Rank, vector<vector<int> >& Ptr ) {
        // Propagating the rank.
        // Time: O(V+E)
        vector<int> pred_rank( Rank.size(), -1 );

        for( int i = 0; i < Rank.size(); ++i ) {
            vector<int> nextptr;
            int s = (i&0x1)?1:-1;

            // Get the min/max co-lex rank of the predecessors of node i.
            for( int j = 0; j < Ptr[i].size(); ++j ) {
                int u = Ptr[i][j];
                int r = Rank[u];
                if( pred_rank[i] == -1 || s*pred_rank[i] < s*r ) {
                    pred_rank[i] = r;
                    nextptr.clear();
                }
                if( pred_rank[i] == r ) {
                    nextptr.push_back( u );
                }
            }
            Ptr[i] = nextptr;
        }

        // Sort by the pair ( rank, predecessor rank )
        return sort_and_get_rank( Rank.size(), [&] (int i, int j) {
                if( Rank[i] < Rank[j] ) return true;
                if( Rank[i] > Rank[j] ) return false;

                return pred_rank[i] < pred_rank[j];
            });
    }

    vector<int> sort_graph( const Graph& G ) {
        const int V = G.V.size();
        const int E = G.E.size();
        vector<int> Rank;
        vector<vector<int> > Ptr;

        init_rank( G, Rank, Ptr );

        int l = 1;
        while( l < 3*V ) {
            vector<int> r = propagate( G, Rank, Ptr );
            if( r == Rank ) break;
            Rank = r;
            l++;
        }
        return Rank;
    }


}
