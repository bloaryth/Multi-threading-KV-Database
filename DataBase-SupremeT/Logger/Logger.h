//
// Created by wanton-wind on 2018/5/20.
//

#ifndef SYSTEM2018_DATABASE_LOGGER_H
#define SYSTEM2018_DATABASE_LOGGER_H

#include <string>
#include <fstream>
#include "../DataSet.h"
#include <vector>
#include "../Tools.hpp"
#include "../DataBase.h"

namespace sample {
class LogPiece {
private:
    sample::Command operation;
    int key;
    std::string value;
    bool is_date;
    Date date;
public:
    LogPiece(sample::Command op, int k, std::string v);

    LogPiece(Date d);

    LogPiece(std::tuple<sample::Command, int, std::string> t);
};

class Logger {
    const std::string LOG_RECORD_PATH = "LOG_RECORD.txt";
private:
    // logger path
    std::string logPath;
    sample::Parser parser;

    // get the exactly context useful for database restore
    std::vector<LogPiece> getRestoreContext();

    std::string getLastLogPath();

public:
    Logger(std::string filename) : logPath(filename) {

    }

    // create log
    void createLog(std::string transaction) {
        // TODO
    }

    // restore the database by log
    void restore(DataSet &database) {
        // TODO
    }

private:
    std::vector<std::string> getWholeLog();

    LogPiece getLogPiece(std::tuple<sample::Command, int, std::string> t);
};
}


#endif //SYSTEM2018_DATABASE_LOGGER_H
