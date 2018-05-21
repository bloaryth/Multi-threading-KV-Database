#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include "TranMgnt/Database.h"
//#include "Sample/Database.h"

using namespace boost::property_tree;


int main(){

    sample::Database database(R"(test.txt)", R"(log.txt)");
    try {
        // s means a transaction
        database.process("PUT 1 111\nPUT 2 222\nPUT 3 333\nGET 1\nGET 2\nGET 3\nGET 4\nDEL 1\nDEL 2\nDEL 5");
        std::cout << database.getOutput().str() << '\n';
    }
    catch (...){
        std::cerr << "Unknown Error occurred.\n";
    }

}