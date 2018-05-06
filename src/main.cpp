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
        database.process("PUT 3 333\nPUT 1 111\nGET 2\nGET 1\n");
        std::cout << database.getOutput().str();
    }
    catch (ptree_error& e){
        std::cerr << e.what() << '\n';
    }

}