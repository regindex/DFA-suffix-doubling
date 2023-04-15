#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cassert>
#include <set>

using namespace std;

map<int,char> label;
map<int,vector<int> > incoming;

int conv(char c ) {
	switch(c) {
		case 0 : return 0;
		case 'a': return 1;
		case 'c': return 2; 
		case 'g': return 3;
		case 'n': return 4;
		case 't': return 5;
			
		default:  cerr << "ERROR=" << c << '\t' << (int)c << endl; assert(0); return -1;
	}
}

int main( void ) {
	int u, v;
	char c;

	label[0] = 0;
	while( cin >> u >> v >> c ) {
		if( label.count(v) ) {
			assert( label.at(v) == c );
		}
		label[v] = c;
		incoming[v].push_back(u);
	}

	cout << label.size() << endl;
	for( auto i = label.begin(); i != label.end(); ++i ) {
		cout << conv( i->second ) << ' ';
	}
	cout << endl;
	cout << "0 0" << endl;
	for( auto i = incoming.begin(); i != incoming.end(); ++i ) {
	assert( set<int>( i->second.begin(), i->second.end() ).size() == i->second.size() );
		for( int j = 0; j < i->second.size(); ++j ) {
			cout << i->second[j] << ' ' << i->first << endl;
		}
	}

        return 0;
}
