//
// Created by wanton-wind on 2018/6/26.
//

#ifndef SYSTEM2018_DATABASE_SYNCQUEUE_H
#define SYSTEM2018_DATABASE_SYNCQUEUE_H

#include<list>
#include<mutex>
#include<thread>
#include<condition_variable>
#include <iostream>


namespace Dytz {

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
        SyncQueue(int maxSize) :maxSize(maxSize), needStop(false) {

        }

        void put(const T &x) {
            std::unique_lock<std::mutex> locker(queueMutex);
            notFull.wait(locker, [this]{ return needStop || bufferList.size() < maxSize; });
            if (needStop) {
                return;
            }
            bufferList.push_back(std::move(x));
            notEmpty.notify_one();
        }

        void take(std::list<T> &list)
        {
            std::unique_lock<std::mutex> locker(queueMutex);
            notEmpty.wait(locker, [this]{ return needStop || !bufferList.empty(); });
            if (needStop) {
                return;
            }
            list = std::move(bufferList);
            notFull.notify_one();
        }

        void stop()
        {
            {
                std::lock_guard<std::mutex> locker(queueMutex);
                needStop = true;
            }
            notFull.notify_all();
            notEmpty.notify_all();
        }

    };

}


#endif //SYSTEM2018_DATABASE_SYNCQUEUE_H
