#include "QuadraticProbing.h"

void QuadraticProbing::createAccount(std::string id, int count) {
    if (used >= threshold) resize();
    int index = hash(id);
    for(int i = index, d = 1, n = -1; ; i = (index+((d*d + d)>>1))%capacity, d++){
        if(bankStorage1d[i].id == "DELETED"){
            if(n == -1) n = i;
            continue;
        }
        if(bankStorage1d[i].id == ""){
            if(n == -1) {
                bankStorage1d[i].id = id;
                bankStorage1d[i].balance = count;
                used++;
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

std::vector<int> QuadraticProbing::getTopK(int k) {
    std::vector<int> values;
    for(int i = 0; i < capacity; i++){
        if(bankStorage1d[i].id != "" && bankStorage1d[i].id != "DELETED"){
            values.push_back(bankStorage1d[i].balance);
        }
    }
    k = (k < size) ? k : size;
    quickSort(values, 0, values.size()-1);
    values.resize(k);
    return values;
}

int QuadraticProbing::getBalance(std::string id) {
    int index = hash(id);
    for(int i = index, d = 1, n = -1; ; i = (index+((d*d + d)>>1))%capacity, d++){
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

void QuadraticProbing::addTransaction(std::string id, int count) {
    if (used >= threshold) resize();
    int index = hash(id);
    for(int i = index, d = 1, n = -1; ; i = (index+((d*d + d)>>1))%capacity, d++){
        if(bankStorage1d[i].id == "DELETED"){
            if(n == -1) n = i;
            continue;
        }
        if(bankStorage1d[i].id == ""){
            if(n == -1) {
                bankStorage1d[i].id = id;
                bankStorage1d[i].balance = count;
                used++;
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

bool QuadraticProbing::doesExist(std::string id) {
    int index = hash(id);
    for(int i = index, d = 1, n = -1; ; i = (index+((d*d + d)>>1))%capacity, d++){
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

bool QuadraticProbing::deleteAccount(std::string id) {
    int index = hash(id);
    for(int i = index, d = 1, n = -1; ; i = (index+((d*d + d)>>1))%capacity, d++){
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
int QuadraticProbing::databaseSize() {
    return size;
}

int QuadraticProbing::hash(std::string id) {
    int hash_value = 0;
    for (char c : id) {
        hash_value = (hash_value*31 + c) % capacity;
    }
    return hash_value;
}

void QuadraticProbing::resize() {
    /*capacity = 2*capacity + 1;
    while (gcd(17, capacity) != 1) {
        capacity++;
    }*/
    capacity = 200003;
    threshold = static_cast<int>(capacity * loadFactor); 
    std::vector<Account> temp;
    for(int i = 0; i < bankStorage1d.size(); i++){
        if(bankStorage1d[i].id != "" && bankStorage1d[i].id != "DELETED"){
            temp.push_back(bankStorage1d[i]);
        }
    }
    bankStorage1d.clear();
    bankStorage1d.resize(capacity);
    used = 0, size = 0;
    for(int i = 0; i < temp.size(); i++){
        createAccount(temp[i].id, temp[i].balance);
    }
}