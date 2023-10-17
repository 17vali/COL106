/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

void destroy(SymNode* root) {
    if(root == NULL) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

SymbolTable::SymbolTable(){

}

void SymbolTable::insert(string k){
    SymNode* curr = root;
    SymNode* parent = NULL;
    while(curr!=NULL) {
        if(curr->key == k) {
            return;
        }
        parent = curr;
        if(curr->key > k) curr = curr->left;
        else curr = curr->right;
    }

    if(parent == NULL) {
        root = new SymNode(k);
    }
    else if(parent->key > k) {
        parent->left = new SymNode(k);
        parent->left->par = parent;
    }
    else {
        parent->right = new SymNode(k);
        parent->right->par = parent;
    }
    size++;

    while(parent!=NULL) {
        int l_height = parent->left == NULL ? -1 : parent->left->height;
        int r_height = parent->right == NULL ? -1 : parent->right->height;
        parent->height = max(l_height, r_height) + 1;
        int balance = l_height - r_height;
        if(balance > 1) {
            int ll_height = parent->left->left == NULL ? -1 : parent->left->left->height;
            int lr_height = parent->left->right == NULL ? -1 : parent->left->right->height;
            if(ll_height >= lr_height) {
                parent = parent->RightRightRotation();
                if(parent->par == NULL) root = parent;
            }
            else {
                parent = parent->LeftRightRotation();
                if(parent->par == NULL) root = parent;
            }
        }
        else if(balance < -1) {
            int rl_height = parent->right->left == NULL ? -1 : parent->right->left->height;
            int rr_height = parent->right->right == NULL ? -1 : parent->right->right->height;
            if(rr_height >= rl_height) {
                parent = parent->LeftLeftRotation();
                if(parent->par == NULL) root = parent;
            }
            else {
                parent = parent->RightLeftRotation();
                if(parent->par == NULL) root = parent;
            }
        }
        parent = parent->par;
    }
}

void SymbolTable::remove(string k){
    SymNode* curr = root;
    SymNode* parent = NULL;
    while(curr!=NULL) {
        if(curr->key == k) {
            break;
        }
        parent = curr;
        if(curr->key > k) curr = curr->left;
        else curr = curr->right;
    }

    if(curr == NULL) return;

    if(curr->left == NULL && curr->right == NULL) {
        if(parent == NULL) {
            root= NULL;
        }
        else if(parent->left == curr) {
            parent->left = NULL;
        }
        else {
            parent->right = NULL;
        }
        delete curr;
    } else if(curr->left == NULL) {
        if(parent == NULL) {
            root = curr->right;
            root->par = NULL;
        } else if(parent->left == curr) {
            parent->left = curr->right;
            parent->left->par = parent;
        } else {
            parent->right = curr->right;
            parent->right->par = parent;
        }
        delete curr;
    } else if(curr->right == NULL) {
        if(parent == NULL) {
            root = curr->left;
            root->par = NULL;
        } else if(parent->left == curr) {
            parent->left = curr->left;
            parent->left->par = parent;
        } else {
            parent->right = curr->left;
            parent->right->par = parent;
        }
        delete curr;
    } else {
        SymNode* succ = curr->right;
        SymNode* succ_parent = curr;
        while(succ->left != NULL) {
            succ_parent = succ;
            succ = succ->left;
        }
        if(succ_parent == curr) {
            succ_parent->right = succ->right;
            if(succ_parent->right != NULL) succ_parent->right->par = succ_parent;
        } else {
            succ_parent->left = succ->right;
            if(succ_parent->left != NULL) succ_parent->left->par = succ_parent;
        }
        curr->key = succ->key;
        curr->address = succ->address;
        parent = succ_parent;
        delete succ;
    }
    size--;

    while(parent!=NULL) {
        int l_height = parent->left == NULL ? -1 : parent->left->height;
        int r_height = parent->right == NULL ? -1 : parent->right->height;
        parent->height = max(l_height, r_height) + 1;
        int balance = l_height - r_height;
        if(balance > 1) {
            int ll_height = parent->left->left == NULL ? -1 : parent->left->left->height;
            int lr_height = parent->left->right == NULL ? -1 : parent->left->right->height;
            if(ll_height >= lr_height) {
                parent = parent->RightRightRotation();
                if(parent->par == NULL) root = parent;
            }
            else {
                parent = parent->LeftRightRotation();
                if(parent->par == NULL) root = parent;
            }
        }
        else if(balance < -1) {
            int rl_height = parent->right->left == NULL ? -1 : parent->right->left->height;
            int rr_height = parent->right->right == NULL ? -1 : parent->right->right->height;
            if(rr_height >= rl_height) {
                parent = parent->LeftLeftRotation();
                if(parent->par == NULL) root = parent;
            }
            else {
                parent = parent->RightLeftRotation();
                if(parent->par == NULL) root = parent;
            }
        }
        parent = parent->par;
    }
}

int SymbolTable::search(string k){
    SymNode* curr = root;
    while(curr!=NULL) {
        if(curr->key == k) {
            return curr->address;
        }
        else if(curr->key > k) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    return -2;
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* curr = root;
    while(curr!=NULL) {
        if(curr->key == k) {
            curr->address = idx;
            return;
        }
        else if(curr->key > k) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    destroy(root);
}