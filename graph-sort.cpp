#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <set>

using namespace std;
using namespace chrono;

int N;
vector<int> I;
vector<int> R;
vector<int> R_;
vector<int> E;
vector<int> E_;
vector<int> oE;
vector<int> oE_;

vector<int> C;
vector<int> I_;

ostream& operator << ( ostream& out, const vector<int>& vs ) {
    for( int i = 0; i < vs.size(); ++i ) {
        out << vs[i] << ' ';
    }
    return out;
}

void load_input( istream& in ) {
    in >> N;
    R.resize(2*N);
    R_.resize(2*N);

    oE.clear(); 
    oE.reserve(2*N+1);
    E.clear();
    E.reserve(2*N);

    for( int i = 0; i < N; ++i ) {
        in >> R[i];
    }
    for( int i = N; i < 2*N; ++i ) {
        R[i] = R[i-N];
    }

    I.resize(2*N);
    I_.resize(2*N);
    C.resize(2*N+1);
    for( int i = 0; i < 2*N; ++i ) {
        I[i] = i;
        C[i] = 0;
    }
    C[2*N] = 0;

    int u, v;
    // ASSUME: sorted by v
    int prev_v = 0;
    int offset_v = 0;
    oE.push_back(0);
    while( in >> u >> v ) {
        while( prev_v < v ) {
            prev_v++;
            oE.push_back( offset_v );
        }
        E.push_back(u);
        offset_v++;
    }
    while( prev_v < N ) {
        prev_v++;
        oE.push_back( offset_v );
    }

    oE.resize(2*N+1);
    for( int i = N+1; i <= 2*N; ++i ) {
        oE[i] = oE[i-1] + oE[i-N] - oE[i-N-1];
    }

    int m = E.size();
    for( int i = 0; i < m; ++i ) {
        E.push_back( E[i]+N );
    }

    oE_.resize(oE.size());
    E_.reserve(E.size());
}

int filter_non_minimum_extender( void ) {
    int eout = 0;
    for( int v = 0; v < N; ++v ) {
        /*if( oE[v]+1 == oE[v+1] ) {
            E[eout] = E[oE[v]];
            oE[v] = eout++;
            continue;
        }*/
        int min_rank_of_extender = R[E[oE[v]]];
        int write_offset = 0;
        for( int i = oE[v]; i < oE[v+1]; ++i ) {
            if( min_rank_of_extender > R[E[i]] ) {
                min_rank_of_extender = R[E[i]];
                write_offset = 0;
            }

            if( min_rank_of_extender == R[E[i]] ) {
                E[eout+write_offset++] = E[i];
            }
        }
        oE[v] = eout;
        eout += write_offset;
    }
    return eout;
}

int filter_non_maximum_extender( int eout ) {
    for( int v = N; v < 2*N; ++v ) {
        /*if( oE[v]+1 == oE[v+1] ) {
            E[eout] = E[oE[v]];
            oE[v] = eout++;
            continue;
        }*/
        int max_rank_of_extender = R[E[oE[v]]];
        int write_offset = 0;
        for( int i = oE[v]; i < oE[v+1]; ++i ) {
            if( max_rank_of_extender < R[E[i]] ) {
                max_rank_of_extender = R[E[i]];
                write_offset = 0;
            }

            if( max_rank_of_extender == R[E[i]] ) {
                E[eout+write_offset++] = E[i];
            }
        }
        oE[v] = eout;
        eout += write_offset;
    }
    oE[2*N] = eout;
    return eout;
}

void filter( void ) {
    int eout;
    eout = filter_non_minimum_extender();
    eout = filter_non_maximum_extender(eout);
    E.resize(eout);
}

void sort_by_extender_rank( void ) {
    int cmax = 0;
    for( int v = 0; v < 2*N; ++v ) {
        int r_p = R[E[oE[v]]];
        cmax = (cmax>r_p?cmax:r_p);
        C[r_p]++;
    }
    for( int i = 1; i <= cmax; ++i ) {
        C[i] += C[i-1];
    }
    for( int v = 2*N-1; v >= 0; --v ) {
        int r_p = R[E[oE[v]]];
        I[--C[r_p]] = v;
    }
    for( int i = 0; i <= cmax; ++i ) {
        C[i] = 0;
    }
}

void sort_by_rank( void ) {
    int cmax = 0;
    for( int i = 0; i < 2*N; ++i ) {
        int v = I[i];
        int r_p = R[v];
        cmax = (cmax>r_p?cmax:r_p);
        C[r_p]++;
    }
    for( int i = 1; i <= cmax; ++i ) {
        C[i] += C[i-1];
    }
    for( int i = 2*N-1; i >= 0; --i ) {
        int v = I[i];
        int r_p = R[v];
        I_[--C[r_p]] = v;
    }
    for( int i = 0; i <= cmax; ++i ) {
        C[i] = 0;
    }
    swap( I, I_ );
}

void get_rank( void ) {
    int r = 0;
    swap( R_, R );
    R[0]=0;
    for( int i = 1; i < 2*N-1; ++i ) {
        int u = I[i];
        int v = I[i+1];
        if( R_[u] < R_[v] || R_[E[oE[u]]] < R_[E[oE[v]]] ) ++r;
        R[v] = r;
    }
}

void gather_extenders( void ) {
    oE_.clear();
    E_.clear();
    int write_offset = 0;
    for( int u = 0; u < 2*N; ++u ) {
        oE_.push_back( write_offset );
        for( int i = oE[u]; i < oE[u+1]; ++i ) {
            int v = E[i];
            for( int j = oE[v]; j < oE[v+1]; ++j ) {
                int vv = E[j];
                E_.push_back( vv );
                ++write_offset;
            }
        }
    }
    oE_.push_back( write_offset );
    swap( E, E_ );
    swap( oE, oE_ );
}

void check_num_extenders( void ) {
    int m = 0;
    for( int i = 0; i < 2*N; ++i ) {
        int num = oE[i+1]-oE[i];
        m = (m>num)?m:num;
    }
    cerr << "Max #Pointers=\t" << m << endl;
}

int main( void ) {

    load_input( cin );
    cerr << "#Pointers=\t" << E.size() << endl;

    system_clock::time_point start = system_clock::now();

    for( int i = 1; i <= 2*N; i<<=1 ) {
        cerr << "** Sorting with length-2^k suffixes: 2^k=\t" << i << endl;
        check_num_extenders();
        filter();
        cerr << "#Extenders=\t" << E.size() << endl;
        check_num_extenders();

        sort_by_extender_rank();
        cerr << "Sorted 1..." << endl;
        sort_by_rank();
        cerr << "Sorted 2..." << endl;
        get_rank();
        cerr << "Rank computed" << endl;
        gather_extenders();
        cerr << "Extenders collected. #Pointers=\t" << E.size() << endl;
    }

    system_clock::time_point end = system_clock::now();
    nanoseconds nano = end - start;
    cerr << "Elapsed time(ns)=\t" << nano.count() << endl;

    for( int i = 0; i < N; ++i ) {
        cout << R[i] << '\t' << R[i+N] << endl;
    }

    return 0;
}

