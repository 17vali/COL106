#include "stack_a.h"
#include<iostream>
#include<stdexcept>
using namespace std;

Stack_A::Stack_A() {
    size = 0;
}

void Stack_A::push(int data) {
    if(size<1024) {
        stk[size++] = data;
    } else {
        throw runtime_error("Stack Full");
    }
}

int Stack_A::pop() {
    if(size>0) {
        return stk[--size];
    } else {
        throw runtime_error("Empty Stack");
    }
}

int Stack_A::get_element_from_top(int idx) {
    if(idx<size) {
        return stk[size-idx-1];
    } else {
        throw runtime_error("Index out of range");
    }
}

int Stack_A::get_element_from_bottom(int idx) {
    if(idx<size) {
        return stk[idx];
    } else {
        throw runtime_error("Index out of range");
    }
}

void Stack_A::print_stack(bool top_or_bottom) {
    if(top_or_bottom) {
        for(int i=0; i<size; i++) {
            cout<<stk[size-i-1]<<" ";
        }
        cout<<'\n';
    } else {
        for(int i=0; i<size; i++) {
            cout<<stk[i]<<" ";
        }
        cout<<'\n';
    }
}

int Stack_A::add() {
    if(size>1) {
        stk[size-2]+=stk[size-1];
        return stk[--size-1];
    } else {
        throw runtime_error("Not Enough Arguments");
    }
}

int Stack_A::subtract() {
    if(size>1) {
        stk[size-2]-=stk[size-1];
        return stk[--size-1];
    } else {
        throw runtime_error("Not Enough Arguments");
    }
}

int Stack_A::multiply() {
    if(size>1) {
        stk[size-2]*=stk[size-1];
        return stk[--size-1];
    } else {
        throw runtime_error("Not Enough Arguments");
    }
}

int Stack_A::divide() {
    if(size>1) {
        if(stk[size-1]!=0) {
            int res = stk[size-2]/stk[size-1];
            if ((stk[size-2] ^ stk[size-1]) < 0 && res * stk[size-1] != stk[size-2]) res--;
            stk[size-2] = res;
            return stk[--size-1];
        } else {
            throw runtime_error("Divide by Zero Error");
        }
    } else {
        throw runtime_error("Not Enough Arguments");
    }
} 

int* Stack_A::get_stack() {
    return stk;
}

int Stack_A::get_size() {
    return size;
}