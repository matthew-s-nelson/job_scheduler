//
// Created by Matthew Nelson on 7/7/25.
//

#ifndef JOB_SCHEDULER_JOB_H
#define JOB_SCHEDULER_JOB_H

#pragma once
#include <functional>
#include <chrono>
#include <string>
#include <atomic>
#include <uuid/uuid.h>

class Job {
public:
    using Clock = std::chrono::steady_clock;

    Job(std::function<void()> func,
        Clock::time_point scheduledTime,
        int priority = 0);

    void execute() const;
    std::string getId() const;
    Clock::time_point getScheduledTime() const;
    int getPriority() const;

private:
    std::function<void()> func_;
    Clock::time_point scheduledTime_;
    int priority_;
    std::string id_;
};


#endif //JOB_SCHEDULER_JOB_H
