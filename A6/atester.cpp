#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "dict.cpp"
#include "search.cpp"
#include "Node.cpp"
#define DUMP_FILE "dictionary_dump.txt"
using namespace std;
#define TC_DICT "testcase_dict.txt"
#define ANS_DICT "ans_dict.txt"
#define TC_SEARCH "testcase_search.txt"
#define ANS_SEARCH "ans_search.txt"
#define FILE_NAMES "files_gandhi49.txt"

struct Data {
    int book_code;
    int page_no;
    int para;
    int sentence;
};

int main() {
    Dict d;
    SearchEngine s;
    char mode = 'd';

    cout << "Tester for part 1 or 2? ";
    char m;
    cin >> m;
    if (m == '2')
        mode = 's';

    string ins;
    ifstream read_works;
    const string separators = " .,-:!\"\'()?—[];@";
    int arr[4];
    int line_count = 0;

    ifstream files;
    files.open(FILE_NAMES);
    string filename;

    ifstream testcase;
    vector<Node*> search_ans;
    cout << "Checking insert..\n";

    clock_t c_start = clock();
    auto t_start = chrono::high_resolution_clock::now();

    vector<string> sentences;
    vector<Data> metadata;

    while (getline(files, filename)) {
        read_works.open(filename);
        while (read_works.peek() != EOF) {
            getline(read_works, ins);
            line_count++;

            string info = "";
            string to_insert = "";
            int arrc = 0;
            bool flag1 = false, flag2 = false;

            for (auto c: ins) {
                if (flag1) {
                    if (flag2) {
                        to_insert = to_insert + c;
                    }
                    else
                        flag2 = true;
                } else {
                    if (c == ',') {
                        if (arrc == 0) {
                            arr[arrc] = stoi(info.substr(2, info.length() - 2));}
                        else {
                            arr[arrc] = stoi(info);
                        }
                        info = "";
                        arrc++;
                    } else {
                        info = info + c; 
                        if (c == ')')
                            flag1 = true;
                    }
                }
            }
            if (mode == 'd')
                d.insert_sentence(arr[0], arr[1], arr[2], arr[3], to_insert);
            if (mode == 's') {
                s.insert_sentence(arr[0], arr[1], arr[2], arr[3], to_insert);
                sentences.push_back(to_insert);
                metadata.push_back({arr[0], arr[1], arr[2], arr[3]});
            }
        }
        read_works.close();
    }
    clock_t c_end = clock();
    auto t_end = chrono::high_resolution_clock::now();
    cout << fixed << setprecision(2) << "Insert called on " << line_count << " lines successfully in " << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << "ms\n";
    files.close();

    if (mode == 's') {
        string calc;
        cout << "Compute search answers?(Y/N) ";
        cin >> calc;
        int sofar = 0;
        if (calc == "Y") {
            ofstream ans;
            testcase.open(TC_SEARCH);
            ans.open(ANS_SEARCH);
            string tc;
            while (getline(testcase, tc)) {
                transform(tc.begin(), tc.end(), tc.begin(), ::tolower);
                int ct = 0;
                Node* curr = nullptr;
                Node* head = nullptr;
                string to_write = "";
                for (size_t i=0;i<sentences.size();i++) {
                    string searchin = sentences[i];
                    transform(searchin.begin(), searchin.end(), searchin.begin(), ::tolower);
                    size_t loc = searchin.find(tc);
                    if (loc == string::npos)
                        continue;
                    while (loc != string::npos) {
                        ct++;
                        Node* currtmp = new Node(metadata[i].book_code, metadata[i].page_no, metadata[i].para, metadata[i].sentence, loc);
                        to_write += to_string(metadata[i].book_code) + " " + to_string(metadata[i].page_no) + " " + to_string(metadata[i].para) + " " + to_string(metadata[i].sentence) + " " + to_string(loc) + " ";
                        if (curr) {
                            currtmp->left = curr;
                            curr->right = currtmp;
                        }
                        if (!currtmp->left)
                            head = currtmp;
                        curr = currtmp;
                        loc = searchin.find(tc, loc + 1);
                    }
                }
                ans << to_string(ct) + " " + to_write + "\n";
                search_ans.push_back(head);
                sofar++;
                cout << "Answer " << sofar << " generated\n";
            }
            testcase.close();
            ans.close();
        } else {
            string sa;
            ifstream ans(ANS_SEARCH);
            while (getline(ans, sa)) {
                string ct, book, page, para, sent, offs;
                stringstream ans_info(sa);
                getline(ans_info, ct, ' ');
                Node* curr = nullptr;
                Node* head = nullptr;
                for (int var = 0;var < stoi(ct);var++) {
                    getline(ans_info, book, ' ');
                    getline(ans_info, page, ' ');
                    getline(ans_info, para, ' ');
                    getline(ans_info, sent, ' ');
                    getline(ans_info, offs, ' ');
                    Node* currtmp = new Node(stoi(book), stoi(page), stoi(para), stoi(sent), stoi(offs));
                    if (curr) {
                        currtmp->left = curr;
                        curr->right = currtmp;
                    }
                    if (!currtmp->left)
                        head = currtmp;
                    curr = currtmp;
                }
                search_ans.push_back(head);
                sofar++;
                cout << "Answer " << sofar << " read from file\n";
            }
        }
    }

    c_start = clock();
    t_start = chrono::high_resolution_clock::now();

    int i = 0;

    if (mode == 'd') {
        cout << "Checking word counts..\n";
        ifstream ans;
        testcase.open(TC_DICT);
        ans.open(ANS_DICT);
        
        string st;
        string sa;
        while (getline(testcase, st)) {
            getline(ans, sa);
            i++;
            int b = d.get_word_count(st);
            int c = stoi(sa);
            if (b != c) {
                cout << "Error in word count of " << st << ": expected " << c << ", received " << b << " (line " << i << ")\n";
                break;
            }
        }
        ans.close();
    }

    if (mode == 's') {
        cout << "Checking search..\n";
        testcase.open(TC_SEARCH);
        string st;
        while (getline(testcase, st)) {
            i++;
            int c = 0;
            Node* info = s.search(st, c);
            Node* info_ans = search_ans[i-1];
            int ct = 0;
            Node* curr = info_ans;
            while (curr) {
                ct++;
                curr = curr->right;
            }
            if (ct != c) {
                cout << "Error in number of matches of " << st << ": expected " << ct << ", received " << c << " (line " << i << ")\n";
                break;
            }

            Node* curr1 = info;
            Node* curr2 = info_ans;
            while (curr1 && curr2) {
                if (curr1->book_code != curr2->book_code || curr1->page != curr2->page || curr1->paragraph != curr2->paragraph || curr1->sentence_no != curr2->sentence_no || curr1->offset != curr2->offset) {
                    cout << "Error in match info of " << st << ": expected " << curr2->book_code << " " << curr2->page << " " << curr2->paragraph << " " << curr2->sentence_no << " " << curr2->offset << ", received " << curr1->book_code << " " << curr1->page << " " << curr1->paragraph << " " << curr1->sentence_no << " " << curr1->offset << " (line " << i << ")\n";
                    break;
                }
                curr1 = curr1->right;
                curr2 = curr2->right;
            }

            cout << "Search " << i << " successful\n";
        }
    }

    c_end = clock();
    t_end = chrono::high_resolution_clock::now();
    if (mode == 'd')
        cout << fixed << setprecision(2) << "Get word count called on " << i << " lines in " << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << "ms\n";
    if (mode == 's')
        cout << fixed << setprecision(2) << "Search pattern called on " << i << " lines in " << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << "ms\n";

    if (mode == 'd') {
        c_start = clock();
        t_start = chrono::high_resolution_clock::now();

        d.dump_dictionary(DUMP_FILE);

        c_end = clock();
        t_end = chrono::high_resolution_clock::now();
        cout << fixed << setprecision(2) << "Dictionary dumped in " << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << "ms\n";
    }

    return 0;
}