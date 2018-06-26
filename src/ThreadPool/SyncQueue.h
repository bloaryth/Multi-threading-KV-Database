//
// Created by wanton-wind on 2018/6/26.
//

#ifndef SYSTEM2018_DATABASE_SYNCQUEUE_H
#define SYSTEM2018_DATABASE_SYNCQUEUE_H

#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>

template<typename T>
class SyncQueue {
private:
    std::list<T> bufferList;
    std::mutex queueMutex;
    std::condition_variable notEmpty;
    std::condition_variable notFull;
    int maxSize;
    bool needStop;

public:
    SyncQueue(int maxSize) : maxSize(maxSize), needStop(false){

    }

    void put(const T&){

    }

    void get(){}


private:

    template<typename F>
    void add(F&& x){
        std::unique_lock<std::mutex> locker(queueMutex);
        notFull.wait(locker, [this]{return needStop || notFull();});
    }

};


#endif //SYSTEM2018_DATABASE_SYNCQUEUE_H
