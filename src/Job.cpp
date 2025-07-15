//
// Created by Matthew Nelson on 7/7/25.
//

#include "Job.h"
#include <functional>

Job::Job(std::function<void()> func,
         Clock::time_point scheduledTime,
         int repeatIntervalMs,
         int priority
) : func_(func),
    scheduledTime_(scheduledTime),
    repeatIntervalMs_(repeatIntervalMs),
    priority_(priority)
{
    uuid_t uuid;
    uuid_generate(uuid);
    char str[37];
    uuid_unparse(uuid, str);
    id_ = std::string(str);
}

void Job::execute() const {
    func_();
}

std::string Job::getId() const {
    return id_;
}

Job::Clock::time_point Job::getScheduledTime() const {
    return scheduledTime_;
}

int Job::getPriority() const {
    return priority_;
}

bool Job::isRepeating() const {
    return repeatIntervalMs_ > 0;
}

void Job::updateScheduledTimeForRepeat() {
    // In the future, I may want to make this just add to the scheduled time.
    scheduledTime_ = Clock::now() + std::chrono::milliseconds(repeatIntervalMs_);
}