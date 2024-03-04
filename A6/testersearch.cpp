#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "search.h"
#include <chrono>
#define file_ct 98

int main() {
    SearchEngine s;
    auto start = std::chrono::high_resolution_clock::now();
    const std::string FILENAME_PREFIX = "./txtfiles/mahatma-gandhi-collected-works-volume-";

    for (int i = 1; i <= file_ct; i++) {
        std::ifstream inputFile(FILENAME_PREFIX + std::to_string(i) + ".txt");

        if (!inputFile.is_open()) {
            std::cerr << "Error: Unable to open the input file." << std::endl;
            return 1;
        }

        std::string tuple;
        std::string sentence;
        while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
            tuple += ')';
            std::vector<int> metadata;
            std::istringstream iss(tuple);
            std::string token;

            // Ignore the first character (the opening parenthesis)
            iss.ignore(1);

            // Parse and convert the elements to integers
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
                    metadata.push_back(num);
                } else {
                    // Convert the element to integer
                    int num = std::stoi(token);
                    metadata.push_back(num);
                }
            }

            // Insert in the dictionary
            s.insert_sentence(metadata[0], metadata[1], metadata[2], metadata[3], sentence);
        }

        inputFile.close();
    }

    int n_counts = 0;
    Node* head = s.search("satisfaction" , n_counts);
    std::cout << "We have a total of " << n_counts << " matching counts." << std::endl;

    // while(head != nullptr) {
    //     std::cout << head->book_code << ", " << head->page << ", " << head->paragraph << ", " << head->sentence_no << ", " << head->offset << std::endl;
    //     head = head->right;
    // }
    
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by the process: " << duration.count()*0.000001 << " seconds" << std::endl;
    // Print the matched sentences if needed
    // printBaseline(s.extract_baseline(head));
    
    // Clean up memory if necessary

    while(head != nullptr) {
        Node* temp = head;
        head = head->right;
        delete temp;
    }

    return 0;
}
