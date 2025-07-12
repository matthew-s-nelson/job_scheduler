//
// Created by Matthew Nelson on 7/9/25.
//

#include <gtest/gtest.h>
#include "../src/JobScheduler.h"
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

TEST(JobSchedulerTest, RunsJobsInOrderOfExecuteTime) {
    std::vector<int> executionOrder;
    JobScheduler jobScheduler(1);

    // Should run 2nd
    jobScheduler.schedule([&executionOrder] {
        executionOrder.push_back(1);
    }, 100, 1);

    // Should run 1st
    jobScheduler.schedule([&executionOrder] {
        executionOrder.push_back(2);
    }, 50, 1);

    // Should run 3rd
    jobScheduler.schedule([&executionOrder] {
        executionOrder.push_back(3);
    }, 150, 1);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::vector<int> expectedOrer = {2, 1, 3};
    EXPECT_EQ(executionOrder, expectedOrer);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}