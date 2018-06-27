#include <iostream>
#include <string>
#include "Database.hpp"
#include <ctime>


int main(){
	
	clock_t stTime = clock();
	
    Dytz::Database database(R"(test.txt)");
    try {
        // s means a transaction
        //database.process("PUT 1 111\nPUT 2 222\nPUT 3 333\nPUT 1 999\nGET 1\nGET 2\nGET 3\nGET 4\nDEL 1\nDEL 2\nDEL 3\nDEL 5");
        //database.process("PUT 1 111\nPUT 2 222\nPUT 3 333\nPUT 1 999\nGET 1\nGET 2\nGET 3\nGET 4\nDEL 1\nDEL 2\nDEL 3\nDEL 5");
        
        std::ifstream in;
        in.open("C:\\Users\\qydyx\\Desktop\\databaseTest\\data.txt");
        
        database.process(in);
        
        std::cout << database.getOutput().str() << '\n';
    }
    catch (...){
        std::cerr << "Unknown Error occurred.\n";
    }
    
    clock_t edTime = clock();
    
    std::cerr << "Elapsed Time: " << (edTime - stTime) / (double)CLOCKS_PER_SEC << "\n";

}