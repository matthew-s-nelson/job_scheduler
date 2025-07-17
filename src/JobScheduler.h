//
// Created by Matthew Nelson on 7/7/25.
//

#ifndef JOB_SCHEDULER_JOBSCHEDULER_H
#define JOB_SCHEDULER_JOBSCHEDULER_H

#pragma once
#include "ThreadPool.h"
#include <chrono>

class JobScheduler {
public:
    JobScheduler(size_t numThreads);
    ~JobScheduler();

    std::string schedule(std::function<void()> func, int delayMs = 0, int repeatIntervalMs = 0, int priority = 0);
    void cancelJob(std::string jobId);

private:
    ThreadPool pool_;
};


#endif //JOB_SCHEDULER_JOBSCHEDULER_H
