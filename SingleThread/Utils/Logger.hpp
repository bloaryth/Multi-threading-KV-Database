//
// Created by wanton-wind on 2018/5/20.
//

#ifndef SYSTEM2018_DATABASE_LOGGER_H
#define SYSTEM2018_DATABASE_LOGGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Parser.hpp"
#include "../Database.hpp"


namespace Dytz {

    class Database;

    class Logger {
        const std::string LOG_RECORD_PATH = "LOG_RECORD.txt";
    private:
        // logging path
        std::string logPath;

        std::string getLastLogPath(){
            std::ifstream logRecord(LOG_RECORD_PATH);
            if (!logRecord.is_open()) {
                throw OpenFileError();
            }
            std::string cur_line;
            while (std::getline(logRecord, cur_line)) {}
            return cur_line;
        };

        std::vector<std::string> getWholeLog() {
//            logPath = getLastLogPath();
            std::ifstream logFile(logPath);
            if (!logFile.is_open()) {
                throw OpenFileError();
            }
            std::vector<std::string> whole_file = std::vector<std::string>();
            std::string cur_line;
            while (std::getline(logFile, cur_line)) {
                whole_file.push_back(cur_line);
            }
            return whole_file;
        };

    public:
        Logger() {
            std::ifstream logRecord(LOG_RECORD_PATH);
            if (!logRecord) {
                std::ofstream logRecordOut(LOG_RECORD_PATH, std::ios::out);
                logRecordOut << "LOG-" << 0 << ".txt";
                logRecordOut.close();
            }
            logRecord.close();
            logPath = getLastLogPath();
        };

        // TODO split

        // create log
        void createLog(const std::string &transaction) {
            std::ifstream inLog(logPath);
            std::ofstream logFile;
            if(!inLog) {
                logFile.open(logPath, std::ios::out);
            } else {
                logFile.open(logPath, std::ios::app);
            }
            if (!logFile) {
                throw OpenFileError();
            }
            logFile << transaction << '\n';
            logFile.close();
        }

        // get the exactly context useful for database restore
        std::vector<LogPiece> getRestoreContext() { // TODO endline
            std::vector<std::string> whole_log = getWholeLog();
            std::vector<LogPiece> restoreContext;
            if (whole_log.empty()) {
                return restoreContext;
            }
            for (auto citer = whole_log.cend() - 1; citer != whole_log.cbegin(); --citer) {
                if ((*citer)[0] == '@')
                    break;
                restoreContext.push_back(LogPiece(LogParser::decode(*citer)));
            }
            return std::move(restoreContext);
        };

        std::vector<LogPiece> getRollBackContext(){
            // TODO
        }

    };


}


#endif //SYSTEM2018_DATABASE_LOGGER_H
