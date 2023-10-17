/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

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

Evaluator::Evaluator() {
    symtable = new SymbolTable();
}

Evaluator::~Evaluator() {
    delete symtable;
    for(auto d: expr_trees) {
        delete d;
    }
}

void Evaluator::parse(vector<string> code) {
    vector<ExprTreeNode*> stk;
    vector<string> ops;
    for(auto c: code) {
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
            ExprTreeNode* node = new ExprTreeNode(op, static_cast<UnlimitedRational*>(nullptr));
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
                stk.push_back(new ExprTreeNode("VAL", new UnlimitedInt(c)));
            }
            else {
                stk.push_back(new ExprTreeNode("VAR", static_cast<UnlimitedRational*>(nullptr)));
                stk.back()->id = c;
            }
        }
    }
    string assign = ops.back();
    ops.pop_back();
    ExprTreeNode* right = stk.back();
    stk.pop_back();
    ExprTreeNode* left = stk.back();
    stk.pop_back();
    ExprTreeNode* node = new ExprTreeNode(assign, static_cast<UnlimitedRational*>(nullptr));
    node->left = left;
    node->right = right;
    expr_trees.push_back(node);
}

void Evaluator::eval() {
    ExprTreeNode* root = expr_trees.back();
    ExprTreeNode* prev = nullptr;
    vector<ExprTreeNode*> stk;
    stk.push_back(root->right);

    while(!stk.empty()) {
        ExprTreeNode* curr = stk.back();
        if(prev == nullptr || prev->right == curr || prev->left == curr) {
            if(curr->left != nullptr) stk.push_back(curr->left);
            else if(curr->right != nullptr) stk.push_back(curr->right);
            else {
                stk.pop_back();
                if(curr->type == "VAL") {
                    curr->evaluated_value = new UnlimitedRational(curr->val->get_p(), curr->val->get_q());
                } else if(curr->type == "VAR") {
                    UnlimitedRational* val = symtable->search(curr->id);
                    curr->evaluated_value = new UnlimitedRational(val->get_p(), val->get_q());
                }
            }
        } else if(curr->left == prev) {
            if(curr->right != nullptr) stk.push_back(curr->right);
            else {
                stk.pop_back();
                if(curr->type == "VAL") {
                    curr->evaluated_value = new UnlimitedRational(curr->val->get_p(), curr->val->get_q());
                } else if(curr->type == "VAR") {
                    UnlimitedRational* val = symtable->search(curr->id);
                    curr->evaluated_value = new UnlimitedRational(val->get_p(), val->get_q());
                } else {
                    UnlimitedRational* left = curr->left->evaluated_value;
                    UnlimitedRational* right = curr->right->evaluated_value;
                    if(curr->type == "ADD") {
                        curr->evaluated_value = UnlimitedRational::add(left, right);
                    }
                    else if(curr->type == "SUB") {
                        curr->evaluated_value = UnlimitedRational::sub(left, right);
                    }
                    else if(curr->type == "MUL") {
                        curr->evaluated_value = UnlimitedRational::mul(left, right);
                    }
                    else if(curr->type == "DIV") {
                        curr->evaluated_value = UnlimitedRational::div(left, right);
                    }
                }
            }
        } else if(curr->right == prev) {
            stk.pop_back();
            if(curr->type == "VAL") {
                curr->evaluated_value = new UnlimitedRational(curr->val->get_p(), curr->val->get_q());
            } else if(curr->type == "VAR") {
                UnlimitedRational* val = symtable->search(curr->id);
                curr->evaluated_value = new UnlimitedRational(val->get_p(), val->get_q());
            } else {
                UnlimitedRational* left = curr->left->evaluated_value;
                UnlimitedRational* right = curr->right->evaluated_value;
                if(curr->type == "ADD") {
                    curr->evaluated_value = UnlimitedRational::add(left, right);
                }
                else if(curr->type == "SUB") {
                    curr->evaluated_value = UnlimitedRational::sub(left, right);
                }
                else if(curr->type == "MUL") {
                    curr->evaluated_value = UnlimitedRational::mul(left, right);
                }
                else if(curr->type == "DIV") {
                    curr->evaluated_value = UnlimitedRational::div(left, right);
                }
            }
        }
        prev = curr;
    }
    symtable->insert(root->left->id, root->right->evaluated_value);
}