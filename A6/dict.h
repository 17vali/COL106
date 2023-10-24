// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class TrieNode{
public:
    vector<TrieNode*> children;
    bool isEndOfWord;
    int count;

    TrieNode(){
        children = vector<TrieNode*>(54, nullptr);
        isEndOfWord = false;
        count = 0;
    }

    ~TrieNode(){
        // for(int i=0;i<36;i++){
        //     if(children[i]!=nullptr){
        //         delete children[i];
        //     }
        // }
        // delete this;
    }

    void dump(ofstream& file, string& word, int count){
        if(isEndOfWord){
            file<<word<<", "<<count<<endl;
        }
        for(int i=0;i<54;i++){
            if(children[i]!=nullptr){
                if(i<26){
                    word.push_back('a'+i);
                }
                else if(i<36){
                    word.push_back('0'+i-26);
                } else {
                    word.push_back("#$%&*+/<=>\\^_`{|}~"[i-36]);
                }
                children[i]->dump(file, word, children[i]->count);
                word.pop_back();
            }
        }
    }
};

class Dict {
private:
    TrieNode* root;
    string rem = "#$%&*+/<=>\\^_`{|}~";

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};