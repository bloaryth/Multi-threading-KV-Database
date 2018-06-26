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
#include "BpTree.hpp"
#include "Logger/Logger.h"


class DataSet {
public:
	using key_type = int;
	using value_type = std::string;

private:
	std::string fileName;
	BpTree data;
	Logger & logger;

public:
	DataSet(std::string fileName, Logger& logger) : fileName{ fileName }, data{ fileName.c_str() }, logger{ logger } {

	}

	value_type get(key_type key) {
		// TODO log
		std::string str = data.get(key).str;
		if (str == "") {
			std::cerr << "Get " << key << " failed.\n";
		}
		return str;
	}

	DataSet & put(key_type key, value_type value) {
		// TODO log
		bool putAns = data.insert(key, value.c_str());
		if (!putAns) {
			std::cerr << "Put " << key << " failed.\n";
			// TODO restore
		}
		return *this;
	}

	DataSet & del(key_type key) {
		// TODO log
		bool delAns = data.erase(key);
		if (!delAns) {
			std::cerr << "Del " << key << " failed\n";
			// TODO restore
		}
		return *this;
	}

};

#endif //SYSTEM2018_DATABASE_DATA_H
