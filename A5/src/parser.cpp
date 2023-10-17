/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

bool is_integer(string s) {
    if(s[0] == '-') {
        s = s.substr(1);
    }
    for(auto c: s) {
        if(c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

Parser::Parser(){
    symtable = new SymbolTable();
}



void Parser::parse(vector<string> expression){
    vector<ExprTreeNode*> stk;
    vector<string> ops;
    for(auto c: expression) {
        if(c == "(") {
            ops.push_back(c);
        }
        else if(c == ")") {
            string op = ops.back();
            ops.pop_back();
            ExprTreeNode* right = stk.back();
            stk.pop_back();
            ExprTreeNode* left = stk.back();
            stk.pop_back();
            ExprTreeNode* node = new ExprTreeNode(op, 0);
            node->left = left;
            node->right = right;
            stk.push_back(node);
            ops.pop_back();
        }
        else if(c == "+" || c == "-" || c == "*" || c == "/" || c == ":=") {
            if(c == "+") ops.push_back("ADD");
            else if(c == "-") ops.push_back("SUB");
            else if(c == "*") ops.push_back("MUL");
            else if(c == "/") ops.push_back("DIV");
            else ops.push_back(c);
        }
        else {
            if(is_integer(c)) {
                stk.push_back(new ExprTreeNode("VAL", stoi(c)));
            }
            else {
                if(c == "del") {
                    stk.push_back(new ExprTreeNode("DEL", 0));
                } else if(c == "ret") {
                    stk.push_back(new ExprTreeNode("RET", 0));
                } else {
                    stk.push_back(new ExprTreeNode("VAR", 0));
                    stk.back()->id = c;
                }
            }
        }
    }
    string assign = ops.back();
    ops.pop_back();
    ExprTreeNode* right = stk.back();
    stk.pop_back();
    ExprTreeNode* left = stk.back();
    stk.pop_back();
    ExprTreeNode* root = new ExprTreeNode(assign, 0);
    root->left = left;
    root->right = right;
    
    expr_trees.push_back(root);

    if(root->left->type == "VAR") {
        if(symtable->search(root->left->id) == -2) {
            symtable->insert(root->left->id);
        }
    } else if(root->left->type == "DEL") {
        last_deleted = symtable->search(root->right->id);
        symtable->remove(root->right->id);
    }
}

Parser::~Parser(){
    delete symtable;
    for(auto d: expr_trees) {
        delete d;
    }
}