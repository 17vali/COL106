#include "Comp.h"

void Comp::createAccount(std::string id, int count) {
    int h = hash(id);
    int index = hash2(id, h);

    for(int i = index, d = 1 , n = -1; ; i = (index+d*h)%200003, d++){
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

std::vector<int> Comp::getTopK(int k) {
    std::vector<int> values;
    for(int i = 0; i < 200003; i++){
        if(bankStorage1d[i].id != "" && bankStorage1d[i].id != "DELETED"){
            values.push_back(bankStorage1d[i].balance);
        }
    }
    k = (k < size) ? k : size;
    quickSort(values, 0, values.size()-1);
    values.resize(k);
    return values;
}

int Comp::getBalance(std::string id) {
    int h = hash(id);
    int index = hash2(id, h);

    for(int i = index, d = 1 , n = -1; ; i = (index+d*h)%200003, d++){
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

void Comp::addTransaction(std::string id, int count) {
    int h = hash(id);
    int index = hash2(id, h);

    for(int i = index, d = 1 , n = -1; ; i = (index+d*h)%200003, d++){
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

bool Comp::doesExist(std::string id) {
    int h = hash(id);
    int index = hash2(id, h);

    for(int i = index, d = 1 , n = -1; ; i = (index+d*h)%200003, d++){
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

bool Comp::deleteAccount(std::string id) {
    int h = hash(id);
    int index = hash2(id, h);

    for(int i = index, d = 1 , n = -1; ; i = (index+d*h)%200003, d++){
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
int Comp::databaseSize() {
    return size;
}

int Comp::hash(std::string id) {
    int hash_value = 0;
    for (char c : id) {
        hash_value = (hash_value*31 + c) % 200003;
    }
    return hash_value;
}