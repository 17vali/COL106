#include "QuadraticProbing.h"

void QuadraticProbing::createAccount(std::string id, int count) {
    int index = hash(id);
    for(int i = index, n=-1; ; i = (i+2*(++n)+1)%100003){
        if(bankStorage1d[i].id == ""){
            bankStorage1d[i].id = id;
            bankStorage1d[i].balance = count;
            size++;
            break;
        }
    }
}

std::vector<int> QuadraticProbing::getTopK(int k) {
    std::vector<int> values;
    for(int i = 0; i < 100003; i++){
        if(bankStorage1d[i].id != ""){
            values.push_back(bankStorage1d[i].balance);
        }
    }
    for(int i = 0; i < k; i++){
        while(true) {
            int smallest = i;
            if (2*i+1<k && values[2*i+1] < values[smallest]) {
                smallest = 2*i+1;
            }
            if (2*i+2<k && values[2*i+2] < values[smallest]) {
                smallest = 2*i+2;
            }
            if (smallest == i) {
                break;
            }
            int temp = values[i];
            values[i] = values[smallest];
            values[smallest] = temp;
            i = smallest;
        }
    }

    for (int i = k; i < size; i++) {
        if (values[0] > values[i])
            continue;
        else {
            values[0] = values[i];
            int j = 0;
            while(true) {
                int smallest = j;
                if (2*j+1<k && values[2*j+1] < values[smallest]) {
                    smallest = 2*j+1;
                }
                if (2*j+2<k && values[2*j+2] < values[smallest]) {
                    smallest = 2*j+2;
                }
                if (smallest == j) {
                    break;
                }
                int temp = values[j];
                values[j] = values[smallest];
                values[smallest] = temp;
                j = smallest;
            }
        }
    }

    values.resize(k);

    for(int l=0, j=k-1; l<j; l++, j--){
        int temp = values[l];
        values[l] = values[j];
        values[j] = temp;
    }
    return values;
}

int QuadraticProbing::getBalance(std::string id) {
    int index = hash(id);
    for(int i = index, n=-1; ; i = (i+2*(++n)+1)%100003){
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
    for(int i = index, n=-1; ; i = (i+2*(++n)+1)%100003){
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
    for(int i = index, n=-1; ; i = (i+2*(++n)+1)%100003){
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
    for(int i = index, n=-1; ; i = (i+2*(++n)+1)%100003){
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
        hash_value = (hash_value*31 + c - 'A' + 1) % 100003;
    }
    return hash_value;
}

