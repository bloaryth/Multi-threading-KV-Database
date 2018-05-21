//
// Created by wanton-wind on 2018/5/20.
//

#ifndef SYSTEM2018_DATABASE_LOGGER_H
#define SYSTEM2018_DATABASE_LOGGER_H

#include <string>
#include <fstream>
#include "DataSet.h"

class DataSet;

class Logger {
private:
    // logger path
    std::string logPath;

    // get the exactly context useful for database restore
    std::string getRestoreContext(){
        // TODO
    }

public:
    Logger(std::string filename): logPath(filename) {

    }

    // create log
    void createLog(std::string transaction){
        // TODO
    }

    // restore the database by log
    void restore(DataSet & database){
        // TODO
    }
};


#endif //SYSTEM2018_DATABASE_LOGGER_H
