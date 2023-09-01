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
    // IMPLEMENT YOUR CODE HERE
    return std::vector<int>(); // Placeholder return value
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
        hash_value = (hash_value*31 + c - 'A' + 1) % 100000;
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