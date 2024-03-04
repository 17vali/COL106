// Do NOT add any other includes
#include "search.h"

bool char_match(char a, char b){
    return a == b || (a >= 'A' && a <= 'Z' && a + 32 == b) || (a >= 'a' && a <= 'z' && a - 32 == b);
}

vector<int> bad_character_table(string pattern){
    vector<int> table(69, -1);
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

    // vector<int> table(69, pattern.length());
    // for(int i = 0; i < pattern.length(); i++){
    //     if(pattern[i] < 'A') {
    //         table[pattern[i] - 32] = pattern.length() - 1 - i;
    //     } else if(pattern[i] >= 'A' && pattern[i] <= 'Z'){
    //         table[pattern[i] - 26] = pattern.length() - 1 - i;
    //     } else {
    //         table[pattern[i] - 58] = pattern.length() - 1 - i;
    //     }
    // }
    // return table;
}

bool is_prefix(string pattern, int pos){
    for(int i = pos, j = 0; i < pattern.length(); i++, j++){
        if(!char_match(pattern[i], pattern[j])){
            return false;
        }
    }
    return true;
}

// vector<int> suffixes(string pattern) {
//     vector<int> suff(pattern.length());
//     suff[pattern.length() - 1] = pattern.length();
//     int g = pattern.length() - 1;
//     int f;
//     for(int i = pattern.length() - 2; i >= 0; i--){
//         if(i > g && suff[i + pattern.length() - 1 - f] < i - g){
//             suff[i] = suff[i + pattern.length() - 1 - f];
//         } else {
//             if(i < g){
//                 g = i;
//             }
//             f = i;
//             while(g >= 0 && char_match(pattern[g], pattern[g + pattern.length() - 1 - f])){
//                 g--;
//             }
//             suff[i] = f - g;
//         }
//     }
//     return suff;
// }

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
    // vector<int> table(pattern.length());

    // for(int i = 0; i < pattern.length(); i++){
    //     table[i] = pattern.length();
    // }
    // int j = 0;
    // for(int i = pattern.length() - 1; i >= 0; i--){
    //     if(suff[i] == i + 1){
    //         for(; j < pattern.length() - 1 - i; j++){
    //             if(table[j] == pattern.length()){
    //                 table[j] = pattern.length() - 1 - i;
    //             }
    //         }
    //     }
    // }
    // int l = pattern.length() - 2;
    // for(int i = 0; i <= l; i++){
    //     table[pattern.length() - 1 - suff[i]] = pattern.length() - 1 - i;
    // }
    // return table;
}

void boyer_moore(int book_code, int page, int paragraph, int sentence_no, string pattern, string text, Node* &head, int &n_matches, vector<int> bad_char, vector<int> good_suff){
    Node* l = nullptr;
    Node* r = nullptr;

    // vector<int> skip(pattern.length(), 0);

    // int s = 0;
    // int len = text.length() - pattern.length();
    // int shift;
    // while(s <= len){
    //     int j = pattern.length() - 1;
    //     while(j >= 0){
    //         int t = skip[j];
    //         int su = suff[j];
    //         if(t > 0){
    //             if(t > su){
    //                 if(j + 1 == su){
    //                     j--;
    //                 } else {
    //                     j -= su;
    //                 }
    //                 break;
    //             } else {
    //                 j -= t;
    //                 if(t < su){
    //                     break;
    //                 }
    //             }
    //         } else {
    //             if(char_match(pattern[j], text[s + j])){
    //                 j--;
    //             } else {
    //                 break;
    //             }
    //         }
    //     }
    //     if(j < 0){
    //         n_matches++;
    //         Node* temp = new Node(book_code, page, paragraph, sentence_no, s);
    //         if(l == nullptr){
    //             l = temp;
    //         } else {
    //             r->right = temp;
    //             temp->left = r;
    //         }
    //         r = temp;
    //         skip[pattern.length() - 1] = pattern.length();
    //         shift = good_suff[0];
    //     } else {
    //         skip[pattern.length() - 1] = pattern.length() - 1 - j;
    //         if(text[s+j] < 'A') {
    //             shift = max(good_suff[j], (int) (bad_char[text[s + j] - 32] - pattern.length() + 1 + j));
    //         } else if(text[s+j] >= 'A' && text[s+j] <= 'Z') {
    //             shift = max(good_suff[j], (int) (bad_char[text[s + j] - 26] - pattern.length() + 1 + j));
    //         } else {
    //             shift = max(good_suff[j], (int) (bad_char[text[s + j] - 58] - pattern.length() + 1 + j));
    //         }
    //     }
    //     s += shift;
    //     copy(skip.begin() + shift, skip.end(), skip.begin());
    //     fill(skip.begin() + pattern.length() - shift, skip.end(), 0);
    // }

    // int s = 0;
    // int u = 0;
    // int shift = pattern.length();
    // int len = text.length() - pattern.length();
    // while(s <= len){
    //     int j = pattern.length() - 1;
    //     while(j >= 0 && char_match(pattern[j], text[s + j])){
    //         j--;
    //         if(u != 0 && j == pattern.length() - 1 - shift){
    //             j -= u;
    //         }
    //     }
    //     if(j < 0){
    //         n_matches++;
    //         Node* temp = new Node(book_code, page, paragraph, sentence_no, s);
    //         if(l == nullptr){
    //             l = temp;
    //         } else {
    //             r->right = temp;
    //             temp->left = r;
    //         }
    //         r = temp;
    //         shift = good_suff[0];
    //         u = pattern.length() - shift;
    //     } else {
    //         int t_shift = u + j + 1 - pattern.length();
    //         int bc_shift;
    //         if(text[s+j] < 'A') {
    //             bc_shift = bad_char[text[s + j] - 32] - pattern.length() + 1 + j;
    //         } else if(text[s+j] >= 'A' && text[s+j] <= 'Z') {
    //             bc_shift = bad_char[text[s + j] - 26] - pattern.length() + 1 + j;
    //         } else {
    //             bc_shift = bad_char[text[s + j] - 58] - pattern.length() + 1 + j;
    //         }
    //         shift = max(t_shift, bc_shift);
    //         shift = max(shift, good_suff[j]);
    //         if(shift == good_suff[j]){
    //             u = pattern.length() - max(shift, j + 1);
    //         } else {
    //             if(t_shift < bc_shift){
    //                 shift = max(shift, u + 1);
    //             }
    //             u = 0;
    //         }
    //     }
    //     s += shift;
    // }

    // int s = 0;
    // int len = text.length() - pattern.length();
    // while(s <= len){
    //     int j = pattern.length() - 1;
    //     while(j >= 0 && char_match(pattern[j], text[s + j])){
    //         j--;
    //     }
    //     if(j < 0){
    //         n_matches++;
    //         Node* temp = new Node(book_code, page, paragraph, sentence_no, s);
    //         if(l == nullptr){
    //             l = temp;
    //         } else {
    //             r->right = temp;
    //             temp->left = r;
    //         }
    //         r = temp;
    //         s += good_suff[pattern.length()];
    //     } else {
    //         if(text[s+j] < 'A') {
    //             s+= j - min(good_suff[j], bad_char[text[s + j] - 32]);
    //         } else if(text[s+j] >= 'A' && text[s+j] <= 'Z') {
    //             s+= j - min(good_suff[j], bad_char[text[s + j] - 26]);
    //         } else {
    //             s+= j - min(good_suff[j], bad_char[text[s + j] - 58]);
    //         }
    //     }
    // }

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
            if(l == nullptr){
                l = temp;
            } else {
                r->right = temp;
                temp->left = r;
            }
            r = temp;
            if(text[s+pattern.length()] < 'A') {
                s+= (s + pattern.length() < text.length()) ? pattern.length() - bad_char[text[s + pattern.length()] - 32] : 1;
            } else if(text[s+pattern.length()] >= 'A' && text[s+pattern.length()] <= 'Z') {
                s+= (s + pattern.length() < text.length()) ? pattern.length() - bad_char[text[s + pattern.length()] - 26] : 1;
            } else {
                s+= (s + pattern.length() < text.length()) ? pattern.length() - bad_char[text[s + pattern.length()] - 58] : 1;
            }
        } else {
            if(text[s+j] < 'A') {
                s+= max(1, j - bad_char[text[s + j] - 32]);
            } else if(text[s+j] >= 'A' && text[s+j] <= 'Z') {
                s+= max(1, j - bad_char[text[s + j] - 26]);
            } else {
                s+= max(1, j - bad_char[text[s + j] - 58]);
            }
        }
    }

    if(r != nullptr){
        r->right = head;
        if(head!=nullptr) head->left = r;
        head = l;
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
    vector<int> bad_char = bad_character_table(pattern);
    // vector<int> suff = suffixes(pattern);
    vector<int> good_suff = good_suffix_table(pattern);

    Node* head = nullptr;
    Sentence* temp = sent_head;
    while(temp != nullptr){
        boyer_moore(temp->book_code, temp->page, temp->paragraph, temp->sentence_no, pattern, temp->sent, head, n_matches, bad_char, good_suff);
        temp = temp->next;
    }
    return head;
}