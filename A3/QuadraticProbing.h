#ifndef QUADRATICPROBING_H
#define QUADRATICPROBING_H

#include "BaseClass.h"
#include <iostream>

class QuadraticProbing : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;

    QuadraticProbing() {
        size = 0, used = 0, capacity = 7, threshold = static_cast<int>(capacity * loadFactor);
        bankStorage1d.resize(7);
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
    int size, threshold, capacity, used;
    double loadFactor = 0.65;
    void resize();
};

#endif // QUADRATICPROBING_H
