#include <assert.h>
#include <sstream>
#include "qna_tool.h"

using namespace std;

class AVLNode {
public:
    int book_code;
    int page;
    int paragraph;
    double score;
    int height;
    
    AVLNode* par = nullptr;
    AVLNode* left = nullptr;
    AVLNode* right = nullptr;

    AVLNode(int b_code, int pg, int para, double sc) {
        book_code = b_code;
        page = pg;
        paragraph = para;
        score = sc;
        height = 0;
    }

    AVLNode* LeftLeftRotation(){
        AVLNode* r = this->right;
        AVLNode* rl = r->left;

        r->par = this->par;
        if(r->par == nullptr) ;
        else if(r->par->left == this) r->par->left = r;
        else r->par->right = r;

        r->left = this;
        this->par = r;
        this->right = rl;
        if(rl != nullptr) rl->par = this;

        int l_height = this->left == nullptr ? -1 : this->left->height;
        int r_height = this->right == nullptr ? -1 : this->right->height;

        this->height = max(l_height, r_height) + 1;

        int rl_height = r->left == nullptr ? -1 : r->left->height;
        int rr_height = r->right == nullptr ? -1 : r->right->height;

        r->height = max(rl_height, rr_height) + 1;

        return r;
    }

    AVLNode* RightRightRotation(){
        AVLNode* l = this->left;
        AVLNode* lr = l->right;

        l->par = this->par;
        if(l->par == nullptr) ;
        else if(l->par->left == this) l->par->left = l;
        else l->par->right = l;

        l->right = this;
        this->par = l;
        this->left = lr;
        if(lr != nullptr) lr->par = this;

        int l_height = this->left == nullptr ? -1 : this->left->height;
        int r_height = this->right == nullptr ? -1 : this->right->height;

        this->height = max(l_height, r_height) + 1;

        int ll_height = l->left == nullptr ? -1 : l->left->height;
        int lr_height = l->right == nullptr ? -1 : l->right->height;

        l->height = max(ll_height, lr_height) + 1;

        return l;
    }

    AVLNode* LeftRightRotation(){
        this->left = this->left->LeftLeftRotation();
        return this->RightRightRotation();
    }

    AVLNode* RightLeftRotation(){
        this->right = this->right->RightRightRotation();
        return this->LeftLeftRotation();
    }

    ~AVLNode() {
        if(left != nullptr) delete left;
        if(right != nullptr) delete right;
    }
};

void insert_avl(int b_code, int pg, int para, double sc, AVLNode*& avl_root, int& avl_size) {
    AVLNode* curr = avl_root;
    AVLNode* parent = nullptr;
    while(curr!=nullptr) {
        if(curr->book_code == b_code && curr->page == pg && curr->paragraph == para) {
            curr->score += sc;
            return;
        }
        parent = curr;
        if(b_code < curr->book_code || (b_code == curr->book_code && (pg < curr->page || (pg == curr->page && para < curr->paragraph)))) curr = curr->left;
        else curr = curr->right;
    }

    if(parent == nullptr) {
        avl_root = new AVLNode(b_code, pg, para, sc);
    }
    else if(b_code < parent->book_code || (b_code == parent->book_code && (pg < parent->page || (pg == parent->page && (para < parent->paragraph))))) {
        parent->left = new AVLNode(b_code, pg, para, sc);
        parent->left->par = parent;
    }
    else {
        parent->right = new AVLNode(b_code, pg, para, sc);
        parent->right->par = parent;
    }
    avl_size++;

    while(parent!=nullptr) {
        int l_height = parent->left == nullptr ? -1 : parent->left->height;
        int r_height = parent->right == nullptr ? -1 : parent->right->height;
        parent->height = max(l_height, r_height) + 1;
        int balance = l_height - r_height;
        if(balance > 1) {
            int ll_height = parent->left->left == nullptr ? -1 : parent->left->left->height;
            int lr_height = parent->left->right == nullptr ? -1 : parent->left->right->height;
            if(ll_height >= lr_height) {
                parent = parent->RightRightRotation();
                if(parent->par == nullptr) avl_root = parent;
            }
            else {
                parent = parent->LeftRightRotation();
                if(parent->par == nullptr) avl_root = parent;
            }
        }
        else if(balance < -1) {
            int rl_height = parent->right->left == nullptr ? -1 : parent->right->left->height;
            int rr_height = parent->right->right == nullptr ? -1 : parent->right->right->height;
            if(rr_height >= rl_height) {
                parent = parent->LeftLeftRotation();
                if(parent->par == nullptr) avl_root = parent;
            }
            else {
                parent = parent->RightLeftRotation();
                if(parent->par == nullptr) avl_root = parent;
            }
        }
        parent = parent->par;
    }
}

void heapify_down(vector<AVLNode*>& heap, int i, int sz) {
    while(i < sz) {
        int l = 2*i + 1;
        int r = 2*i + 2;
        int min_idx = i;
        if(l < sz && heap[l]->score < heap[min_idx]->score) min_idx = l;
        if(r < sz && heap[r]->score < heap[min_idx]->score) min_idx = r;
        if(min_idx == i) break;
        AVLNode* temp = heap[i];
        heap[i] = heap[min_idx];
        heap[min_idx] = temp;
        i = min_idx;
    }
}

QNA_tool::QNA_tool(){
    root = new TrieNode();
    ifstream file("unigram_freq.csv");
    string line;
    while(getline(file, line)) {
        if (line == "word,count") continue;
        TrieNode* curr = root;
        int c = 0;
        for(char w : line) {
            int index;
            c++;
            if(w>='a' && w<='z'){
                index = w-'a';
            }
            else{
                break;
            }
            if(curr->children.size() <= index) {
                curr->children.resize(index+1, nullptr);
            }
            if(curr->children[index]==nullptr){
                curr->children[index] = new TrieNode();
            }
            curr = curr->children[index];
        }
        curr->g_count = stoll(line.substr(c));
    }
    file.close();
}

QNA_tool::~QNA_tool(){
    delete root; 
}

void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    TrieNode* curr = root;
    for(char w : sentence){
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
                if(curr!=root){
                    curr->isEndOfWord = true;
                    curr->count++;
                    int size = curr->sentences.size();
                    if(size == 0 || curr->sentences[size-1]->paragraph != paragraph || curr->sentences[size-1]->page != page || curr->sentences[size-1]->book_code != book_code){
                        curr->sentences.push_back(new Sentence(book_code, page, paragraph));
                        size++;
                    }
                    curr->sentences[size-1]->count++;
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
        int size = curr->sentences.size();
        if(size == 0 || curr->sentences[size-1]->paragraph != paragraph || curr->sentences[size-1]->page != page || curr->sentences[size-1]->book_code != book_code){
            curr->sentences.push_back(new Sentence(book_code, page, paragraph));
            size++;
        }
        curr->sentences[size-1]->count++;
    }
}

Node* QNA_tool::get_top_k_para(string question, int k) {
    AVLNode* avl_root = nullptr;
    int avl_size = 0;

    TrieNode* curr = root;
    bool flag = false;

    for(char w : question){
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
                if(curr!=root && !flag){
                    double sc = (double) (curr->count + 1) / (double) (curr->g_count + 1);
                    for(Sentence* s : curr->sentences){
                        double f_sc = (double) s->count * sc;
                        insert_avl(s->book_code, s->page, s->paragraph, f_sc, avl_root, avl_size);
                    }
                }
                flag = false;
                curr = root;
                continue;
            }
        }
        if(flag) continue;
        if(curr->children[index]==nullptr){
            flag = true;
            continue;
        }
        curr = curr->children[index];
    }
    if(curr!=root && !flag){
        double sc = (double) (curr->count + 1) / (double) (curr->g_count + 1);
        for(Sentence* s : curr->sentences){
            double f_sc = (double) s->count * sc;
            insert_avl(s->book_code, s->page, s->paragraph, f_sc, avl_root, avl_size);
        }
    }

    vector<AVLNode*> stk;
    vector<AVLNode*> heap;

    stk.push_back(avl_root);

    while(!stk.empty()){
        AVLNode* curr = stk.back();
        stk.pop_back();
        if(heap.size() < k) {
            heap.push_back(curr);
            if(heap.size() == k){
                for(int i=k/2-1;i>=0;i--){
                    heapify_down(heap, i, k);
                }
            }
        } else {
            if(curr->score > heap[0]->score) {
                heap[0] = curr;
                heapify_down(heap, 0, k);
            }
        }
        
        if(curr->right!=nullptr) stk.push_back(curr->right);
        if(curr->left!=nullptr) stk.push_back(curr->left);
    }

    Node* res = nullptr;

    while(heap.size() > 0){
        AVLNode* curr = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify_down(heap, 0, heap.size());
        Node* temp = new Node(curr->book_code, curr->page, curr->paragraph, 0, 0);
        temp->right = res;
        if(res != nullptr) res->left = temp;
        res = temp;
    }

    delete avl_root;

    return res;
}

Node* QNA_tool::c_get_top_k_para(string question, int k, int k1) {
    AVLNode* avl_root = nullptr;
    int avl_size = 0;

    TrieNode* curr = root;
    bool flag = false;

    for(char w : question){
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
                if(curr!=root && !flag){
                    double sc = (double) (curr->count + 1) / (double) (curr->g_count + 1);
                    for(Sentence* s : curr->sentences){
                        double f_sc = (double) (s->count * sc * (1 + k1)) / (double) (s->count + k1);
                        // double f_sc = (double) s->count * sc;
                        // double f_sc = log(1 + s->count);
                        insert_avl(s->book_code, s->page, s->paragraph, f_sc, avl_root, avl_size);
                    }
                }
                flag = false;
                curr = root;
                continue;
            }
        }
        if(flag) continue;
        if(curr->children[index]==nullptr){
            flag = true;
            continue;
        }
        curr = curr->children[index];
    }
    if(curr!=root && !flag){
        double sc = (double) (curr->count + 1) / (double) (curr->g_count + 1);
        for(Sentence* s : curr->sentences){
            double f_sc = (double) (s->count * sc * (1 + k1)) / (double) (s->count + k1);
            // double f_sc = (double) s->count * sc;
            // double f_sc = log(1 + s->count);
            insert_avl(s->book_code, s->page, s->paragraph, f_sc, avl_root, avl_size);
        }
    }

    vector<AVLNode*> stk;
    vector<AVLNode*> heap;

    stk.push_back(avl_root);

    while(!stk.empty()){
        AVLNode* curr = stk.back();
        stk.pop_back();
        if(heap.size() < k) {
            heap.push_back(curr);
            if(heap.size() == k){
                for(int i=k/2-1;i>=0;i--){
                    heapify_down(heap, i, k);
                }
            }
        } else {
            if(curr->score > heap[0]->score) {
                heap[0] = curr;
                heapify_down(heap, 0, k);
            }
        }
        
        if(curr->right!=nullptr) stk.push_back(curr->right);
        if(curr->left!=nullptr) stk.push_back(curr->left);
    }

    Node* res = nullptr;

    while(heap.size() > 0){
        AVLNode* curr = heap[0];
        cout << curr->score << endl;
        heap[0] = heap.back();
        heap.pop_back();
        heapify_down(heap, 0, heap.size());
        Node* temp = new Node(curr->book_code, curr->page, curr->paragraph, 0, 0);
        temp->right = res;
        if(res != nullptr) res->left = temp;
        res = temp;
    }

    delete avl_root;

    return res;
}

void QNA_tool::query(string question, string filename){ 
    std::cout << "Q: " << question << std::endl;

    vector<string> stopwords = {"gandhiji", "gandhi", "mahatma", "views", "view"};

    for(string s : stopwords){
        TrieNode* curr = root;
        for(char c : s) {
            int index = c - 'a';
            curr = curr->children[index];
        }
        curr->g_count *= 10000;
    }

    query_llm_keywords(filename, "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", question);

    ifstream file("keywords.txt");
    string line;
    string keywords = "";
    while(getline(file, line)) {
        keywords += line;
    }
    file.close();

    query_llm(filename, c_get_top_k_para(keywords, 7, 1.2), 7, "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", question);

    for(string s : stopwords) {
        TrieNode* curr = root;
        for(char c : s) {
            int index = c - 'a';
            curr = curr->children[index];
        }
        curr->g_count /= 10000;
    }

    return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph){

    cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;
    
    std::string filename = "corpus/mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in the sentence
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos) {
                token = token.substr(start, end - start + 1);
            }
            
            // Check if the element is a number or a string
            if (token[0] == '\'') {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            } else {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if(
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph)
        ){
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}

void QNA_tool::query_llm(string filename, Node* root, int k, string API_KEY, string question){

    // first write the k paragraphs into different files

    Node* traverse = root;
    int num_paragraph = 0;

    while(num_paragraph < k){
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        // delete the file if it exists
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    ofstream outfile("query.txt");
    outfile << "I will provide some text/context .You have to only use that text to answer a question. you should not use any other information . You must infer the answer from the test given that the answer might not be explicitly defined in the text. Also quote relevant pieces from the text given supporting  the answer generated for the query give. Provide the answer with what you infer and then quote small pieces from text.\nQuestion - ";
    outfile << question;
    outfile << "\nContext - ";
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();

    // you do not need to necessarily provide k paragraphs - can configure yourself

    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    
    return;
}

void QNA_tool::query_llm_keywords(string filename, string API_KEY, string question){

    ofstream outfile("keyword_query.txt");
    outfile << "Generate a list of single-word keywords related to a query considering variations and synonyms. The keywords should be straightforward , simple and suitable for search purposes. What I want is to search for these words in a corpus of text. Sometimes the exact words of queries are not match so I want a list of words from you to whom I can search for similar contextual words derived from the context of the query and nothing else. Give the words in a single line only. Include variations of a single word . eg affair, affairs, Christianity , Christian, flavour, flavours. Also don't give words which introduce something new into the context because it will ruin the contextual similarity search I am trying to achieve. Query - ";
    outfile << question;
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();

    // you do not need to necessarily provide k paragraphs - can configure yourself

    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += "keyword_query.txt";

    system(command.c_str());
    
    return;
}