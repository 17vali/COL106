// Do NOT add any other includes
#include "dict.h"

Dict::Dict(){
    root = new TrieNode();
}

Dict::~Dict(){
    delete root;
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    TrieNode* curr = root;
    for(char w : sentence){
        int index;
        if(w>='a' && w<='z' ){
            index = w-'a';
        }
        else if(w>='A' && w<='Z'){
            index = w-'A';
        }
        else if(w>='0' && w<='9'){
            index = w-'0'+26;
        } 
        else{
            auto it = rem.find(w);
            if(it!=string::npos){
                index = it+36;
            } else {
                if(curr!=root){
                    curr->isEndOfWord = true;
                    curr->count++;
                    curr = root;
                }
                continue;
            }
        }
        if(index >= curr->children.size()) {
            curr->children.resize(index+1, nullptr);
        }
        if(curr->children[index]==nullptr){
            curr->children[index] = new TrieNode();
        }
        curr = curr->children[index];
    }
    if(curr!=root){
        curr->isEndOfWord = true;
        curr->count++;
    }
}

int Dict::get_word_count(string word){
    TrieNode* curr = root;
    for(char w : word){
        int index;
        if(w>='a' && w<='z'){
            index = w-'a';
        }
        else if(w>='A' && w<='Z'){
            index = w-'A';
        }
        else if(w>='0' && w<='9'){
            index = w-'0'+26;
        }
        else{
            auto it = rem.find(w);
            if(it!=string::npos){
                index = it+36;
            } else {
                return 0;
            }
        }
        if(curr->children[index]==nullptr){
            return 0;
        }
        curr = curr->children[index];
    }
    if(curr->isEndOfWord){
        return curr->count;
    }
    return 0;
}

void Dict::dump_dictionary(string filename){
    ofstream file;
    file.open(filename);
    string word;
    root->dump(file, word, root->count);
    file.close();
}