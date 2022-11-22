#ifndef __E84AF3B0_DFA_H__
#define __E84AF3B0_DFA_H__

#include <vector>
#include <map>
#include <string>

namespace DFA {

typedef int label_t;
extern const label_t empty_label;

struct Graph;
struct Node;
struct Edge;

struct Graph {
    std::vector<Node*> V;
    std::vector<Edge*> E;

    Node* add_node( void );
    Edge* add_edge( Node *u, Node *v, label_t label );
    Edge* add_edge( int u, int v, label_t label );
};

struct Node {
    Node( int _id );
    int id;
    std::vector<Edge*> incoming;
    std::map<label_t,Edge*> outgoing;
};

struct Edge {
    Edge( Node *_u, Node *_v, label_t _l );
    Node* u;
    Node* v;
    label_t label;
};
}

#endif
