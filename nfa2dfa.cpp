#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <cassert>

using namespace std;

map< int,map<char,set<int> > > NFA;

bool is_DFA( void ) {
    for( auto i = NFA.begin(); i != NFA.end(); ++i ) {
        for( auto j = i->second.begin(); j != i->second.end(); ++j ) {
            if( j->second.size() > 1 ) return false;
        }
    }
    return true;
}

char to_lower( char c ) {
	if( 'A' <= c && c <= 'Z' ) return c-'A'+'a';
	return c;
}

map< set<int>, int > StateSet_ID;
map< int,map<char,int> > DFA;

set<char> outlabels( const set<int>& u ) {
    set<char> ret;
    for( auto i = u.begin(); i != u.end(); ++i ) {
        if( NFA.count(*i) == 0 ) continue;
        const map<char,set<int> >& m = NFA.at(*i);
        for( auto j = m.begin(); j != m.end(); ++j ) {
            ret.insert( j->first );
        }
    }
    return ret;
}

set<int> move( const set<int>& u, char x ) {
    set<int> ret;
    for( auto i = u.begin(); i != u.end(); ++i ) {
        if( NFA.count(*i) == 0 ) continue;
        const map<char,set<int> >& m = NFA.at(*i);
        if( m.count( x ) == 0 ) continue;
        const set<int>& vs = m.at( x );
        for( auto j = vs.begin(); j != vs.end(); ++j ) {
            ret.insert( *j );
        }
    }
    return ret;
}

int get_stateset_id( const set<int>& vs ) {
    return StateSet_ID.insert( make_pair( vs, (int)StateSet_ID.size() ) ).first->second;
}

void convert( void ) {
    queue< set<int> > q;
    set<int> v_init({0});
    q.push(v_init);
    DFA[get_stateset_id(v_init)];

    while( !q.empty() ) {
        set<int> u = q.front();
        q.pop();
        int u_id = get_stateset_id( u );

        set<char> ls = outlabels( u );
        for( auto i = ls.begin(); i != ls.end(); ++i ) {
            char l = *i;
            set<int> v = move( u, l );
            int v_id = get_stateset_id( v );
            assert( DFA.at(u_id).count(l) == 0 );

            DFA[u_id][l] = v_id;

            if( DFA.count( v_id ) ) continue;
            DFA[v_id];
            q.push(v);
        }
    }
}


int main( void ) {
    int u, v;
    char l;
    while( cin >> u >> v >> l ) {
        NFA[u][to_lower(l)].insert(v);
    }

    convert();

    for( auto i = DFA.begin(); i != DFA.end(); ++i ) {
        for( auto j = i->second.begin(); j != i->second.end(); ++j ) {
            cout << i->first << '\t' << j->second << '\t' << j->first << endl;
        }
    }
    return 0;
}
