#include "Logger.h"
#include <vector>
#include <fstream>
#include <cstdio>
#include "Parser.h"
#include <tuple>

Logger::LogPiece::LogPiece(sample::Command op, int k, std::string v) : operation(op), key(k), value(v) {}

Logger::LogPiece::LogPiece(Date d) : date(d) {}

Logger::LogPiece::LogPiece(std::tuple<sample::Command, int, std::string> t) :
	operation(std::get<0>(t)), key(std::get<1>(t)), value(std::get<2>(t)) {}

std::vector<Logger::LogPiece> Logger::getRestoreContext()
{
	std::vector<std::string> whole_log = getWholeLog();
	std::vector<std::string>::const_iterator citer;
	std::vector<Logger::LogPiece> transaction_logs;
	for (std::vector<std::string>::const_iterator citer = whole_log.cend() - 1; citer != whole_log.cbegin(); --citer)
	{
		if ((*citer)[0] == '@')
			break;
		transaction_logs.push_back(Logger::LogPiece(parser.decode(*citer)));
	}
	return std::move(transaction_logs);
}

std::vector<std::string> Logger::getWholeLog()
{
	logPath = getLastLogPath();
	std::ifstream log_file(logPath);
	if (!log_file.is_open())
	{
		std::cout << "fail to open file";
		exit(1);
	}
	std::vector<std::string> whole_file = std::vector<std::string>();
	std::string cur_line;
	while (std::getline(log_file, cur_line))
	{
		whole_file.push_back(cur_line);
	}
	return whole_file;
}

std::string Logger::getLastLogPath()
{
	std::ifstream log_record(LOG_RECORD_PATH);
	if (!log_record.is_open())
	{
		std::cout << "fail to open file";
		exit(1);
	}
	std::string cur_line;
	while (std::getline(log_record, cur_line)) {}
	return cur_line;
}



