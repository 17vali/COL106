#include "LinearProbing.h"

void LinearProbing::createAccount(std::string id, int count) {
    int index = hash(id);
    for(int i = index; ; i = (i+1)%100000){
        if(bankStorage1d[i].id == ""){
            bankStorage1d[i].id = id;
            bankStorage1d[i].balance = count;
            size++;
            break;
        }
    }
}

std::vector<int> LinearProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    return std::vector<int>(); // Placeholder return value
}

int LinearProbing::getBalance(std::string id) {
    int index = hash(id);
    for(int i = index; ; i = (i+1)%100000){
        if(bankStorage1d[i].id == id){
            return bankStorage1d[i].balance;
        }
        if(bankStorage1d[i].id == ""){
            return -1;
        }
    }
}

void LinearProbing::addTransaction(std::string id, int count) {
    int index = hash(id);
    for(int i = index; ; i = (i+1)%100000){
        if(bankStorage1d[i].id == id){
            bankStorage1d[i].balance += count;
            break;
        }
        if(bankStorage1d[i].id == ""){
            break;
        }
    }
}

bool LinearProbing::doesExist(std::string id) {
    int index = hash(id);
    for(int i = index; ; i = (i+1)%100000){
        if(bankStorage1d[i].id == id){
            return true;
        }
        if(bankStorage1d[i].id == ""){
            return false;
        }
    }
}

bool LinearProbing::deleteAccount(std::string id) {
    int index = hash(id);
    for(int i = index; ; i = (i+1)%100000){
        if(bankStorage1d[i].id == id){
            bankStorage1d[i].id = "";
            bankStorage1d[i].balance = 0;
            size--;
            return true;
        }
        if(bankStorage1d[i].id == ""){
            return false;
        }
    }
}
int LinearProbing::databaseSize() {
    return size;
}

int LinearProbing::hash(std::string id) {
    int hash_value = 0;
    for (char c : id) {
        hash_value = (hash_value*31 + c - 'A' + 1) % 100000;
    }
    return hash_value;
}

