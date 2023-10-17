/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    height = 0;
}

SymNode::SymNode(string k){
    key = k;
    height = 0;
}

SymNode* SymNode::LeftLeftRotation(){
    SymNode* r = this->right;
    SymNode* rl = r->left;

    r->par = this->par;
    if(r->par == NULL) ;
    else if(r->par->left == this) r->par->left = r;
    else r->par->right = r;

    r->left = this;
    this->par = r;
    this->right = rl;
    if(rl != NULL) rl->par = this;

    int l_height = this->left == NULL ? -1 : this->left->height;
    int r_height = this->right == NULL ? -1 : this->right->height;

    this->height = max(l_height, r_height) + 1;

    int rl_height = r->left == NULL ? -1 : r->left->height;
    int rr_height = r->right == NULL ? -1 : r->right->height;

    r->height = max(rl_height, rr_height) + 1;

    return r;
}

SymNode* SymNode::RightRightRotation(){
    SymNode* l = this->left;
    SymNode* lr = l->right;

    l->par = this->par;
    if(l->par == NULL) ;
    else if(l->par->left == this) l->par->left = l;
    else l->par->right = l;

    l->right = this;
    this->par = l;
    this->left = lr;
    if(lr != NULL) lr->par = this;

    int l_height = this->left == NULL ? -1 : this->left->height;
    int r_height = this->right == NULL ? -1 : this->right->height;

    this->height = max(l_height, r_height) + 1;

    int ll_height = l->left == NULL ? -1 : l->left->height;
    int lr_height = l->right == NULL ? -1 : l->right->height;

    l->height = max(ll_height, lr_height) + 1;

    return l;
}

SymNode* SymNode::LeftRightRotation(){
    this->left = this->left->LeftLeftRotation();
    return this->RightRightRotation();
}

SymNode* SymNode::RightLeftRotation(){
    this->right = this->right->RightRightRotation();
    return this->LeftLeftRotation();
}

SymNode::~SymNode(){
    
}