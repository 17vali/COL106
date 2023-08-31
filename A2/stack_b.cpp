#include "stack_b.h"
#include<iostream>
#include<stdexcept>
using namespace std;

Stack_B::Stack_B() {
    capacity = 1024;
    try {
        stk = new int[capacity];
    } catch (const bad_alloc&) {
        throw runtime_error("Out of Memory");
    }
    size = 0;
}

Stack_B::~Stack_B() {
    delete[] stk;
}

void Stack_B::push(int data) {
    if(size == capacity) {
        this->capacity *= 2;
        int* new_stk;
        try {
            new_stk = new int[capacity];
        } catch (const bad_alloc&) {
            throw runtime_error("Out of Memory");
        }
        for(int i=0; i<size; i++) {
            new_stk[i] = stk[i];
        }
        delete[] stk;
        stk = new_stk;
    }
    stk[size++] = data;
}

int Stack_B::pop() {
    if(size>0) {
        if (size == capacity / 4 && capacity>1024) {
            this->capacity /= 2;
            int* new_stk;
            try {
                new_stk = new int[capacity];
            } catch (const bad_alloc&) {
                throw runtime_error("Out of Memory");
            }
            for(int i=0; i<size; i++) {
                new_stk[i] = stk[i];
            }
            delete[] stk;
            stk = new_stk;
        }
        return stk[--size];
    } else {
        throw runtime_error("Empty Stack");
    }
}

int Stack_B::get_element_from_top(int idx) {
    if(idx<size) {
        return stk[size-idx-1];
    } else {
        throw runtime_error("Index out of range");
    }
}

int Stack_B::get_element_from_bottom(int idx) {
    if(idx<size) {
        return stk[idx];
    } else {
        throw runtime_error("Index out of range");
    }
}

void Stack_B::print_stack(bool top_or_bottom) {
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

int Stack_B::add() {
    if(size>1) {
        stk[size-2]+=stk[size-1];
        pop();
        return stk[size-1];
    } else {
        throw runtime_error("Not Enough Arguments");
    }
}

int Stack_B::subtract() {
    if(size>1) {
        stk[size-2]-=stk[size-1];
        pop();
        return stk[size-1];
    } else {
        throw runtime_error("Not Enough Arguments");
    }
}

int Stack_B::multiply() {
    if(size>1) {
        stk[size-2]*=stk[size-1];
        pop();
        return stk[size-1];
    } else {
        throw runtime_error("Not Enough Arguments");
    }
}

int Stack_B::divide() {
    if(size>1) {
        if(stk[size-1]!=0) {
            int res = stk[size-2]/stk[size-1];
            if ((stk[size-2] ^ stk[size-1]) < 0 && res * stk[size-1] != stk[size-2]) res--;
            stk[size-2] = res;
            pop();
            return stk[size-1];
        } else {
            throw runtime_error("Divide by Zero Error");
        }
    } else {
        throw runtime_error("Not Enough Arguments");
    }
}

int* Stack_B::get_stack() {
    return stk;
}

int Stack_B::get_size() {
    return size;
}