//
// Created by Matthew Nelson on 7/7/25.
//

#include "ThreadPool.h"
#include <iostream>
#include <chrono>

ThreadPool::ThreadPool(size_t numThreads): stop_(false) {
    for (size_t i = 0; i < numThreads; ++i) {
        workers_.emplace_back(&ThreadPool::workerLoop, this);
    }
}

void ThreadPool::enqueueJob(Job job) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        jobs_.push(job);
    }
    cv_.notify_one();
}

void ThreadPool::shutdown() {
    stop_ = true;
    cv_.notify_all();

    for (std::thread worker : workers_) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void ThreadPool::~ThreadPool() {
    shutdown();
}

void ThreadPool::workerLoop() {
    // Go until thread pool is shutdown
    while (true) {
        Job job([] {}, Job::Clock::now()); // dummy job
        {
            std::unique_lock<std::mutex> lock(mutex_);

            cv_.wait(lock, [this]() {
                return stop_ || !jobs_.empty();
            });

            // Only stop if all jobs are completed
            if (stop_ && jobs_.empty()) return;

            auto now = Job::Clock::now();

            // Wait until we reach the next job's scheduled time
            if (jobs_.top().getScheduledTime() > now) {
                cv_.wait_until(lock, jobs_.top().getScheduledTime());
                continue;
            }

            job = jobs_.top();
            jobs_.pop();
        }

        std::cout << "[Thread " << std::this_thread::get_id() << "] Executing job: " << job.getId() << "\n";
        job.execute();
    }
}