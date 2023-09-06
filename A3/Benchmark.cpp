#include <iostream>
#include <unordered_map>
#include <vector>
#include <random>
#include "Chaining.h"
#include "LinearProbing.h"
#include "QuadraticProbing.h"
#include "CubicProbing.h"
#include "Comp.h"
#include <chrono>

using namespace std;

const int N = 100000;

vector<string> keys(N);
vector<int> values(N);

void testChaining() {
    Chaining c;
    for (int i = 0; i < N; i++) {
        c.createAccount(keys[i], values[i]);
        int val = c.getBalance(keys[i]);
        if (val != values[i]) cout<<("BRUH\n");
    }
}

void testLinearProbing() {
    LinearProbing lp;
    for (int i = 0; i < N; i++) {
        lp.createAccount(keys[i], values[i]);
        int val = lp.getBalance(keys[i]);
        if (val != values[i]) cout<<("BRUH\n");
    }
}

void testQuadraticProbing() {
    QuadraticProbing qp;
    for (int i = 0; i < N; i++) {
        qp.createAccount(keys[i], values[i]);
        int val = qp.getBalance(keys[i]);
        if (val != values[i]) cout<<("BRUH\n");
    }
}

void testCubicProbing() {
    CubicProbing cp;
    for (int i = 0; i < N; i++) {
        cp.createAccount(keys[i], values[i]);
        int val = cp.getBalance(keys[i]);
        if (val != values[i]) cout<<("BRUH\n");
    }
}

void testCompProbing() {
    Comp c;
    for (int i = 0; i < N; i++) {
        c.createAccount(keys[i], values[i]);
        int val = c.getBalance(keys[i]);
        if (val != values[i]) cout<<("BRUH\n");
    }
}

void testHashMapSpeed() {
    std::unordered_map<string, int> hashmap;
    for (int i = 0; i < N; i++) {
        hashmap[keys[i]] = values[i];
        int val = hashmap[keys[i]];
        if (val != values[i]) cout <<("BRUH\n");
    }
}

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> acc(1e9, 1e10-1);
    uniform_int_distribution<int> code(1e6, 1e7-1);
    uniform_int_distribution<int> dist(0, 1e9-1);
    uniform_int_distribution<int> ifsc(0, 25);

    for (int i = 0; i < N; i++) {
        char a = 'A' + ifsc(gen);
        char b = 'A' + ifsc(gen);
        char c = 'A' + ifsc(gen);
        char d = 'A' + ifsc(gen);
        keys[i] = (string(1, a) + string(1, b) + string(1, c) + string(1, d) + to_string(code(gen)) + '_' + to_string(acc(gen)));
        values[i] = dist(gen);
    }

    auto chainingStart = chrono::high_resolution_clock::now();
    testChaining();
    auto chainingEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> chainingDuration = chainingEnd - chainingStart;
    cout << "Chaining Time: " << chainingDuration.count() << " seconds\n";

    auto linearStart = chrono::high_resolution_clock::now();
    testLinearProbing();
    auto linearEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> linearDuration = linearEnd - linearStart;
    cout << "Linear Probing Time: " << linearDuration.count() << " seconds\n";

    auto quadraticStart = chrono::high_resolution_clock::now();
    testQuadraticProbing();
    auto quadraticEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> quadraticDuration = quadraticEnd - quadraticStart;
    cout << "Quadratic Probing Time: " << quadraticDuration.count() << " seconds\n";

    auto cubicStart = chrono::high_resolution_clock::now();
    testCubicProbing();
    auto cubicEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> cubicDuration = cubicEnd - cubicStart;
    cout << "Cubic Probing Time: " << cubicDuration.count() << " seconds\n";

    auto compStart = chrono::high_resolution_clock::now();
    testCompProbing();
    auto compEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> compDuration = compEnd - compStart;
    cout << "Comp Probing Time: " << compDuration.count() << " seconds\n";

    auto hashMapStart = chrono::high_resolution_clock::now();
    testHashMapSpeed();
    auto hashMapEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> hashMapDuration = hashMapEnd - hashMapStart;
    cout << "HashMap Time: " << hashMapDuration.count() << " seconds\n";

    return 0;
}
