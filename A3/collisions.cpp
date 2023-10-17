#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>  // Include the file handling library
#include <string> 
#include <cmath>  
#include <chrono>
using namespace std;
size_t customHash(const std::string& id) {
    int hash=0;
    for(char c: id)
    {
        hash += c;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash%172421;
    //^ 11810 (best) 0.117701

    // int h = 0x12345678;

    // h ^= 2166136261UL;
    // for(char c: id) {
    //     h ^= c;
    //     h *= 16777619;
    // }
    // return h%172421;
    //^ 11696 0.205374

    //172421
}

int main() {

    // Create a hash table to store key -> value pairs
    std::unordered_map<size_t, std::string> hashTable;

    int collisions = 0;
    std::ifstream inputFile("abcd.txt");

    if (!inputFile) {
        std::cerr << "Failed to open the input file." << std::endl;
        return 1;  // Exit with an error code
    }

    std::string line;
    auto Start = chrono::high_resolution_clock::now();
    while (std::getline(inputFile, line)) {
        std::string key = line.substr(1, line.length() - 2);
        size_t hash = customHash(key);

        // Check if the hash already exists in the hash table
        auto it = hashTable.find(hash);
        if (it != hashTable.end()) {
            // std::cout << "Collision: " << key << " and " << it->second << " hash to the same value " << hash << std::endl;
            collisions++;
        }

        // Store the hash -> key mapping in the hash table
        hashTable[hash] = key;
    }
    auto End = chrono::high_resolution_clock::now();
    chrono::duration<double> Duration = End - Start;

    std::cout << "Total collisions: " << collisions << std::endl;
    std::cout << "Total time: " << Duration.count() << std::endl;

    return 0;
}
