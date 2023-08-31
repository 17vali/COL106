#include "node.h"
#include<iostream>
#include<stdexcept>
using namespace std;

Node::Node(bool sentinel) {
    is_sentinel = sentinel;
}

Node::Node(int v, Node* nxt=nullptr, Node* prv=nullptr) {
    value = v;
    next = nxt;
    prev = prv;
    is_sentinel = false;
}

bool Node::is_sentinel_node() {
    return is_sentinel;
}

int Node::get_value() {
    return value;
}