#pragma once

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

#include <iostream>

// todo: make adding workers thread safe

class ThreadPool {
public:
    ThreadPool() { init(1); }
    ThreadPool(size_t threads) { init(threads); }
    ~ThreadPool();
    // object is move only
    ThreadPool& operator=(ThreadPool&& other) noexcept {
        
        //std::unique_lock<std::mutex> otherLock(other.queue_mutex);
        //std::unique_lock<std::mutex> thisLock(this->queue_mutex);

        // Guard self assignment
        if (this == &other) {
            return *this;
        }

        std::cout << "Trying to copy a threadpool! not supported correctly and may result in UB";

        /*
        this->workers = std::exchange(other.workers, {});
        this->tasks = std::exchange(other.tasks, {});
        other.condition.notify_all();
        this->stop = std::exchange(other.stop, true);
        */

        //this->workers = std::move(other.workers);
        //this->tasks = std::move(other.tasks);
        
        other.stop = true;
        other.condition.notify_all();

        return *this;
    }
    ThreadPool(ThreadPool&& other) noexcept {
        std::cout << "Trying to copy a threadpool! not supported correctly and may result in UB";
        /*
        std::unique_lock<std::mutex> otherLock(other.queue_mutex);
        std::unique_lock<std::mutex> thisLock(this->queue_mutex);
        this->tasks = std::move(other.tasks);
        this->workers = std::move(other.workers);
        other.condition.notify_all();
        this->stop = std::exchange(other.stop, true);        
        */
    }

    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::result_of<F(Args...)>::type>;
    inline void addThread();
    inline void removeThreadGentle();
    size_t numWorkers() const { return workers.size(); }
    size_t numTasks() { 
        queue_mutex.lock(); 
        auto n = tasks.size(); 
        queue_mutex.unlock(); 
        return n; 
    }
private:
    inline void init(size_t threads);
    // need to keep track of threads so we can join them
    std::vector< std::thread > workers;
    // the task queue
    std::queue< std::function<void()> > tasks;
    
    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

inline void ThreadPool::init(size_t threads) {
    this->stop = false;
    for (size_t i = 0; i < threads; ++i)
        workers.emplace_back(
            [this]
            {
                for (;;)
                {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock,
                            [this] { return this->stop || !this->tasks.empty(); });
                        if (this->stop && this->tasks.empty())
                            return;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }

                    task();
                }
            }
            );
}

// add new work item to the pool
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) 
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared< std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        if(stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        tasks.emplace([task](){ (*task)(); });
    }
    condition.notify_one();
    return res;
}

inline void ThreadPool::addThread() {
    workers.emplace_back(
        [this]
        {
            for (;;)
            {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(this->queue_mutex);
                    this->condition.wait(lock,
                        [this] { return this->stop || !this->tasks.empty(); });
                    if (this->stop && this->tasks.empty())
                        return;
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }

                task();
            }
        }
    );
}

inline void ThreadPool::removeThreadGentle() {
    // first look for one who is not working ...
    for (auto&& thread : workers)
        if (thread.joinable()) {
            thread.join();
            return;
        }
    // else just wait on the first one yolo ...
    workers[0].join();
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for(std::thread &worker: workers)
        if (worker.joinable())
            worker.join();
}
