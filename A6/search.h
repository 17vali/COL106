// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

class Sentence{
public:
    int book_code;
    int page;
    int paragraph;
    int sentence_no;
    string sent;
    Sentence* next;

    Sentence(int b_code, int pg, int para, int s_no, string sent) {
        this->book_code = b_code;
        this->page = pg;
        this->paragraph = para;
        this->sentence_no = s_no;
        this->sent = sent;
    }
};

class SearchEngine {
private:
    Sentence* sent_head;

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);

    /* -----------------------------------------*/
};