//
// Created by Matthew Nelson on 7/7/25.
//

#include "Job.h"

Job::Job(std:function<void()> func,
         Clock::time_point scheduledTime,
         int priority)
         : func_(func), scheduledTime_(scheduledTime), priority_(priority) {
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