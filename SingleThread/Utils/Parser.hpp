//
// Created by wanton-wind on 2018/5/6.
//

#ifndef SYSTEM2018_DATABASE_BASEPARSER_H
#define SYSTEM2018_DATABASE_BASEPARSER_H

#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include "Error.hpp"

namespace Dytz {

    enum class InstCommand {
        PUT = 0, GET = 1, DEL = 2,
    };

    using InstPiece = std::tuple<InstCommand, int, std::string>;

    class InstParser {
    private:
        static InstCommand stoc(const std::string &cs) {
            if (cs == "PUT") {
                return InstCommand::PUT;
            } else if (cs == "GET") {
                return InstCommand::GET;
            } else if (cs == "DEL") {
                return InstCommand::DEL;
            } else {
                throw UnknownCommandType();
            }
        }

    public:
        static InstPiece decode(std::stringstream &ss) {
            std::string cs;
            int k;
            std::string v;
            ss >> cs >> k >> v;
            InstCommand c = stoc(cs);
            return std::make_tuple(c, k, v);
        };

        static InstPiece decode(const std::string &s) {
            std::stringstream ss(s);
            return decode(ss);
        };
    };

    enum class LogCommand {
        INSERT = 0, UPDATE = 1, ERASE = 2,
    };

    using LogPiece = std::tuple<LogCommand, int, std::string, std::string>;

    class LogParser {
    private:
        static LogCommand stoc(const std::string &cs) {
            if (cs == "INSERT") {
                return LogCommand::INSERT;
            } else if (cs == "UPDATE") {
                return LogCommand::UPDATE;
            } else if (cs == "ERASE") {
                return LogCommand::ERASE;
            } else {
                throw UnknownCommandType();
            }
        }

    public:
        static LogPiece decode(std::stringstream &ss) {
            std::string cs;
            int k;
            std::string vn;
            std::string vo;
            ss >> cs >> k >> vn >> vo;
            LogCommand c = stoc(cs);
            return std::make_tuple(c, k, vn, vo);
        };

        static LogPiece decode(const std::string &s) {
            std::stringstream ss(s);
            return decode(ss);
        };
    };


}

#endif //SYSTEM2018_DATABASE_BASEPARSER_H
