#include "QuadraticProbing.h"

void QuadraticProbing::createAccount(std::string id, int count) {
    int index = hash(id);
    for(int i = index, n=-1; ; i = (i+2*(++n)+1)%100000){
        if(bankStorage1d[i].id == ""){
            bankStorage1d[i].id = id;
            bankStorage1d[i].balance = count;
            size++;
            break;
        }
    }
}

std::vector<int> QuadraticProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    return std::vector<int>(); // Placeholder return value
}

int QuadraticProbing::getBalance(std::string id) {
    int index = hash(id);
    for(int i = index, n=-1; ; i = (i+2*(++n)+1)%100000){
        if(bankStorage1d[i].id == id){
            return bankStorage1d[i].balance;
        }
        if(bankStorage1d[i].id == ""){
            return -1;
        }
    }
}

void QuadraticProbing::addTransaction(std::string id, int count) {
    int index = hash(id);
    for(int i = index, n=-1; ; i = (i+2*(++n)+1)%100000){
        if(bankStorage1d[i].id == id){
            bankStorage1d[i].balance += count;
            break;
        }
        if(bankStorage1d[i].id == ""){
            break;
        }
    }
}

bool QuadraticProbing::doesExist(std::string id) {
    int index = hash(id);
    for(int i = index, n=-1; ; i = (i+2*(++n)+1)%100000){
        if(bankStorage1d[i].id == id){
            return true;
        }
        if(bankStorage1d[i].id == ""){
            return false;
        }
    }
}

bool QuadraticProbing::deleteAccount(std::string id) {
    int index = hash(id);
    for(int i = index, n=-1; ; i = (i+2*(++n)+1)%100000){
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
int QuadraticProbing::databaseSize() {
    return size;
}

int QuadraticProbing::hash(std::string id) {
    int hash_value = 0;
    for (char c : id) {
        hash_value = (hash_value*31 + c - 'A' + 1) % 100000;
    }
    return hash_value;
}

