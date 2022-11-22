#include "DFA.h"

namespace DFA {
const label_t empty_label = -1;

Node* Graph::add_node( void ) {
    Node *v = new Node( V.size() );
    V.push_back( v );
    return v;
}

Edge* Graph::add_edge( Node *u, Node *v, label_t label ) {
    if( u->outgoing.count(label) ) return 0;
    Edge *e = new Edge( u, v, label );
    E.push_back( e );
    return e;
}

Edge* Graph::add_edge( int u, int v, label_t label ) {
    while( V.size() <= u ) add_node();
    while( V.size() <= v ) add_node();
    return add_edge( V[u], V[v], label );
}

Node::Node( int _id )
:id(_id) {
    ;
}

Edge::Edge( Node *_u, Node *_v, label_t _l )
:u(_u), v(_v), label(_l) {
    u->outgoing[label] = this;
    v->incoming.push_back(this);
}

}
