//#include <iostream>
//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/json_parser.hpp>
////#include <boost/thread.hpp>
////#include <boost/foreach.hpp>
//#include <mutex>
//#include <shared_mutex>
//#include <string>
//#include "TranMgnt/Database.h"
////#include "Sample/Database.h"
//#include <map>
//
//using namespace boost::property_tree;
//
//
//int main(){
//
//    sample::Database database(R"(test.txt)", R"(log.txt)");
//    try {
//        // s means a transaction
//        database.process("PUT 1 111\nPUT 2 222\nPUT 3 333\nGET 1\nGET 2\nGET 3\nGET 4\nDEL 1\nDEL 2\nDEL 5");
//        std::cout << database.getOutput().str() << '\n';
//    }
//    catch (...){
//        std::cerr << "Unknown Error occurred.\n";
//    }
//
//}

//linux, g++ -std=c++14 -o t *.cpp -pthread
#include <queue>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <unistd.h>

class Task{
private:
    int no;
public:
    Task(int n){
        no = n;
    }
    //可以继承这个类重写该方法执行任务
    virtual void run(){
        sleep(no); //构造时决定执行几秒，模拟线程运行
        std::cout << no << "T\n";
    }
};

class Thread{
private:
    std::thread _thread;
    bool _isfree;
    Task *_task;
    std::mutex _locker;
public:
    //构造
    Thread() : _isfree(true), _task(nullptr){
        _thread = std::thread(&Thread::run, this);
        _thread.detach(); //放到后台， join是等待线程结束
    }
    //是否空闲
    bool isfree(){
        return _isfree;
    }
    //添加任务
    void add_task(Task *task){
        if(_isfree){
            _locker.lock();
            _task = task;
            _isfree = false;
            _locker.unlock();
        }
    }
    //如果有任务则执行任务，否则自旋
    void run(){
        while(true){
            if(_task){
                _locker.lock();
                _isfree = false;
                _task->run();
                _isfree = true;
                _task = nullptr;
                _locker.unlock();
            }
        }
    }
};

class ThreadPool{
private:
    std::queue<Task *> task_queue;
    std::vector<Thread *> _pool;
    std::mutex _locker;
public:
    //构造线程并后台执行，默认数量为10
    ThreadPool(int n = 10){
        while(n--){
            Thread *t = new Thread();
            _pool.push_back(t);
        }
        std::thread main_thread(&ThreadPool::run, this);
        main_thread.detach();
    }
    //释放线程池
    ~ThreadPool(){
        for(int i = 0;i < _pool.size(); ++i){
            delete _pool[i];
        }
    }
    //添加任务
    void add_task(Task *task){
        _locker.lock();
        task_queue.push(task);
        _locker.unlock();
    }
    //轮询
    void run(){
        while(true){
            _locker.lock();
            if(task_queue.empty()){
                continue;
            }
            // 寻找空闲线程执行任务
            for(int i = 0; i < _pool.size(); ++i){
                if(_pool[i]->isfree()){
                    _pool[i]->add_task(task_queue.front());
                    task_queue.pop();
                    break;
                }
            }
            _locker.unlock();
        }
    }
};
int main(){
    ThreadPool tp(2);

    Task t1(1);
    Task t2(3);
    Task t3(2);
    tp.add_task(&t1);
    tp.add_task(&t2);
    tp.add_task(&t3);

    sleep(4);   //等待调度器结束，不然会崩溃
    return 0;
}