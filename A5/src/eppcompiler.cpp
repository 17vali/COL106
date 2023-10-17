/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler(){
    
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    output_file = out_file;
    memory_size = mem_limit;
}

void EPPCompiler::compile(vector<vector<string>> code){
    for(auto tokens: code) {
        targ.parse(tokens);
        vector<string> commands = generate_targ_commands();
        write_to_file(commands);
    }
}

vector<string> EPPCompiler::generate_targ_commands(){
    ExprTreeNode* root = targ.expr_trees.back();
    ExprTreeNode* prev = NULL;
    vector<string> commands;

    if(root->left->type == "DEL") {
        least_mem_loc.push_heap(targ.last_deleted);
        commands.push_back("DEL = mem[" + to_string(targ.last_deleted) + "]");
        return commands;
    }

    vector<ExprTreeNode*> stk;
    stk.push_back(root->right);

    while(!stk.empty()) {
        ExprTreeNode* curr = stk.back();
        if(prev == NULL || prev->right == curr || prev->left == curr) {
            if(curr->right != NULL) stk.push_back(curr->right);
            else if(curr->left != NULL) stk.push_back(curr->left);
            else {
                stk.pop_back();
                if(curr->type == "VAL") {
                    commands.push_back("PUSH " + to_string(curr->num));
                } else if(curr->type == "VAR") {
                    commands.push_back("PUSH mem[" + to_string(targ.symtable->search(curr->id)) + "]");
                }
            }
        } else if(curr->right == prev) {
            if(curr->left != NULL) stk.push_back(curr->left);
            else {
                stk.pop_back();
                if(curr->type == "VAL") {
                    commands.push_back("PUSH " + to_string(curr->num));
                } else if(curr->type == "VAR") {
                    commands.push_back("PUSH mem[" + to_string(targ.symtable->search(curr->id)) + "]");
                } else {
                    commands.push_back(curr->type);
                }
            }
        } else if(curr->left == prev) {
            stk.pop_back();
            if(curr->type == "VAL") {
                commands.push_back("PUSH " + to_string(curr->num));
            } else if(curr->type == "VAR") {
                commands.push_back("PUSH mem[" + to_string(targ.symtable->search(curr->id)) + "]");
            } else {
                commands.push_back(curr->type);
            }
        }
        prev = curr;
    }
    if(root->left->type == "VAR") {
        int m_loc = targ.symtable->search(root->left->id);
        if(m_loc == -1) {
            int min = least_mem_loc.get_min();
            if(min == -1) {
                m_loc = targ.symtable->get_size()-1;
            } else {
                m_loc = min;
                least_mem_loc.pop();
            }
            targ.symtable->assign_address(root->left->id, m_loc);
        }
        commands.push_back("mem[" + to_string(m_loc) + "] = POP");
    } else {
        commands.push_back("RET = POP");
    }
    return commands;
}

void EPPCompiler::write_to_file(vector<string> commands){
    ofstream out_file;
    out_file.open(output_file, ios::app);
    for(auto c: commands) {
        out_file << c << endl;
    }
    out_file << endl;
    out_file.close();
}

EPPCompiler::~EPPCompiler(){

}
