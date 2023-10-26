// Do NOT add any other includes
#include "search.h"

bool char_match(char a, char b){
    return a == b || (a >= 'A' && a <= 'Z' && a + 32 == b) || (a >= 'a' && a <= 'z' && a - 32 == b);
}

vector<int> bad_character_table(string pattern){
    vector<int> table(69, -1); //
    for(int i = 0; i < pattern.length(); i++){
        if(pattern[i] < 'A') {
            table[pattern[i] - 32] = i;
        } else if(pattern[i] >= 'A' && pattern[i] <= 'Z'){
            table[pattern[i] - 26] = i;
        } else {
            table[pattern[i] - 58] = i;
        }
    }
    return table;
}

bool is_prefix(string pattern, int pos){
    for(int i = pos, j = 0; i < pattern.length(); i++, j++){
        if(!char_match(pattern[i], pattern[j])){
            return false;
        }
    }
    return true;
}

vector<int> good_suffix_table(string pattern){
    int next = 1;
    vector<int> table(pattern.length()+1, 0);

    for(int i = pattern.length() - 1; i >= 0; i--){
        if(is_prefix(pattern, i + 1)){
            next = i + 1;
        }
        table[i] = i - next;
        if(i == 0){
            table[pattern.length()] = next;
        }
    }

    for(int i = 0; i < pattern.length() - 1; i++){
        int suff_len = 0;
        for(int j = i, k = pattern.length() - 1; j >= 0 && char_match(pattern[j], pattern[k]); j--, k--){
            suff_len++;
        }
        if(!char_match(pattern[i - suff_len], pattern[pattern.length() - suff_len - 1])) {
            table[pattern.length() - suff_len - 1] = i - suff_len;
        }
    }

    return table;
}

void boyer_moore(int book_code, int page, int paragraph, int sentence_no, string pattern, string text, Node* &head, int &n_matches){
    vector<int> bad_char = bad_character_table(pattern);
    vector<int> good_suff = good_suffix_table(pattern);

    int s = 0;
    int len = text.length() - pattern.length();
    while(s <= len){
        int j = pattern.length() - 1;
        while(j >= 0 && char_match(pattern[j], text[s + j])){
            j--;
        }
        if(j < 0){
            n_matches++;
            Node* temp = new Node(book_code, page, paragraph, sentence_no, s);
            temp->right = head;
            if(head!=nullptr) head->left = temp;
            head = temp;
            s += good_suff[pattern.length()];
        } else {
            if(text[s+j] < 'A') {
                s+= j - min(good_suff[j], bad_char[text[s + j] - 32]);
            } else if(text[s+j] >= 'A' && text[s+j] <= 'Z') {
                s+= j - min(good_suff[j], bad_char[text[s + j] - 26]);
            } else {
                s+= j - min(good_suff[j], bad_char[text[s + j] - 58]);
            }
        }
    }
}

SearchEngine::SearchEngine(){
    sent_head = nullptr;
}

SearchEngine::~SearchEngine(){
    while(sent_head != nullptr){
        Sentence* temp = sent_head;
        sent_head = sent_head->next;
        delete temp;
    }
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    Sentence* temp = new Sentence(book_code, page, paragraph, sentence_no, sentence);
    temp->next = sent_head;
    sent_head = temp;
}

Node* SearchEngine::search(string pattern, int& n_matches){
    Node* head = nullptr;
    Sentence* temp = sent_head;
    while(temp != nullptr){
        boyer_moore(temp->book_code, temp->page, temp->paragraph, temp->sentence_no, pattern, temp->sent, head, n_matches);
        temp = temp->next;
    }
    return head;
}