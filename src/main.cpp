//
// Created by Matthew Nelson on 7/7/25.
//

#include "JobScheduler.h"
#include <iostream>
#include <thread>

int main() {
    JobScheduler jobScheduler(3);

    jobScheduler.schedule([] {
        std::cout << "Job Second\n";
    }, 1000, 1);

    jobScheduler.schedule([] {
        std::cout << "Job First\n";
    }, 50, 1);

    jobScheduler.schedule([] {
        std::cout << "Job Third\n";
    }, 1100, 1);

    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 0;
}