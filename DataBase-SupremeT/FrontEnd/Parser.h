//
// Created by wanton-wind on 2018/5/6.
//

#ifndef SYSTEM2018_DATABASE_BASEPARSER_H
#define SYSTEM2018_DATABASE_BASEPARSER_H

#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include "../Error.h"

namespace sample {
enum class Command {
    PUT = 0, GET = 1, DEL = 2,
};

class Parser {
private:
    static Command stoc(std::string cs) {
        if (cs == "PUT") {
            return Command::PUT;
        }
        else if (cs == "GET") {
            return Command::GET;
        }
        else if (cs == "DEL") {
            return Command::DEL;
        }
        else {
            throw UnknownCommandType();
        }
    }

public:
    static std::tuple<Command, int, std::string> decode(std::stringstream& ss) {
        std::string cs;
        int k;
        std::string v;
        ss >> cs >> k >> v;
        Command c = stoc(cs);
        return std::make_tuple(c, k, v);
    };

    static std::tuple<Command, int, std::string> decode(std::string s) {
        std::stringstream ss{ s };
        return decode(ss);
    };
};

}

#endif //SYSTEM2018_DATABASE_BASEPARSER_H
