//
// Created by wanton-wind on 2018/5/6.
//

#ifndef SYSTEM2018_DATABASE_DATA_H
#define SYSTEM2018_DATABASE_DATA_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <fstream>
#include <iostream>

class DataSet final {
public:
    using ptree = boost::property_tree::ptree;
    using key_type = std::string;
    using value_type = std::string;

private:
    std::string fileName;
    ptree data;

public:
    DataSet(std::string fileName): fileName(fileName) {
        std::fstream fs{fileName};
        if (fs.bad()){
            std::cerr << "read file faild.\n";
        }
        std::stringstream ss;
        ss << fs.rdbuf();
        try {
            boost::property_tree::read_json(ss, data);
        }
        catch (...){    // ptree_error
            std::cerr << "json is corrupted\n";
        }
    }

    ~DataSet() {
        std::ofstream fs{fileName};
        std::stringstream ss;
        boost::property_tree::write_json(ss, data);
        fs << ss.rdbuf();
        fs.close();
    }

    value_type get(key_type key) {
        return data.get<value_type>(key);
    }

    DataSet & put(key_type key, value_type value) {
        data.put(key, value);
        return *this;
    }

    DataSet & del(key_type key) {
        data.erase(key);
        return *this;
    }

};

#endif //SYSTEM2018_DATABASE_DATA_H
