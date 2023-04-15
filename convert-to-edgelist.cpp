#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

struct LabeledNode {
    vector<int> pred;
    vector<int> succ;
    string label;

    int indegree (void) const { return pred.size(); }
    int outdegree(void) const { return succ.size(); }
};

vector<LabeledNode> NodeLabeledGraph;

char canonical( char x ) {
    switch(x) {
        case 'A': case 'C': case 'G': case 'T': return x;
        case 'a': case 'c': case 'g': case 't': return x-'a'+'A';
        default:;
    }
    return 'N';
}

void process_node( const string& l ) {
    istringstream ss( l );
    string tag;
    int vid;
    string label;

    ss >> tag >> vid >> label;

    if( NodeLabeledGraph.size() <= vid ) NodeLabeledGraph.resize( vid+1 );

    NodeLabeledGraph[vid].label = label;
}

void process_link( const string& l ) {
    istringstream ss( l );
    string tag;
    int uid;
    string tmp;
    int vid;

    ss >> tag >> uid >> tmp >> vid >> tmp >> tmp;

    NodeLabeledGraph[uid].succ.push_back(vid);
    NodeLabeledGraph[vid].pred.push_back(uid);
}

void convert_to_charlabeled_graph( void ) {
    int newV = NodeLabeledGraph.size();
    for( int i = 0; i < NodeLabeledGraph.size(); ++i ) {
        if( NodeLabeledGraph[i].label.empty() ) {
            assert( i == 0 );
            continue;
        }

        if( NodeLabeledGraph[i].indegree() == 0 ) {
            cout << 0 << '\t' << i << '\t' << canonical( NodeLabeledGraph[i].label[0] ) << endl;
        }
    }

    for( int i = 0; i < NodeLabeledGraph.size(); ++i ) {
        int u = i;
        for( int j = 1; j < NodeLabeledGraph[i].label.size(); ++j ) {
            int v = newV++;
            char l = canonical(NodeLabeledGraph[i].label[j]);
            cout << u << '\t' << v << '\t' << l << endl;
            u = v;
        }

        for( int j = 0; j < NodeLabeledGraph[i].succ.size(); ++j ) {
            int v = NodeLabeledGraph[i].succ[j];
            char l = canonical(NodeLabeledGraph[v].label[0]);
            cout << u << '\t' << v << '\t' << l << endl;
        }
    }
}

int main( void ) {
    string line;
    while( getline( cin, line ) ) {
        if( line.empty() ) continue;
        switch( line[0] ) {
            case 'S':
                process_node( line );
                break;
            case 'L':
                process_link( line );
                break;
            default:
            ;
        }
    }
    convert_to_charlabeled_graph();
    return 0;
}
