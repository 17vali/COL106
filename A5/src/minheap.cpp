/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"

//Write your code below this line

void destroy(HeapNode* r) {
    if(r == NULL) return;
    destroy(r->left);
    destroy(r->right);
    delete r;
}

MinHeap::MinHeap(){
    
}

void MinHeap::push_heap(int num){
    size++;
    if(root == NULL) {
        root = new HeapNode(num);
        return;
    }

    int sz = size;
    int msb = -1;
    while (sz >>= 1) {
        msb++;
    }

    HeapNode* curr = root;
    while(msb) {
        if(size & (1<<msb)) {
            curr = curr->right;
        }
        else {
            curr = curr->left;
        }
        msb--;
    }

    if(size & 1) {
        curr->right = new HeapNode(num);
        curr->right->par = curr;
        curr = curr->right;
    }
    else {
        curr->left = new HeapNode(num);
        curr->left->par = curr;
        curr = curr->left;
    }

    while(curr->par != NULL && curr->par->val > curr->val) {
        int temp = curr->par->val;
        curr->par->val = curr->val;
        curr->val = temp;
        curr = curr->par;
    }
}

int MinHeap::get_min(){
    if(size == 0) return -1;
    return root->val;
}

void MinHeap::pop(){

    if(size == 1) {
        delete root;
        root = NULL;
        size--;
        return;
    }

    int sz = size;
    int msb = -1;
    while (sz >>= 1) {
        msb++;
    }

    HeapNode* curr = root;
    while(msb) {
        if(size & (1<<msb)) {
            curr = curr->right;
        }
        else {
            curr = curr->left;
        }
        msb--;
    }

    if(size & 1) {
        root->val = curr->right->val;
        HeapNode* del = curr->right;
        curr->right = NULL;
        delete del;
    }
    else {
        root->val = curr->left->val;
        HeapNode* del = curr->left;
        curr->left = NULL;
        delete del;
    }

    curr = root;
    size--;

    while(curr->left != NULL) {
        if(curr->right == NULL || curr->left->val < curr->right->val) {
            if(curr->val > curr->left->val) {
                int temp = curr->val;
                curr->val = curr->left->val;
                curr->left->val = temp;
                curr = curr->left;
            }
            else {
                break;
            }
        }
        else {
            if(curr->val > curr->right->val) {
                int temp = curr->val;
                curr->val = curr->right->val;
                curr->right->val = temp;
                curr = curr->right;
            }
            else {
                break;
            }
        }
    }
}

MinHeap::~MinHeap(){
    destroy(root);
}