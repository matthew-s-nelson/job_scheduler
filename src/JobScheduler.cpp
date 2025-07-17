//
// Created by Matthew Nelson on 7/7/25.
//

#include "JobScheduler.h"

JobScheduler::JobScheduler(size_t numThreads): pool_(numThreads) {}

JobScheduler::~JobScheduler() {
    pool_.shutdown();
}

std::string JobScheduler::schedule(std::function<void()> func, int delayMs, int repeatIntervalMs, int priority) {
    auto scheduledTime = Job::Clock::now() + std::chrono::milliseconds(delayMs);
    Job newJob(func, scheduledTime, repeatIntervalMs, priority);
    pool_.enqueueJob(newJob);
    return newJob.getId();
}

void JobScheduler::cancelJob(std::string jobId) {
    pool_.cancelJob(jobId);
}