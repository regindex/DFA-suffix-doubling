#ifndef __A5BF072D_GRAPH_SORT__UTIL_H__
#define __A5BF072D_GRAPH_SORT__UTIL_H__

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

template <class T, class U>
std::ostream& operator << ( std::ostream& out, const std::map<T,U>& v ) {
    out << '{';
    for( auto i = v.begin(); i != v.end(); ++i ) {
        if( i != v.begin() ) out << ',';
        out << i->first << ':' << i->second;
    }
    out << '}';
    return out;
}

template <class T>
std::ostream& operator << ( std::ostream& out, const std::set<T>& v ) {
    out << '{';
    for( auto i = v.begin(); i != v.end(); ++i ) {
        if( i != v.begin() ) out << ',';
        out << *i;
    }
    out << '}';
    return out;
}

template <class T>
std::ostream& operator << ( std::ostream& out, const std::vector<T>& v ) {
    out << '[';
    for( int i = 0; i < v.size(); ++i ) {
        if( i > 0 ) out << ',';
        out << v[i];
    }
    out << ']';
    return out;
}

template <class COMP>
std::vector<int> sort_and_get_rank( int n, const COMP& comp ) {
    // Sort using COMP and return the resulting rank
    std::vector<int> sorted_idx( n );
    for( int i = 0; i < n; ++i ) sorted_idx[i] = i;

    // TODO to replace with an O(n) sort algorithm in the future
    std::sort( sorted_idx.begin(), sorted_idx.end(), comp );

    std::vector<int> rank( n );
    int r = 0;
    for( int i = 0; i < n; ++i ) {
        if( i > 0 && comp( sorted_idx[i-1], sorted_idx[i] ) ) ++r;
        rank[ sorted_idx[i] ] = r;
    }
    return rank;
}


#endif
