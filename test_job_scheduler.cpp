//
// Created by Matthew Nelson on 7/9/25.
//

#include <gtest/gtest.h>
#include "JobScheduler.h"
#include <atomic>
#include <chrono>
#include <thread>

TEST(JobSchedulerTest, ExecutesJob) {
    std::atomic<bool> ran = false;

    JobScheduler jobScheduler(1);
    jobScheduler.schedule([&ran] {
        ran = true;
    }, 0, 1);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_TRUE(ran);
}

TEST(JobSchedulerTest, ExecutesAfterDelay) {
    std::atomic<bool> ran = false;

    JobScheduler jobScheduler(1);
    jobScheduler.schedule([&ran] {
        ran = true;
    }, 50, 1);

    EXPECT_FALSE(ran);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_TRUE(ran);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}