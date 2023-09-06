#ifndef COMP_H
#define COMP_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Comp : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;

    Comp() {
        bankStorage1d.resize(200003);
        size = 0;
    }

    int hash2(std::string id, int h) {
        for (char c: id) {
            h ^= c;
            h *= 0x5bd1e995;
            h ^= h >> 15;
        }
        return h%200003;
    }

    void quickSort(std::vector<int>& arr, int left, int right) {
        int i = left, j = right;
        int tmp;
        int pivot = arr[(left + right) / 2];
        
        while (i <= j) {
            while (arr[i] > pivot)
                i++;
            while (arr[j] < pivot)
                j--;
            if (i <= j) {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                
                i++;
                j--;
            }
        };
        
        if (left < j)
            quickSort(arr, left, j);
        if (i < right)
            quickSort(arr, i, right);
    }
    
private:
    int size;
};

#endif // COMP_H
