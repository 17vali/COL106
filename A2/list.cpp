#include "list.h"
#include<iostream>
#include<stdexcept>
using namespace std;

List::List() {
    size = 0;
    try {
        sentinel_head = new Node();
        sentinel_tail = new Node();
    } catch (const bad_alloc&) {
        throw runtime_error("Out of Memory");
    }
    sentinel_head->next = sentinel_tail;
    sentinel_tail->prev = sentinel_head;
}

List::~List() {
    Node* curr = sentinel_head->next;
    while(curr!=sentinel_tail) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete sentinel_head;
    delete sentinel_tail;
}

void List::insert(int v) {
    Node* new_node;
    try {
        new_node = new Node(v, sentinel_tail, sentinel_tail->prev);
    } catch (const bad_alloc&) {
        throw runtime_error("Out of Memory");
    }
    sentinel_tail->prev->next = new_node;
    sentinel_tail->prev = new_node;
    size++;
}

int List::delete_tail() {
    Node* temp = sentinel_tail->prev;
    int v = temp->get_value();
    sentinel_tail->prev = temp->prev;
    temp->prev->next = sentinel_tail;
    delete temp;
    size--;
    return v;
}

int List::get_size() {
    return size;
}

Node* List::get_head() {
    return sentinel_head;
}