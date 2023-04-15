#include <string>
#include <iostream>
#include <cctype>

using namespace std;



int main( int argc, char **argv ) {
	if( argc < 2 ) return 1;
	string key = string( ">chr" ) + string( argv[1] );
	int m = key.size();
	
	string line;
	while( getline( cin, line ) ) {
		if( !line.empty() && line.compare(0,m,key) == 0 && (line.size() == m || isspace( line[m] ) ) ) {
			//cout << ">" << key << endl;
			cout << '>' << line.substr(4) << endl;
			break;
		}
	}
	while( getline( cin, line ) ) {
		if( line.empty() || line[0] == '>' ) break;
		cout << line << endl;
	}
	return 0;
}
