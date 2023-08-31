#include "stack_c.h"
#include<iostream>
#include<stdexcept>
using namespace std;

Stack_C::Stack_C() {
    try {
        stk = new List();
    } catch (const bad_alloc&) {
        throw runtime_error("Out of Memory");
    }
}

Stack_C::~Stack_C() {
    delete stk;
}

void Stack_C::push(int data) {
    stk->insert(data);
}

int Stack_C::pop() {
    if(stk->get_size()>0) {
        return stk->delete_tail();
    } else {
        throw runtime_error("Empty Stack");
    }
}

int Stack_C::get_element_from_top(int idx) {
    if(idx<stk->get_size()) {
        Node* curr = stk->get_head()->next;
        int n = stk->get_size()-idx-1;
        for(int i=0; i<n; i++) {
            curr = curr->next;
        }
        return curr->get_value();
    } else {
        throw runtime_error("Index out of range");
    }
}

int Stack_C::get_element_from_bottom(int idx) {
    if(idx<stk->get_size()) {
        Node* curr = stk->get_head()->next;
        for(int i=0; i<idx; i++) {
            curr = curr->next;
        }
        return curr->get_value();
    } else {
        throw runtime_error("Index out of range");
    }

}

void Stack_C::print_stack(bool top_or_bottom) {
    if(top_or_bottom) {
        string s = "";
        Node* curr = stk->get_head()->next;
        while(!curr->is_sentinel_node()) {
            s = to_string(curr->get_value()) + " " + s;
            curr = curr->next;
        }
        cout<<s<<'\n';
    } else {
        Node* curr = stk->get_head()->next;
        while(!curr->is_sentinel_node()) {
            cout<<curr->get_value()<<" ";
            curr = curr->next;
        }
        cout<<'\n';
    }
}

int Stack_C::add() {
    if(stk->get_size()>1) {
        int a = stk->delete_tail();
        int b = stk->delete_tail();
        stk->insert(a+b);
        return a+b;
    } else {
        throw runtime_error("Not Enough Arguments");
    }
}

int Stack_C::subtract() {
    if(stk->get_size()>1) {
        int a = stk->delete_tail();
        int b = stk->delete_tail();
        stk->insert(b-a);
        return b-a;
    } else {
        throw runtime_error("Not Enough Arguments");
    }
}

int Stack_C::multiply() {
    if(stk->get_size()>1) {
        int a = stk->delete_tail();
        int b = stk->delete_tail();
        stk->insert(a*b);
        return a*b;
    } else {
        throw runtime_error("Not Enough Arguments");
    }
}

int Stack_C::divide() {
    if(stk->get_size()>1) {
        int a = stk->delete_tail();
        if(a==0) {
            stk->insert(a);
            throw runtime_error("Divide by Zero Error");
        }
        int b = stk->delete_tail();
        int res = b/a;
        if ((a ^ b) < 0 && res * a != b) res--;
        stk->insert(res);
        return res;
    } else {
        throw runtime_error("Not Enough Arguments");
    }
}

List* Stack_C::get_stack() {
    return stk;
}

int Stack_C::get_size() {
    return stk->get_size();
}