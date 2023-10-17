#include "Chaining.h"
#include "LinearProbing.h"
#include "QuadraticProbing.h"
#include "CubicProbing.h"
#include "Comp.h"
#include <cassert>

void testDatabase(BaseClass *db) {
    db->createAccount("1234", 1000);
    db->createAccount("Bob", 1500);
    db->createAccount("Charlie", 2000);
    db->createAccount("David", 1800);
    db->createAccount("Eve", 1500);

    assert(db->getBalance("1234") == 1000);
    assert(db->getBalance("Bob") == 1500);
    assert(db->getBalance("Charlie") == 2000);

    db->addTransaction("1234", -200);
    db->addTransaction("Bob", 300);
    db->addTransaction("Charlie", -600);

    assert(db->getBalance("1234") == 800);
    assert(db->getBalance("Bob") == 1800);
    assert(db->getBalance("Charlie") == 1400);

    std::vector<int> topBalances = db->getTopK(7);
    assert(topBalances.size() == 5);
    assert(topBalances[0] == 1800);
    assert(topBalances[1] == 1800);
    assert(topBalances[2] == 1500);
    assert(topBalances[3] == 1400);
    assert(topBalances[4] == 800);

    assert(db->databaseSize() == 5);

    assert(db->doesExist("1234"));
    assert(db->doesExist("Eve"));
    assert(!db->doesExist("Gabe"));
}


int main() {
    Chaining chainingDB;
    LinearProbing linearProbingDB;
    QuadraticProbing quadraticProbingDB;
    CubicProbing cubicProbingDB;
    Comp compDB;

    std::cout << "Testing Chaining:" << std::endl;
    testDatabase(&chainingDB);

    std::cout << "\nTesting Linear Probing:" << std::endl;
    testDatabase(&linearProbingDB);

    std::cout << "\nTesting Quadratic Probing:" << std::endl;
    testDatabase(&quadraticProbingDB);

    std::cout << "\nTesting Cubic Probing:" << std::endl;
    testDatabase(&cubicProbingDB);

    std::cout << "\nTesting Comp:" << std::endl;
    testDatabase(&compDB);

    std::cout << "\nAll tests passed!" << std::endl;
    return 0;
}
