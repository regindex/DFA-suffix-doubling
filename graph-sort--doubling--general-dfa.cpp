#include "DFA.h"
#include "graph-sort.h"
#include <vector>
#include <set>

using namespace std;
using DFA::Graph;

namespace doubling {
    static int max_ptrs( const vector<vector<int> >& ptrs ) {
        int m = 0;
        for( int i = 0; i < ptrs.size(); ++i ) {
            m = max( m, (int)ptrs[i].size() );
        }
        return m;
    }

    static int num_ptrs( const vector<vector<int> >& ptrs ) {
        int count = 0;
        for( int i = 0; i < ptrs.size(); ++i ) {
            count += ptrs[i].size();
        }
        return count;
    }

    void init_rank( const Graph& G, vector<int>& Rank, vector<vector<int> >& Ptr ) {
        // Description: Initialize Rank and Ptr with min/max incoming labels
        // Time: O(V+E)
        // Return:
        //     For each node v,
        //       Rank[2*v  ] is the (co-lex) rank of its minimum suffix.
        //       Rank[2*v+1] is the (co-lex) rank of itx maximum suffix.
        //     Ptr: the pointers to the predecessors. This function returns the set of pointers to the source nodes of the incoming edges with the minimum/maximum label.
        const int V = G.V.size();
        const int E = G.E.size();

        vector<DFA::label_t> min_incoming_label( V, DFA::empty_label );
        vector<DFA::label_t> max_incoming_label( V, DFA::empty_label );

        Ptr = vector<vector<int> >(2*V);

        for( int i = 0; i < E; ++i ) {
            int u = G.E[i]->u->id;
            int v = G.E[i]->v->id;
            DFA::label_t l = G.E[i]->label;

            if( min_incoming_label[v] == DFA::empty_label || l < min_incoming_label[v] ) {
                min_incoming_label[v] = l;
                Ptr[2*v  ].clear();
            }
            if( max_incoming_label[v] == DFA::empty_label || max_incoming_label[v] < l ) {
                max_incoming_label[v] = l;
                Ptr[2*v+1].clear();
            }
            if( l == min_incoming_label[v] ) { Ptr[2*v  ].push_back( 2*u   ); }
            if( l == max_incoming_label[v] ) { Ptr[2*v+1].push_back( 2*u+1 ); }
        }

        // Sort by incoming edge label.
        Rank = sort_and_get_rank( 2*V, [&] (int i, int j) {
                DFA::label_t r_i = ((i&0x1)?max_incoming_label[i>>1]:min_incoming_label[i>>1]);
                DFA::label_t r_j = ((j&0x1)?max_incoming_label[j>>1]:min_incoming_label[j>>1]);
                return r_i < r_j;
            });
    }

    static vector<int> get_pred_rank( vector<int>& Rank, vector<vector<int> >& Ptr ) {
        // Description: Compute the min/max rank of predecessors 
        // Time: proportional to the total number of pointers
        // Return: ret[v] is the maximum/minimum rank of v's predecessors
        vector<int> ret( Rank.size(), -1 );
        for( int i = 0; i < Ptr.size(); ++i ) {
            int s = (i&0x1)?1:-1;
            for( int j = 0; j < Ptr[i].size(); ++j ) {
                int u = Ptr[i][j];
                int r = Rank[u];
                if( ret[i] == -1 || s*ret[i] < s*r ) {
                    ret[i] = r;
                }
            }
        }
        return ret;
    }

    static vector< vector<int> > get_target_ptr( vector<int>& Rank, vector<int>& targetRank, vector<vector<int> >& Ptr ) {
        // Description: Leave only pointers to nodes having the rank same as the targetRank
        // Time: proportional to the total number of pointers
        // Return: remaining pointers
        vector<vector<int> > ret( Ptr.size() );
        
        for( int i = 0; i < Ptr.size(); ++i ) {
            for( int j = 0; j < Ptr[i].size(); ++j ) {
                int u = Ptr[i][j];
                int r = Rank[u];
                if( targetRank[i] == r ) {
                    ret[i].push_back( u );
                }
            }
        }
        return ret;

    }

    static vector< vector<int> > get_two_hop_pointers( vector<vector<int> >& Ptr ) {
        // Description: Update the pointers
        // Time: proportional to the total number of pointers before/after merging
        //     the number of iteration of loop for i and j = the number of pointers before merging
        //     the number of calls of ret[i].push_back() = the number of pointers after merging
        vector<vector<int> > ret(Ptr.size());
        for( int i = 0; i < Ptr.size(); ++i ) {
            for( int j = 0; j < Ptr[i].size(); ++j ) {
                for( int k = 0; k < Ptr[ Ptr[i][j] ].size(); ++k ) {
                    int p = Ptr[ Ptr[i][j] ][k];
                    ret[i].push_back( p );
                }
            }
        }
        return ret;
    }

    static void doubling( const Graph& G, vector<int>& Rank, vector<vector<int> >& Ptr ) {
        // Description: a doubling procedure

        // Sort the node using the pairs of ranks
        vector<int> nextrank = get_pred_rank( Rank, Ptr );
        Rank = sort_and_get_rank( Rank.size(), [&] (int i, int j) {
                if( Rank[i] < Rank[j] ) return true;
                if( Rank[i] > Rank[j] ) return false;

                return nextrank[i] < nextrank[j];
            });

        // Remove pointers to nodes with non-{min/max} ranks
        nextrank = get_pred_rank( Rank, Ptr );
        Ptr = get_target_ptr( Rank, nextrank, Ptr );

        // Update the pointers
        Ptr = get_two_hop_pointers( Ptr ); 

        // In fact, one more filtering step is needed to ensure that the predecessors of a node have the same rank.
        // Or, the pointer-removal above should look 2-hops farther.
        //nextrank = get_pred_rank( Rank, Ptr );
        //Ptr = get_target_ptr( Rank, nextrank, Ptr );

    }

    vector<int> sort_graph( const Graph& G ) {
        const int V = G.V.size();
        const int E = G.E.size();
        vector<int> Rank;
        vector<vector<int> > Ptr;

        init_rank( G, Rank, Ptr );
        //cout << "L=1" << endl;
        //cout << Rank  << endl;
        //cout << Ptr   << endl;

        int countmax = num_ptrs( Ptr );
        int nummax = max_ptrs( Ptr );
        int l = 1;

        while( l < 4*V ) {
            doubling( G, Rank, Ptr );
            l <<= 1;

            countmax = max(countmax, num_ptrs( Ptr ) );
            nummax = max(nummax, max_ptrs( Ptr ) );
            //cout << "L=" << l << endl;
            //cout << Rank  << endl;
            //cout << Ptr   << endl;
        }
        return Rank;
    }

}
