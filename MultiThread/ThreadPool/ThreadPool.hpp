//
// Created by wanton-wind on 2018/6/27.
//

#ifndef SYSTEM2018_DATABASE_THREADPOOL_H
#define SYSTEM2018_DATABASE_THREADPOOL_H

#include <vector>
#include <thread>
#include <functional>
#include <memory>
#include <atomic>
#include <mutex>
#include "SyncQueue.hpp"

namespace Dytz {

    const int MaxTaskCount = 100;

    class Task {
        std::function
    };

    class ThreadPool {
    private:
//        using Task = decltype([]{});
        using Task =

        std::list<std::shared_ptr<std::thread>> threads;
        SyncQueue<Task> syncQueue;
        std::atomic_bool running;
        std::once_flag stopFlag;

    public:
        ThreadPool(int numThreads = std::thread::hardware_concurrency()) : syncQueue(MaxTaskCount) {
            start(numThreads);
        }

        ~ThreadPool() {
            stop();
        }

        void stop() {
            std::call_once(stopFlag, [this]{ stopThreads(); });
        }

        template<typename Function, typename... Args>
        void addTask(const Function &function, Args&... args) {
            syncQueue.put([&function, &args...]{ return function(args...); });
        };

    private:
        void start(int numThreads) {
            running = true;
            for (int i = 0; i <numThreads; ++i) {
                threads.push_back(std::make_shared<std::thread>(&ThreadPool::runInThread, this));
            }
        }

        void runInThread() {
            while (running) {
                std::list<Task> list;
                syncQueue.take(list);
                for (auto& task : list) {
                    if (!running) {
                        return;
                    }
                    task();
                }
            }
        }

        void stopThreads() {
            syncQueue.stop();
            running = false;
            for (const auto & thread : threads) {
                if (thread) {
                    thread->join();
                }
            }
            threads.clear();
        }
    };
}

#endif //SYSTEM2018_DATABASE_THREADPOOL_H
