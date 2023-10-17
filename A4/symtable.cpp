/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

void destroy(SymEntry* root) {
    if(root == nullptr) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

SymbolTable::SymbolTable() {
    size = 0;
    root = nullptr;
}

SymbolTable::~SymbolTable() {
    destroy(root);
}

void SymbolTable::insert(string k, UnlimitedRational* v) {
    SymEntry* curr = root;
    SymEntry* parent = nullptr;
    while(curr!=nullptr) {
        if(curr->key == k) {
            curr->val = v;
            return;
        }
        parent = curr;
        if(curr->key > k) curr = curr->left;
        else curr = curr->right;
    }

    if(parent == nullptr) {
        root = new SymEntry(k, v);
    }
    else if(parent->key > k) {
        parent->left = new SymEntry(k, v);
    }
    else {
        parent->right = new SymEntry(k, v);
    }
    size++;
}

void SymbolTable::remove(string k) {
    SymEntry* curr = root;
    SymEntry* parent = nullptr;
    while(curr!=nullptr) {
        if(curr->key == k) {
            break;
        }
        parent = curr;
        if(curr->key > k) curr = curr->left;
        else curr = curr->right;
    }

    if(curr == nullptr) return;

    if(curr->left == nullptr && curr->right == nullptr) {
        if(parent == nullptr) {
            root= nullptr;
        }
        else if(parent->left == curr) {
            parent->left = nullptr;
        }
        else {
            parent->right = nullptr;
        }
        delete curr;
    } else if(curr->left == nullptr) {
        if(parent == nullptr) root = curr->right;
        else if(parent->left == curr) parent->left = curr->right;
        else parent->right = curr->right;
        delete curr;
    } else if(curr->right == nullptr) {
        if(parent == nullptr) root = curr->left;
        else if(parent->left == curr) parent->left = curr->left;
        else parent->right = curr->left;
        delete curr;
    } else {
        SymEntry* succ = curr->right;
        SymEntry* succ_parent = curr;
        while(succ->left != nullptr) {
            succ_parent = succ;
            succ = succ->left;
        }
        if(succ_parent == curr) succ_parent->right = succ->right;
        else succ_parent->left = succ->right;
        curr->key = succ->key;
        delete curr->val;
        curr->val = new UnlimitedRational(succ->val->get_p(), succ->val->get_q());
        delete succ;
    }
    size--;
}

UnlimitedRational* SymbolTable::search(string k) {
    SymEntry* curr = root;
    while(curr!=nullptr) {
        if(curr->key == k) {
            return curr->val;
        }
        else if(curr->key > k) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    return nullptr;
}

int SymbolTable::get_size() {
    return size;
}

SymEntry* SymbolTable::get_root() {
    return root;
}