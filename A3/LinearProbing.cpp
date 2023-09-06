#include "LinearProbing.h"

void LinearProbing::createAccount(std::string id, int count) {
    int index = hash(id);
    for(int i = index, n = -1; ; i = (i+1)%172421){
        if(bankStorage1d[i].id == "DELETED"){
            if(n == -1) n = i;
            continue;
        }
        if(bankStorage1d[i].id == ""){
            if(n == -1) {
                bankStorage1d[i].id = id;
                bankStorage1d[i].balance = count;
            } else {
                bankStorage1d[n].id = id;
                bankStorage1d[n].balance = count;
            }
            size++;
            return;
        }
        if(bankStorage1d[i].id == id){
            if (n != -1) {
                bankStorage1d[n].id = id;
                bankStorage1d[n].balance = count;
                bankStorage1d[i].id = "DELETED";
                bankStorage1d[i].balance = 0;
            } else {
                bankStorage1d[i].balance = count;
            }
            return;
        }
    }
}

std::vector<int> LinearProbing::getTopK(int k) {
    std::vector<int> values;
    for(int i = 0, n = -1; i < 172421; i++){
        if(bankStorage1d[i].id != "" && bankStorage1d[i].id != "DELETED"){
            values.push_back(bankStorage1d[i].balance);
        }
    }
    k = (k < size) ? k : size;
    quickSort(values, 0, values.size()-1);
    values.resize(k);
    return values;
}

int LinearProbing::getBalance(std::string id) {
    int index = hash(id);
    for(int i = index, n = -1; ; i = (i+1)%172421){
        if(bankStorage1d[i].id == "DELETED"){
            if(n == -1) n = i;
            continue;
        }
        if(bankStorage1d[i].id == ""){
            return -1;
        }
        if(bankStorage1d[i].id == id){
            if (n != -1) {
                bankStorage1d[n].id = bankStorage1d[i].id;
                bankStorage1d[n].balance = bankStorage1d[i].balance;
                bankStorage1d[i].id = "DELETED";
                bankStorage1d[i].balance = 0;
                return bankStorage1d[n].balance;
            } else {
                return bankStorage1d[i].balance;
            }
        }
    }
}

void LinearProbing::addTransaction(std::string id, int count) {
    int index = hash(id);
    for(int i = index, n = -1; ; i = (i+1)%172421){
        if(bankStorage1d[i].id == "DELETED"){
            if(n == -1) n = i;
            continue;
        }
        if(bankStorage1d[i].id == ""){
            if(n == -1) {
                bankStorage1d[i].id = id;
                bankStorage1d[i].balance = count;
            } else {
                bankStorage1d[n].id = id;
                bankStorage1d[n].balance = count;
            }
            size++;
            return;
        }
        if(bankStorage1d[i].id == id){
            if (n != -1) {
                bankStorage1d[n].id = id;
                bankStorage1d[n].balance = bankStorage1d[i].balance + count;
                bankStorage1d[i].id = "DELETED";
                bankStorage1d[i].balance = 0;
            } else {
                bankStorage1d[i].balance += count;
            }
            return;
        }
    }
}

bool LinearProbing::doesExist(std::string id) {
    int index = hash(id);
    for(int i = index, n = -1; ; i = (i+1)%172421){
        if(bankStorage1d[i].id == "DELETED"){
            if(n == -1) n = i;
            continue;
        }
        if(bankStorage1d[i].id == ""){
            return false;
        }
        if(bankStorage1d[i].id == id){

            if(n != -1) {
                bankStorage1d[n].id = bankStorage1d[i].id;
                bankStorage1d[n].balance = bankStorage1d[i].balance;
                bankStorage1d[i].id = "DELETED";
                bankStorage1d[i].balance = 0;
            }
            return true;
        }
    }
}

bool LinearProbing::deleteAccount(std::string id) {
    int index = hash(id);
    for(int i = index; ; i = (i+1)%172421){
        if(bankStorage1d[i].id == "DELETED"){
            continue;
        }
        if(bankStorage1d[i].id == ""){
            return false;
        }
        if(bankStorage1d[i].id == id){
            bankStorage1d[i].id = "DELETED";
            bankStorage1d[i].balance = 0;
            size--;
            return true;
        }
    }
}
int LinearProbing::databaseSize() {
    return size;
}

int LinearProbing::hash(std::string id) {
    int hash_value = 0;
    for (char c : id) {
        hash_value = (hash_value*31 + c) % 172421;
    }
    return hash_value;
}