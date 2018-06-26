#include <iostream>
#include <string>
#include "Database.hpp"


int main(){

    Dytz::Database database(R"(test.txt)");
    try {
        // s means a transaction
        database.process("PUT 1 111\nPUT 2 222\nPUT 3 333\nPUT 1 999\nGET 1\nGET 2\nGET 3\nGET 4\nDEL 1\nDEL 2\nDEL 3\nDEL 5");
        std::cout << database.getOutput().str() << '\n';
    }
    catch (...){
        std::cerr << "Unknown Error occurred.\n";
    }

}