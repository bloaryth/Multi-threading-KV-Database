#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include "Sample/Database.h"

using namespace boost::property_tree;


int main(){

    sample::Database database(R"(test.json)");
    try {
        // s means a transaction
        database.process("PUT 1 111\nPUT 2 222\nPUT 3 333\nGET 1\nGET 2\nGET 3\nDEL 1\nDEL 2");
        std::cout << database.getOutput().str();
    }
    catch (ptree_error& e){
        std::cerr << e.what() << '\n';
    }

}