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
    }, 0, 0, 0);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_TRUE(ran);
}

TEST(JobSchedulerTest, ExecutesAfterDelay) {
    std::atomic<bool> ran = false;

    JobScheduler jobScheduler(1);
    jobScheduler.schedule([&ran] {
        ran = true;
    }, 50, 0, 0);

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
    }, 100, 0, 0);

    // Should run 1st
    jobScheduler.schedule([&executionOrder] {
        executionOrder.push_back(2);
    }, 50, 0, 0);

    // Should run 3rd
    jobScheduler.schedule([&executionOrder] {
        executionOrder.push_back(3);
    }, 150, 0, 0);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::vector<int> expectedOrer = {2, 1, 3};
    EXPECT_EQ(executionOrder, expectedOrer);
}

TEST(JobSchedulerTest, CancelsJob) {
    bool ran = false;
    JobScheduler jobScheduler(1);

    std::string jobId = jobScheduler.schedule([&ran] {
        ran = true;
    }, 100, 0, 0);

    // Cancel the job before it runs
    jobScheduler.cancelJob(jobId);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    EXPECT_FALSE(ran);
}

TEST(JobSchedulerTest, RepeatingJob) {
    std::atomic<int> runCount = 0;
    JobScheduler jobScheduler(1);

    std::string jobId = jobScheduler.schedule([&runCount] {
        runCount++;
    }, 0, 60, 0); // Repeat every 50ms

    jobScheduler.schedule([&jobScheduler, jobId] {
        jobScheduler.cancelJob(jobId); // Cancel after some time
    }, 200, 0, 0);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    EXPECT_EQ(runCount.load(), 4); // Should have run at least 3 times
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}