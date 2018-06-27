//
// Created by wanton-wind on 2018/5/6.
//

#ifndef SYSTEM2018_DATABASE_DATABASE_H
#define SYSTEM2018_DATABASE_DATABASE_H

#include <iostream>
#include <tuple>
#include "BpTree/BpTree.hpp"
#include "Utils/Error.hpp"
#include "Utils/Parser.hpp"
#include "Utils/Logger.hpp"
#include "ThreadPool/ThreadPool.hpp"

namespace Dytz {

    class Logger;

    class Database {

    private:
        friend class Logger;

        using key_type = int;
        using value_type = std::string;

        BpTree data;
        Logger logger;
        thread_local std::stringstream ss;
        ThreadPool threadPool;

    public:
        Database(const std::string &name) : data(name.c_str(), false) {
            restore();
        }

        void process(std::stringstream & s, std::stringstream & output) {
            logger.createLog("@START");
            std::string command;
            while (std::getline(s, command)) {
                InstCommand c;
                int k;
                std::string v;
                try {
                    std::tie(c, k, v) = InstParser::decode(command);
                    processSingle(c, k, v);
                }
                catch (UnknownCommandType&) {
                    std::cerr << "UnknownCommandType in \"" << command << "\".\n";
                }
                catch (OpenFileError&) {
                    std::cerr << "OpenFileError in \"" << command << "\".\n";
                }
            }
            logger.createLog("@END");
            output = std::move(ss);
        }

        // s means a transaction
        std::stringstream& process(const std::string &s) {
            std::stringstream ss(s);
            std::stringstream output;
            threadPool.addTask(process, ss, output);
            return output; // FIXME output may not be already
        }

    private:
        // process single command
        void processSingle(InstCommand c, int k, const std::string &v) {
            switch (c) {
                case InstCommand::PUT:
                    put(k, v);
                    break;
                case InstCommand::GET:
                    ss << get(k) << ' ';
                    break;
                case InstCommand::DEL:
                    del(k);
                    break;
            }
        }

        value_type get(key_type key) {
            bool isFind = data.find(key);
            if (!isFind) {
                std::cerr << "Get " << key << " failed.\n";
            }
            return data.get(key).str;
        }

        Database & put(key_type key, const value_type &value) {
            bool isFind = data.find(key);
            if (!isFind) {
                logger.createLog("INSERT " + std::to_string(key) + " " + value);
                data.insert(key, value.c_str());
            } else {
                logger.createLog("UPDATE " + std::to_string(key) + " " + value + " " + data.get(key).str);
                data.update(key, value.c_str());
            }
            return *this;
        }

        Database & del(key_type key) {
            bool isFind = data.find(key);
            if (!isFind) {
                std::cerr << "Del " << key << " failed.\n";
            } else {
                logger.createLog("ERASE " + std::to_string(key) + " " + data.get(key).str);
                data.erase(key);
            }
            return *this;
        }

        Database & restore(){
            std::vector<LogPiece> restoreContext = logger.getRestoreContext();
            for (const auto & logpiece : restoreContext) {
                LogCommand c;
                int k;
                std::string vn;
                std::string vo;
                std::tie(c, k, vn, vo) = logpiece;
                if (c == LogCommand::INSERT) {
                    data.erase(k);
                } else if (c == LogCommand::UPDATE) {
                    data.update(k, vo.c_str());
                } else if (c == LogCommand::ERASE) {
                    if (vn != "") {
                        data.insert(k, vn.c_str());
                    }
                } else {
                    throw UnknownCommandType();
                }
            }
        }

    };

}

#endif //SYSTEM2018_DATABASE_DATABASE_H
