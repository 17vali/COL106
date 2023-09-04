#include "Chaining.h"

void Chaining::createAccount(std::string id, int count) {
    int index = hash(id);
    Account* account = search(id, index);
    if (account == nullptr) {
        bankStorage2d[index].push_back(Account{id, count});
        size++;
    }
}

std::vector<int> Chaining::getTopK(int k) {
    std::vector<int> values;
    for(int i = 0; i < 100003; i++){
        for(Account& account : bankStorage2d[i]) {
            values.push_back(account.balance);
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

int Chaining::getBalance(std::string id) {
    int index = hash(id);
    Account* account = search(id, index);
    if (account == nullptr) {
        return -1;
    }
    return account->balance;
}

void Chaining::addTransaction(std::string id, int count) {
    int index = hash(id);
    Account* account = search(id, index);
    if (account == nullptr) {
        return;
    }
    account->balance += count;
}

bool Chaining::doesExist(std::string id) {
    int index = hash(id);
    Account* account = search(id, index);
    return account != nullptr;
}

bool Chaining::deleteAccount(std::string id) {
    int index = hash(id);
    Account* account = search(id, index);
    if (account == nullptr) {
        return false;
    }
    int i = account - &bankStorage2d[index][0];
    bankStorage2d[index].erase(bankStorage2d[index].begin() + i);
    size--;
    return true;
}
int Chaining::databaseSize() {
    return size;
}

int Chaining::hash(std::string id) {
    int hash_value = 0;
    for (char c : id) {
        hash_value = (hash_value*31 + c - 'A' + 1) % 100003;
    }
    return hash_value;
}

Account* Chaining::search(std::string id, int index) {
    if (bankStorage2d[index].size() == 0) {
        return nullptr;
    }
    for(Account& account : bankStorage2d[index]) {
        if (account.id == id) {
            return &account;
        }
    }
    return nullptr;
}