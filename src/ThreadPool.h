//
// Created by Matthew Nelson on 7/7/25.
//

#ifndef JOB_SCHEDULER_THREADPOOL_H
#define JOB_SCHEDULER_THREADPOOL_H

#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include "Job.h"
#include <cstdlib>
#include <unordered_set>

class ThreadPool {
public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();

    // Add a job to the thread pool
    void enqueueJob(Job job);
    // Shut down the thread pool and clean up resources
    void shutdown();
    void cancelJob(const std::string jobId);

private:
    void workerLoop();

    // Compare by priority if they are scheduled for the same time.
    struct JobComparator {
        bool operator()(const Job& a, const Job& b) {
            if (a.getScheduledTime() == b.getScheduledTime()) {
                return a.getPriority() > b.getPriority();
            }
            return a.getScheduledTime() > b.getScheduledTime();
        }
    };

    std::priority_queue<Job, std::vector<Job>, JobComparator> jobs_;
    std::unordered_set<std::string> canceledJobs_;
    std::vector<std::thread> workers_;
    std::mutex mutex_;
    std::mutex cancelJobsMutex_;
    std::condition_variable cv_;
    std::atomic<bool> stop_;
};


#endif //JOB_SCHEDULER_THREADPOOL_H
