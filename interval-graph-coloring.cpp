#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cassert>
#include <algorithm>

using namespace std;

int main( void ) {
    
    vector< pair< pair< int, int >, int > > intervals;
    string line;
    int interval_no = 0;

    int s, e;
    while( cin >> s >> e ) {
        assert( s <= e );
        if( s == e ) {
            intervals.push_back( make_pair( make_pair( 2*s  , 1 ), interval_no ) );
            intervals.push_back( make_pair( make_pair( 2*e+1, 0 ), interval_no ) );
        } else {
            intervals.push_back( make_pair( make_pair( 2*s+1, 1 ), interval_no ) );
            intervals.push_back( make_pair( make_pair( 2*e  , 0 ), interval_no ) );
        }
        interval_no++;
    }

    sort( intervals.begin(), intervals.end() );

    int W = 0;
    vector<int> S( interval_no, -1 );
    vector<int> E( interval_no, -1 );
    vector<int> color( interval_no, -1 );
    queue<int> Q;

    for( int i = 0; i < intervals.size(); ++i ) {
        int time  = intervals[i].first.first;
        int start = intervals[i].first.second;
        int i_no  = intervals[i].second;

        if( start ) {
            assert( color[i_no] == -1 );
            S[i_no] = time/2;
            if( Q.empty() ) {
                color[i_no] = W++;
            } else {
                color[i_no] = Q.front();
                Q.pop();
            }
        } else {
            E[i_no] = time/2;
            Q.push( color[i_no] );
        }
    }

    for( int i = 0; i < color.size(); ++i ) {
        cout << S[i] << '\t' << E[i] << '\t' << color[i] << endl;
    }

    return 0;
}
